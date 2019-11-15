#include <stdio.h>
#include <sys/wait.h> 
#include <unistd.h>

void main(){
    int pid,i;
    pid=fork();
    if(pid!=0)
    {
        for(i=0;i<10;i++)
        {
            wait(NULL);
            printf("Je suis le processus père %d\n",i);
        }
    }
    if(pid==0)
    {
        for(i=0;i<10;i++)
        {
            printf("Je suis le processus fils %d\n",i);
            execlp("./prog", NULL);
        }
    }
    
}