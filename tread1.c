/*
  Criação de processos em UNIX.

gcc -o fork fork.c
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main ()
{
  int retval, n;

  scanf("%d", &n);
   
  printf ("Ola, sou o processo %5d\n", getpid());

  for(int i = 0; i < n; i++){
        retval = fork ();
        if(retval == 0){
                printf ("[%d]-> sou %5d, filho de %5d\n", i, getpid(), getppid());
                exit(0);
        } else {
                wait(0);
        }

}


  exit (0) ;
}
