//
// Created by gtuser on 8/14/18.
//

#include <helper.h>


extern char **environ;

void
main()
{
  int i;
  for (i = 0;environ[i];++i) printf("%s\n", environ[i]);
  
  exit(0);
}