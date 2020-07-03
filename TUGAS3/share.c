/*
// Tambahkan di sini nama para kontributor (akunGitHub)
// Harap UPDATE tanggal revisi!
// Tue Jun  9 17:46:47 WIB 2020
 */

#include     "share.h"
char*        progs[]={P01, P02, P03, P04};
char         tmpStr[256]={};
extern char* akunGitHub;
extern int   delay;
extern int   boss;
myshare*     mymap;

// Tambahkan di sini nama para kontributor (akunGitHub)
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
        //
        // Blah... Blah... Blah.. harap lengkapi!
        // Lalu dihapus dong, baris Blah... Blah... Blahnya!
        //
        sem_init (&(mymap->mutex), 1, MUTEX); // lihat manual sem_init()!
        //
        // Blah... Blah... Blah.. harap lengkapi!
        // Lalu dihapus dong, baris Blah... Blah... Blahnya!
        //
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

// Tambahkan di sini nama para kontributor (akunGitHub)
// Harap UPDATE tanggal revisi!
// Tue Jun  9 17:46:47 WIB 2020
void myPrint(char* str1, char* str2) {
    printf("%s[%s]\n", str1, str2);
    fflush(NULL);
}

// Tambahkan di sini nama para kontributor (akunGitHub)
// Harap UPDATE tanggal revisi!
// Tue Jun  9 17:46:47 WIB 2020
int getEntry(char* akunGitHub) {
    int entry=0;
    sem_wait (&(mymap->mutex));
    //
    // Blah... Blah... Blah.. harap lengkapi!
    // Lalu dihapus dong, baris Blah... Blah... Blahnya!
    //
    sem_post (&(mymap->mutex));
    return entry;
}

// Tambahkan di sini nama para kontributor (akunGitHub)
// Harap UPDATE tanggal revisi!
// Tue Jun  9 17:46:47 WIB 2020
void display(int entry) {
    sem_wait (&(mymap->mutex));
    //
    // Blah... Blah... Blah.. harap lengkapi!
    // Lalu dihapus dong, baris Blah... Blah... Blahnya!
    //
    sem_post (&(mymap->mutex));
}

// Tambahkan di sini nama para kontributor (akunGitHub)
// Harap UPDATE tanggal revisi!
// Tue Jun  9 17:46:47 WIB 2020
void putInfo(char* akun, int entry) {
    sem_wait (&(mymap->mutex));
    //
    // Blah... Blah... Blah.. harap lengkapi!
    // Lalu dihapus dong, baris Blah... Blah... Blahnya!
    //
    sem_post (&(mymap->mutex));
}

// Tambahkan di sini nama para kontributor (akunGitHub)
// Harap UPDATE tanggal revisi!
// Tue Jun  9 17:46:47 WIB 2020
void checkOpen(void) {
    //
    // Blah... Blah... Blah.. harap lengkapi!
    // Lalu dihapus dong, baris Blah... Blah... Blahnya!
    //
}

// Tambahkan di sini nama para kontributor (akunGitHub)
// Harap UPDATE tanggal revisi!
// Tue Jun  9 17:46:47 WIB 2020
void myWait(int boss, int entry) {
    //
    // Blah... Blah... Blah.. harap lengkapi!
    // Lalu dihapus dong, baris Blah... Blah... Blahnya!
    //
}

// Tambahkan di sini nama para kontributor (akunGitHub)
// Harap UPDATE tanggal revisi!
// Tue Jun  9 17:46:47 WIB 2020
int main(int argc, char* argv[]) {
    sprintf(tmpStr, "START PID[%d] PPID[%d]", getpid(), getppid());
    myPrint(akunGitHub, tmpStr);
    init(boss, argc, argv);
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

