#include <helper.h>


#define INPUTSIZ 256


void doshell(char *);
extern void error(const char *fmt,...);
extern void fatal(const char *fmt,...);


void 
main(){
    char buf[INPUTSIZ];

    printf("> ");
    while ( fgets(buf, INPUTSIZ, stdin) != NULL ){
        doshell(buf);
        printf("> ");
    }
    exit(0);
}

void 
doshell(char *cmd)
{
    pid_t pid;
    if ( ( pid = fork() ) < 0 ) {
        error("fork failed");
        return ;
    }
    if ( pid == 0 ) {
        execl("/bin/sh", "sh", "-c", cmd, NULL);
        fatal("exec failed");
    }

    if ( waitpid(pid, NULL, 0) < 0 ) {
        fatal("waitpid failed");
    }
}