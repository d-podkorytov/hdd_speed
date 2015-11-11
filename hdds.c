#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

ssize_t bytes=0;
ssize_t total=0; 

time_t start;
time_t finish;

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

int main(int argc, char * argv[])
{
 char buf[BUF_SIZE];
 ssize_t s;
 
 sprintf(NAME,"%s",FILENAME);
 
 printf("Writing to %s \n",NAME);
 
 unlink(NAME);
 
 F=open(NAME,O_CREAT | O_WRONLY | O_TRUNC /*| O_LARGEFILE*/  );
 
 if (F<=0) exit(1);
 
 atexit(Exit);
 
 signal(SIGQUIT,(void *)Exit);
 signal(SIGABRT,(void *)Exit);
 signal(SIGINT,(void *)Exit);
 
 signal(SIGALRM,Alarm);
 
 alarm(1);

 time(&start);
 for(;;) {s=write(F,buf,BUF_SIZE);
          if (s<0) { close(F);
                     time(&finish);
                     unlink(NAME);printf(" Exit \n");
                     printf("Average speed %03.3f MBytes/sec \n",((float) total)/(1024*1024*difftime(finish-start)));
                     exit(1);
                   }
          
          bytes+=s;
          total+=s;
         }

 return 0;
}
