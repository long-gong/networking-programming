//
// Created by gtuser on 8/14/18.
//

#include <helper.h>

void
main(int argc, char *argv[])
{
  int i;
  printf("argc = %d\n", argc);
  for ( i = 0;i < argc;++ i)
  {
    printf("argv[%d] = %s\n", i, argv[i]);
  }
  exit(0);
}