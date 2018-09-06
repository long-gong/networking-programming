#include <helper.h>

#define INPUTSIZ 256

static sigjmp_buf env;

static void catcher(int);
static void nop(int);
void doshell(char *);
extern void error(const char *fmt,...);
extern void fatal(const char *fmt,...);

void 
main()
{
    struct sigaction sa;
    char buf[INPUTSIZ];

    if ( sigsetjmp(env, 0) ){
        fprintf(stderr, "Interrupted!\n");
        exit(1);
    }

    printf("> ");
    sa.sa_handler = catcher;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGINT);
    sigaddset(&sa.sa_mask, SIGQUIT);

    sa.sa_flags = 0;

    if ( sigaction(SIGINT, &sa, NULL) < 0 )
        fatal("sigaction failed");
    if ( sigaction(SIGQUIT, &sa, NULL) < 0 )
        fatal("sigaction failed");

    if ( sigsetjmp(env, 1) ) printf("\n> ");

    while ( fgets(buf, INPUTSIZ, stdin) != NULL ){
        doshell(buf);
        printf("> ");
    }

    exit(0);
}

static void catcher(int sig)
{
    fflush(stdout);
    fflush(stdin);
    siglongjmp(env, 1);
}

void doshell(char *cmd)
{
    pid_t pid, wpid;
    struct sigaction sigi, osigi;
    struct sigaction sigq, osigq;


    sigemptyset(&sigi.sa_mask);
    sigi.sa_handler = nop;
    sigi.sa_flags = 0;

    if (sigaction(SIGINT, &sigi, &osigi) < 0 )
        fatal("sigaction failed");
    sigemptyset(&sigq.sa_mask);
    sigq.sa_handler = nop;
    sigq.sa_flags = 0;

    if ( sigaction(SIGQUIT, &sigq, &osigq) < 0 )
        fatal("sigaction failed");

    if ( (pid = fork()) < 0 ){
        error("fork failed");
        if ( sigaction(SIGINT, &osigi, NULL) < 0 )
            fatal("sigaction failed");
        if ( sigaction(SIGQUIT, &osigq, NULL) < 0  )
            fatal("sigaction failed");
        return ;
    }
    if ( pid == 0 ){
        execl("/bin/sh", "sh", "-c", cmd, NULL);
        fatal("exec failed");
    }

    while ( (wpid = waitpid(pid, NULL, 0)) != pid ) 
        if ( ( wpid == -1 ) && (errno != EINTR) )
            fatal("waitpid failed");
    if ( sigaction(SIGINT, &osigi, NULL) )
        fatal("sigaction failed");
    if ( sigaction(SIGQUIT, &osigq, NULL) )
        fatal("sigaction failed");
        //error("fork failed");
}

static void nop(int sig){}
