#include <helper.h>


#define LISTSZ 20

struct list {
    struct list *next;
    int         val;
} list[LISTSZ];

struct list *head = NULL;

void handler(int);
void printlist(int);

void main(int argc, char *argv[])
{
    int i,n;
    if (argc == 2) n = atoi(argv[1]);
    else n = 0;

    sigset(SIGINT, handler);

    for ( i = LISTSZ;i >= 0;-- i) {
        list[i].val = i + 1;
        list[i].next = head;
        head = &list[i];
    }

    printlist(n);


    printlist(0);


    exit(0);
}


void printlist(int n)
{
    struct list *p;

    //
    sighold(SIGINT);
    for (p = head; p != NULL;p = p->next){
        printf("%d ", p->val);
        if ( p->val == n ) kill(getpid(), SIGINT);
    }

    sigrelse(SIGINT);
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