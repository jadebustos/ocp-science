/*
  This software is licensed under GPLv2: http://www.gnu.org/licenses/gpl-2.0.html
  (c) 2013 Jose Angel de Bustos Perez <jadebustos@gmail.com>
*/

/*
  The following are deliberately forbidden:
        - Attempt World domination
        - Using this software as compiling massive weapon
        - Translating into Klingon
        - Ask for /home nationalisms
        - Reverse spelling of this source code
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <omp.h>

/*
 Two arguments are required:
 	./pi-mid-point-rule.bin threads iterations
 If the number of arguments is different from two then only one thread is used and pi is calculated once.

 The main goal of this software is to stress as many cores as you want.

 To compile:
   gcc -O2 -Wall -o pi-mid-point-rule.bin pi-mid-point-rule.c -fopenmp

 The GCC OpenMP (GOMP) support library libgomp1 is required to compile.
*/

/* 

            (( 1                        n
           (                           ___
           |      1               1    \        1
  pi = 4 * |  --------- dx ~ 4 * --- *  \  ----------- 
           |   1 + x^2            n     /   1 + x_i^2
           )                           /___
         )) 0                           i=0

         i - (1/2)
  x_i = -----------
            n

*/

int main (int argc, char *argv[]) { /* begin function main */

  unsigned int i = 0;

  int    threads = 1,
         j = 0,
         iterations = 1;

  long double x = .0,
              dx = 1./UINT_MAX,
              pi = .0;

  if ( argc > 2 ) { /* begin if */
    threads = atoi(argv[1]);
    iterations = atoi(argv[2]);
  } /* end if */

  for(j=0;j<iterations;j++) { /* begin for - j */
    #pragma omp parallel num_threads(threads) private(x)
    { /* begin - pragma parallel */
      #pragma omp for reduction(+: pi) schedule(dynamic, threads)
      for(i=1;i<UINT_MAX;i++) { /* begin for - i */
        x = (i - .5) * dx;
        pi = pi + 1./(1+x*x);      
      } /* end for - i */
      #pragma omp barrier
      #pragma omp sections
      { /* begin section */
        pi *= 4.*dx;
      } /* end section */
    } /* end - pragma parallel */

  } /* end for - j */

  printf("pi: %.80Lf\n", pi);
  return 0;

} /* end function main */
