/*
// abhiprayatj, stefansagala, reynardryanda, fatih-alaydrus, raniapriliaa, billhsyn, fadhilhmr
// Harap UPDATE tanggal revisi!
// Tue Jun  9 17:46:47 WIB 2020
 */

#include     "share.h"
char*        progs[]={P00, P01, P02, P03, P04, P05, P06};
char         tmpStr[256]={};
extern char* akunGitHub;
extern int   delay;
extern int   boss;
myshare*     mymap;

// abhiprayatj, stefansagala, reynardryanda, fatih-alaydrus, raniapriliaa, billhsyn, fadhilhmr
// Harap UPDATE tanggal revisi!
// Tue Jun  9 17:46:47 WIB 2020
void init(int isboss, int argc, char* argv[]) {
    if (isboss == BOSS) {
        int ssize=sizeof(myshare);
        int fd   =open(SHAREMEM, MYFLAGS, CHMOD);
        fchmod   (fd, CHMOD);
        ftruncate(fd, ssize);
        mymap=mmap(NULL, ssize, MYPROTECTION, MYVISIBILITY, fd, 0);
        close(fd);
        
        mymap->state = OPEN;
        
        sem_init (&(mymap->mutex), 1, MUTEX); // lihat manual sem_init()!
        
        if (argc > 1){
            mymap->state = OPEN;
            printf("ShareMemory is OPEN, BYE BYE ==== ====\n");
            exit(0);
        }
        
    } else {
        sleep(delay);
        if( access(SHAREMEM, F_OK ) == -1 ) {
            printf("No \"%s\" file.\n", SHAREMEM);
            exit(-1);
        }
        int fd=open(SHAREMEM, O_RDWR, CHMOD);
        int ssize=sizeof(myshare);
        mymap=mmap(NULL, ssize, MYPROTECTION, MYVISIBILITY, fd, 0);
        close(fd);
    }
}

// abhiprayatj, stefansagala, reynardryanda, fatih-alaydrus, raniapriliaa, billhsyn, fadhilhmr
// Harap UPDATE tanggal revisi!
// Tue Jun  9 17:46:47 WIB 2020
void myPrint(char* str1, char* str2) {
    printf("%s[%s]\n", str1, str2);
    fflush(NULL);
}

// abhiprayatj, stefansagala, reynardryanda, fatih-alaydrus, raniapriliaa, billhsyn, fadhilhmr
// Harap UPDATE tanggal revisi!
// Tue Jun  9 17:46:47 WIB 2020
int getEntry(char* akunGitHub) {
    int entry=0;
    sem_wait (&(mymap->mutex));
    
     if (mymap->entry == 7){ //xxx
        int i = 0;
        while(i < mymap->entry){
            int compare = strcmp(mymap->progs[i].akun, akunGitHub);
            if (compare == 0){
                entry = i;
                break;
            }
            i++;
        }
    }
    else entry = mymap->entry++;
    
    mymap->mutexctr++;
    mymap->progs[entry].stamp++;
    
    sem_post (&(mymap->mutex));
    return entry;
}

// abhiprayatj, stefansagala, reynardryanda, fatih-alaydrus, raniapriliaa, billhsyn, fadhilhmr
// Harap UPDATE tanggal revisi!
// Tue Jun  9 17:46:47 WIB 2020
void display(int entry) {
    sem_wait (&(mymap->mutex));
    
    memset(tmpStr, 0, 255);
    mymap->progs[entry].stamp++;
    mymap->mutexctr++;
    
    char state[11]={}; //xxx
    if(mymap->state == OPEN) sprintf(state, "MMAP[%s]", "OPEN");
    sprintf(tmpStr, "progs[%2.2d] TIME[%2.2d] MUTEX[%2.2d] %s ", entry, mymap->mutexctr, mymap->progs[entry].stamp, state);
    int i = 0;
    while (i < mymap->entry){
        sprintf(tmpStr, "%s[%s]", tmpStr, mymap->progs[i].akun);
        i++;
    }
    myPrint(akunGitHub, tmpStr);
    
    sem_post (&(mymap->mutex));
}

// abhiprayatj, stefansagala, reynardryanda, fatih-alaydrus, raniapriliaa, billhsyn, fadhilhmr
// Harap UPDATE tanggal revisi!
// Tue Jun  9 17:46:47 WIB 2020
void putInfo(char* akun, int entry) {
    sem_wait (&(mymap->mutex));
    strcpy(mymap->progs[entry].akun, akun);
    mymap->progs[entry].stamp++;
    mymap->mutexctr++;
    sem_post (&(mymap->mutex));
}

// abhiprayatj, stefansagala, reynardryanda, fatih-alaydrus, raniapriliaa, billhsyn, fadhilhmr
// Harap UPDATE tanggal revisi!
// Tue Jun  9 17:46:47 WIB 2020
void checkOpen(void) {
    if(mymap->state == CLOSED) {
        printf("ShareMemory is NOT OPEN, BYE BYE ==== ====\n");
        exit(0);
    }
}

// abhiprayatj, stefansagala, reynardryanda, fatih-alaydrus, raniapriliaa, billhsyn, fadhilhmr
// Harap UPDATE tanggal revisi!
// Tue Jun  9 17:46:47 WIB 2020
void myWait(int boss, int entry) {
    if (boss == BOSS){
        for (int i = 0; i < mymap->entry; i++) wait(NULL);
        mymap->state = CLOSED;
    }
}

// abhiprayatj, stefansagala, reynardryanda, fatih-alaydrus, raniapriliaa, billhsyn, fadhilhmr
// Harap UPDATE tanggal revisi!
// Tue Jun  9 17:46:47 WIB 2020
int main(int argc, char* argv[]) {
    sprintf(tmpStr, "START PID[%d] PPID[%d]", getpid(), getppid());
    myPrint(akunGitHub, tmpStr);
    init(boss, argc, argv);
    if (boss == BOSS){
        if (!fork()) execlp(progs[1], progs[1], NULL) < 0;
        else{
            if (!fork()) execlp(progs[2], progs[2], NULL) < 0;
            else{
                if (!fork()) execlp(progs[3], progs[3], NULL) < 0;
                else{
                    if (!fork()) execlp(progs[4], progs[4], NULL) < 0;
                    else{
                      if (!fork()) execlp(progs[5], progs[5], NULL) < 0;
                      else{
                        if (!fork()) execlp(progs[6], progs[6], NULL) < 0;
                      }
                    }
                }
            }
        }
    }
    checkOpen();
    sleep  (delay);
    int entry = getEntry(akunGitHub);
    sleep  (delay);
    display(entry);
    sleep  (delay);
    putInfo(akunGitHub, entry);
    sleep  (delay);
    display(entry);
    myWait (boss, entry);
    myPrint(akunGitHub, "BYEBYE =====  ===== =====");
}

