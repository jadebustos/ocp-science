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
#include <gmp.h>
#include <stdlib.h>
#include <string.h>

/*
 One argument are required:
 	./chudnovsky-gmp.bin decimals
 If the number of arguments is different from one then pi is calculated only with 1000 precision decimals.

 The main goal of this software is to stress only one CPU.

 To compile:
   gcc -O2 -Wall -o chudnovsky-gmp.bin chudnovsky-gmp.c -lgmp

 The Multiprecision arithmetic library libgmp is required to compile.
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

  char *pistr,
       *end_decimals;

  FILE *data;

  /* integer gmp variables */
  mpz_t f6i,     /* (6*i)! */
        f3i,     /* /3*i)! */
        fi3,     /* (i!)^3 */
        sumnumi, /* (13591409 + 545140134 * i) */
        sumdeni; /* (-640320)^(3*k) */

  /* double gmp variables */
  mpf_t num,
        sumnum,
        sumden,
        sumterm,
        numi,
        pi;

  mp_exp_t exp;

  /* if args are supplied */
  if ( argc == 2 ) { /* begin if - argc */
    decimals = strtol(argv[1], &end_decimals, 10);
    precision_bits = (decimals * bits_digit) + 1;
    if ( decimals < 1 ) { /* begin if - decimals */
      printf("Error with decimals supplied, %lu.\n", decimals);
      exit(1);
    } /* end if - decimals */
  } /* end if - argc */

  mpf_set_default_prec(precision_bits); /* default precision in bits */

  /* allocation and initialitation variables */
/*  mpz_inits(f6i, f3i, fi3, sumnumi, sumdeni, NULL);
  mpf_inits(num, sumnum, sumden, sumterm, numi, pi, NULL); */

  mpz_init(f6i);
  mpz_init(f3i);
  mpz_init(fi3);
  mpz_init(sumnumi);
  mpz_init(sumdeni);
  mpf_init(num);
  mpf_init(sumnum);
  mpf_init(sumden);
  mpf_init(sumterm);
  mpf_init(pi);

  /* numerator */
  mpf_sqrt_ui(num, 10005);
  mpf_mul_ui(num, num, 426880);

  iters = (decimals/DIGITS_ITERATION) + 1;

  for(i=0;i<iters;i++) { /* begin for - i */
    triplei = 3*i;
    mpz_fac_ui(f6i, 6*i);   /* (6*i)! */
    mpz_fac_ui(f3i, triplei);   /* /3*i)! */
    mpz_fac_ui(fi3, i);     /* i! */
    mpz_pow_ui(fi3, fi3, 3); /* (i!)^3 */

    /* 13591409 + 545140134 * i */
    mpz_set_ui(sumnumi, 545140134);
    mpz_mul_ui(sumnumi, sumnumi, i);
    mpz_add_ui(sumnumi, sumnumi, 13591409);

    /* (-640320)^(3*k) */
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

    mpf_div(sumterm, sumnum, sumden);
    mpf_add(pi, pi, sumterm);
  } /* end for - i */

  /* final calcs */
  mpf_ui_div(pi, 1, pi);
  mpf_mul(pi, pi, num);

  pistr = mpf_get_str(NULL, &exp, 10, decimals, pi);

  data = fopen("gmp-pi.dat","w");
  
  /* opening a file to store pi */
  if ( data == NULL ) { /* begin if - data */
    printf("Error opening a file to store pi.\n");
    exit (1);
  } /* end if - data */

  fprintf(data,"%.1s.%s\n", pistr, pistr+1);

  /* closing file  */
  fclose(data);

  /* freeing gmp variables */
/*  mpz_clears(f6i, f3i, fi3, sumnumi, sumdeni, NULL);
  mpf_clears(num, sumnum, sumden, sumterm, numi, pi, NULL);*/

  mpz_clear(f6i);
  mpz_clear(f3i);
  mpz_clear(fi3);
  mpz_clear(sumnumi);
  mpz_clear(sumdeni);
  mpf_clear(num);
  mpf_clear(sumnum);
  mpf_clear(sumden);
  mpf_clear(sumterm);
  mpf_clear(numi);
  mpf_clear(pi);

  /* freeing pi */
  free(pistr);

  return 0;

} /* end function - main */
