//
// Created by gtuser on 8/14/18.
//
#include <helper.h>

void
main(int argc, char *argv[])
{
  int i;
  char *cmd = NULL;
  
  if (( cmd = strrchr(argv[0], '/')) == NULL )
    cmd = argv[0];
  else cmd ++;
  
  if ( argc == 1 ) {
    fprintf(stderr, "usage : %s args...\n", cmd);
    exit(1);
  }
  
  printf("argc = %d\n", argc);
  for(i = 0;i < argc;++ i) printf("argv[%d] = %s\n", i, argv[i]);
  exit(0);
}