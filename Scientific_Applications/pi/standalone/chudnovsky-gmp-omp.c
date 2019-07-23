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
#include <string.h>
#include <time.h>
#include <gmp.h>
#include <omp.h>

#include "mytime.h"

/*
 Two arguments are required:
 	./chudnovsky-gmp-omp.bin threads decimals
 If the number of arguments is different from two then only one thread is used and pi is calculated only with 1000 precision decimals.

 The main goal of this software is to stress as many cores as you want.

 To compile:
   gcc -O2 -Wall -o chudnovsky-gmp-omp.bin chudnovsky-gmp-omp.c -lgmp -fopenmp

 The Multiprecision arithmetic library libgmp is required to compile.
 The GCC OpenMP (GOMP) support library libgomp1 is required to compile.
*/

/*
 The Chudnovsky Algorithm:
                                _____
                     426880 * \/10005
  pi = ---------------------------------------------
         _inf_
         \     (6*i)! * (13591409 + 545140134 * i)
          \    -----------------------------------
          /     (3*i)! * (i!)^3 * (-640320)^(3*i)
         /____
          i=0

                          num
  pi = ---------------------------------------------
         _inf_
         \     f6i * sumnumi
          \    -----------------------------------
          /     f3i * fi3 * sumdeni
         /____
          i=0
*/

/* decimal digits per iteration that algorithm generates in each iteration */
#define DIGITS_ITERATION 14.1816474627254776555

int main (int argc, char *argv[]) { /* begin function - main */

  /* bits per decimal digit, log2(10) */
  double bits_digit = 3.3219280948873626; 
  
  unsigned long int i              = 0,
                    iters          = 0,
                    triplei        = 0,
                    decimals       = 1000, 
	            precision_bits = (decimals * bits_digit) + 1;

  int  threads = 1;

  char *pistr,        /* to store pi as a string */
       *end_decimals;

  /* starting and ending dates */
  time_t startTime,
         endTime;

  FILE *data;

  mpf_t pi,  /* pi aproximation */
        num; /* numerator */

   /* time variables */ 
  clock_t clock_timer;
  double wall_timer;

  /* if args are supplied */
  if ( argc == 3 ) { /* begin if - argc */
    threads  = atoi(argv[1]);
    decimals = strtol(argv[2], &end_decimals, 10);
    precision_bits = (decimals * bits_digit) + 1;
    if ( decimals < 1 ) { /* begin if - decimals */
      printf("Error with decimals supplied, %lu.\n", decimals);
      exit(1);
    } /* end if - decimals */
  } /* end if - argc */

  mpf_set_default_prec(precision_bits); /* default precision in bits */

  /* allocation and initialitation, mpf_inits does not work on RHEL 6.x due to gmp version */
    mpf_init(pi);
    mpf_init(num);

  /* pi */
  mpf_set_ui(pi, 0);

  /* numerator */
  mpf_sqrt_ui(num, 10005);
  mpf_mul_ui(num, num, 426880);

  iters = (decimals/DIGITS_ITERATION) + 1;

  /* getting start time */
  startTime = time(NULL);

  #pragma omp parallel num_threads(threads) private(triplei, i) shared(pi, num, startTime, endTime)
  { /* begin - pragma parallel */
    /* integer gmp variables */
    mpz_t f6i,     /* (6*i)! */
          f3i,     /* /3*i)! */
          fi3,     /* (i!)^3 */
          sumnumi, /* (13591409 + 545140134 * i) */
          sumdeni; /* (-640320)^(3*k) */

    /* double gmp variables */
    mpf_t sumnum,
          sumden,
          sumterm,
          sumterm_tmp,
          numi;

    mp_exp_t exp;

    /* allocation and initialitation, mpf_inits does not work on RHEL 6.x due to gmp version */
    mpz_init(f6i);
    mpz_init(f3i);
    mpz_init(fi3);
    mpz_init(sumnumi);
    mpz_init(sumdeni);
    mpf_init(sumnum);
    mpf_init(sumden);
    mpf_init(sumterm);
    mpf_init(sumterm_tmp);
    mpf_init(numi);
    
    mpf_set_ui(sumterm, 0);

    /* init time */    
    clock_timer = clock();
    wall_timer = omp_get_wtime();

    #pragma omp for ordered
    for(i=0;i<iters;i++) { /* begin for - i */
      triplei = 3*i;
      mpz_fac_ui(f6i, 6*i);       /* (6*i)! */
      mpz_fac_ui(f3i, triplei);   /* /3*i)! */
      mpz_fac_ui(fi3, i);         /* i! */
      mpz_pow_ui(fi3, fi3, 3);    /* (i!)^3 */

      /* 13591409 + 545140134 * i */
      mpz_set_ui(sumnumi, 545140134);
      mpz_mul_ui(sumnumi, sumnumi, i);
      mpz_add_ui(sumnumi, sumnumi, 13591409);

      /* (-640320)^(3*i) */
      mpz_ui_pow_ui(sumdeni, 640320, triplei);
 
      if ( (triplei&1) == 1 ) {
        mpz_neg(sumdeni, sumdeni);
      }

      /* sumnumi */
      mpz_mul(sumnumi, sumnumi, f6i);

      /* sumdeni */
      mpz_mul(sumdeni, sumdeni, fi3);
      mpz_mul(sumdeni, sumdeni, f3i);

      /* sumterm */
      mpf_set_z(sumnum, sumnumi);
      mpf_set_z(sumden, sumdeni);

      mpf_div(sumterm_tmp, sumnum, sumden);
      mpf_add(sumterm, sumterm, sumterm_tmp);

    } /* end for - i */

    #pragma omp critical
    { /* begin - pragma critical */
      mpf_add(pi, pi, sumterm);
    } /* end - pragma critical */
    #pragma omp barrier
    #pragma omp single
    { /* begin - pragma single */
      /* final calcs */
      mpf_ui_div(pi, 1, pi);
      mpf_mul(pi, pi, num);

      /* getting end time */
      endTime = time(NULL);

      /* converting pi to string */    
      pistr = mpf_get_str(NULL, &exp, 10, decimals, pi);

      /* opening a file to store stats about pi computation */
      data = fopen("omp-gmp-pi.info","w");
  
      if ( data == NULL ) { /* begin if - data */
        printf("Error opening a file to store stats about pi computation.\n");
        exit (1);
      } /* end if - data */
      
      fprintf(data,"Threads: %d\n", threads);
      fprintf(data,"Decimals: %lu\n", decimals);
      fprintf(data,"Precision bits: %lu\n", precision_bits);
      fprintf(data,"Iterations: %lu\n", iters);
      fprintf(data,"Total time (sec): %e\n", (double) (clock() - clock_timer)/CLOCKS_PER_SEC);
    } /* end -pragma single  */
    # pragma omp barrier
    # pragma omp critical
    { /* begin - pragma critical */
      int tid = omp_get_thread_num();
      fprintf(data,"Processor time (sec) thread %d: %e\n", tid, omp_get_wtime() - wall_timer);
    } /* end - pragma critical */
    # pragma omp barrier
    # pragma omp single
    { /* begin - pragma single */ 
      fprintf(data,"Start time: %s", strTime(&startTime));
      fprintf(data,"End time: %s", strTime(&endTime));
      /* closing file */
      fclose(data);

      /* opening a file to store pi */
      data = fopen("omp-gmp-pi.dat","w");
  
      if ( data == NULL ) { /* begin if - data */
        printf("Error opening a file to store pi.\n");
        exit (1);
      } /* end if - data */

      fwrite(pistr, sizeof(char), 1, data);
      fputc('.', data);
      fwrite(pistr + 1, sizeof(char), decimals - 1, data);
      
      /* closing file  */
      fclose(data);
    } /* end - pragma single */
    /* freeing gmp variables, mpf_clears does not work on RHEL 6.x due to gmp version */
    mpz_clear(f6i);
    mpz_clear(f3i);
    mpz_clear(fi3);
    mpz_clear(sumnumi);
    mpz_clear(sumdeni);
    mpf_clear(sumnum);
    mpf_clear(sumden);
    mpf_clear(sumterm);
    mpf_clear(sumterm_tmp);
    mpf_clear(numi);

  } /* end - pragma parallel */

  /* freeing gmp variables, mpf_clears does not work on RHEL 6.x due to gmp version */
  mpf_clear(pi);
  mpf_clear(num);

  /* freeing pi */
  free(pistr);

  return 0;

} /* end function - main */
