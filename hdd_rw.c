#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

ssize_t bytes=0;
ssize_t total=0; 

time_t start;
time_t finish;

extern int errno;

int F;
char NAME[255];

#define FILENAME argv[1]?argv[1]:"test.hdds"

void Exit()
{
 
 close(F);
 unlink(NAME);
 printf(" unlink  %s \n",NAME);
 fflush(stdout);
 
 exit(0);
}

void Alarm()
{
 
 printf("\rSize:%03.3f Mb Speed:%03.3f Mbytes/sec     ", (float)total/(1024*1024),(float)bytes/(1024*1024));
 bytes=0;
 
 fflush(stdout);
  
 signal(SIGALRM,(void *)Alarm);
 alarm(1);
 
}

#define BUF_SIZE (1024*7)

int write_tst(int argc, char * argv[])
{
 char buf[BUF_SIZE];
 ssize_t s;
 size_t size=BUF_SIZE;
 
 sprintf(NAME,"%s",FILENAME);
 
 printf("Writing to %s \n",NAME);
 
 unlink(NAME);

 time(&start);
 
 for(;;) {s=write(F,buf,size);
          if (s<0) { 
                     time(&finish);
                     printf(" Writing finished \n");
                     printf("Average write speed %03.3f MBytes/sec \n",((float) total)/(1024*1024*difftime(finish-start)));
                     return(0);
                   }
          
          bytes+=s;
          total+=s;
         }

 return 0;
}

int read_tst(int argc, char * argv[])
{
 char buf[BUF_SIZE];
 ssize_t s;
 
 printf("Reading from %s \n",NAME);
 
 s=lseek(F,0,SEEK_SET);
 
 total=0;
 bytes=0;

 time(&start);
  
 if (s!=0) {printf(" cant read file %s %s \n",NAME,sys_errlist[errno]);}
 
 for(;;) {s=read(F,buf,BUF_SIZE);
          if (s<=0) { close(F);
                     time(&finish);
                     unlink(NAME);printf(" Reading finished \n");
                     printf("Average read speed %03.3f MBytes/sec \n",((float) total)/(1024*1024*difftime(finish-start)));
                     printf("Read %ld bytes \n",total); 
                     return(0);
                   }
          
          bytes+=s;
          total+=s;
         }

 return 0;
}


int main(int argc, char * argv[])
{
 char buf[BUF_SIZE];
 ssize_t s;
 
 sprintf(NAME,"%s",FILENAME);
 
 printf("Open file %s \n",NAME);
 
 unlink(NAME);
 
 F=open(NAME,O_CREAT | O_RDWR | O_TRUNC /*| O_LARGEFILE*/  );
 
 if (F<=0) exit(1);
 
 atexit(Exit);
 
 signal(SIGQUIT,(void *)Exit);
 signal(SIGABRT,(void *)Exit);
 signal(SIGINT,(void *)Exit);
 
 signal(SIGALRM,Alarm);
 
 alarm(1);

 write_tst(argc,argv);
 read_tst(argc,argv);
 
 return 0;
}

