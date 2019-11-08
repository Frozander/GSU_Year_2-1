#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int i;
    __pid_t pid;

    char **args = malloc(sizeof(char*) * (argc - 1));

    for (i = 1; i < argc; i++)
        args[i - 1] = argv[i];

    printf("Starting %s with ", argv[1]);
    for (i = 0; i < argc - 2; i++)
        printf(" %s", args[i]);
    printf("\n");

    if ((pid = fork()) == 0)
    {
        execvp(argv[1], args);
        perror("Cannot execute command!");
        _exit(1);
    }
    if (pid < 0)
        perror("Fork Error!");    
    if (pid > 0)
    {
        int status;
        waitpid(pid, &status, 0);

        if (status > 0)
            printf("Process sent an error!\n");
        else
            printf("Process finished succesfully!\n");        
    }
    
    return 0;
}
