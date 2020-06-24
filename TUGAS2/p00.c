/*
// Sun Jun 21 14:27:37 WIB 2020
// Tue Jun  9 17:46:47 WIB 2020
 */

// adjust DELAY and akunGitHub
#define  DELAY 5
#define  akunGitHub "stefansagala"
#include "p00.h"

char*    progs[]={P01, P02, P03, P04, P05, P06};
myshare* mymap;
int      entry;

int init(void) {
    int ssize=sizeof(myshare);
    int fd   =open(SHAREMEM, MYFLAGS, CHMOD);
    fchmod   (fd, CHMOD);
    ftruncate(fd, ssize);
    mymap=mmap(NULL, ssize, MYPROTECTION, MYVISIBILITY, fd, 0);
    close(fd);
    
    sem_init(&mymap->mutex, 1, 1);
    mymap->state = OPEN;

    return BOSS;
}

char tmpStr[256]={};  // temp string
void myprint(char* str1, char* str2) {
    printf("%-14s[%s]\n", str1, str2);
}

int getEntry(void) {
    return entry;
}

// display MMAP entry
void display(int entry) {
    int i;
    char akun[256] = {};
    int k = 0;
    while( k < getEntry()){
        sprintf(akun, "%s[%s]", akun, mymap->progs[k].akun);
        k++;
    }

    char state[5] = {}; 
    if (mymap->state == 255) 
        sprintf(state, "OPEN");

    sprintf(tmpStr, "progs[%2.2d] TIME[%2.2d] MUTEX[%2.2d] MMAP[%s] %s",
        getEntry(), mymap->mutexctr, mymap->progs[getEntry()].stamp, state, akun);
    myprint(akunGitHub, tmpStr);
}

void putInfo(char* akun, int entry) {
    strcpy(mymap->progs[entry].akun, akun);
}

void checkOpen(void) {
    if (mymap->state == CLOSED) {
      printf("CLOSED, BYE BYE ==== ====");
      exit(0);
    }
}

void incrementBos(int x) {
    sem_wait(&mymap->mutex);
    if (x == 1){
	entry = mymap->entry++;
    }
    mymap->mutexctr++;
    mymap->progs[getEntry()].stamp++;
    if (x == 2){
        display(mymap->entry);
    }
    if (x == 3){
        putInfo(akunGitHub, getEntry());
    }
    sem_post(&mymap->mutex);
}

int main(void) {
    sprintf(tmpStr, "START PID[%d] PPID[%d]", getpid(), getppid());
    myprint(akunGitHub, tmpStr);
    int boss=init();
    checkOpen();
    sleep (DELAY);

    int pid = getpid();
    int i = 0;
    while( i < sizeof(progs)/sizeof(char*)){
        if (fork() == 0) {
            execlp(progs[i], progs[i], NULL);
        };
        i++;
    }

    sleep (DELAY);

    incrementBos(1);

    incrementBos(2);

    sleep (DELAY);

    incrementBos(3);

    int j = 0;
    while( j < sizeof(progs)/sizeof(char*) ){
        incrementBos(2);
        wait(NULL);
        j++;
    }
    
    myprint(akunGitHub, "BYEBYE =====  ===== =====");
    mymap->state = CLOSED;
}