#include <helper.h>

#define LISTSZ 20

struct list {
    struct list *next;
    int         val;
} list[LISTSZ];

struct list *head = NULL;

void handler(int);
void printlist(int);

void 
main(int argc, char *argv[])
{
    int i, n;
    struct sigaction sa;

    if ( argc == 2 ) n = atoi(argv[1]);
    else n = 0;

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    for ( i = LISTSZ - 1;i >= 0;-- i){
        list[i].val = i + 1;
        list[i].next = head;
        head = &list[i];
    }

    printlist(n);
    printlist(0);

    exit(0);
}

void 
printlist(int n)
{
    struct list *p;
    sigset_t s, os;

    sigemptyset(&s);
    sigaddset(&s, SIGINT);
    sigprocmask(SIG_BLOCK, &s, &os);


    for ( p = head;p != NULL; p = p->next ){
        printf("%d ", p->val);

        if ( p->val == n ) kill(getpid(), SIGINT);
    }

    sigprocmask(SIG_SETMASK, &os, NULL);
    printf("\n");
}

void handler(int sig)
{
    struct list *p, *op;

    op = NULL;
    for ( p = head;p != NULL; p = p->next ) {
        if ( p->val == 12 ) {
            if ( op != NULL ) op->next = p->next;
            else head = p->next;
            p->next = NULL;
            break;
        }
        op = p;
    }
}