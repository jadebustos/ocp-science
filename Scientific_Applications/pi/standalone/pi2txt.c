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

/*
  ./pi2txt.bin decimals pi_binary_file pi_txt_file
  where decimals is the number of decimals we want to read from pi_binary_file and write to pi_txt_file

 This software is licensed under GPLv2: http://www.gnu.org/licenses/gpl-2.0.html
 (c) 2013 Jose Angel de Bustos Perez <jadebustos@gmail.com>

*/

int main (int argc, char *argv[]) { /* begin function - main */

  long unsigned int decimals  = atol(argv[1]),
                    charsRead = 0;

  int chars,
      chunkSize = 100;

  char piStr[101];

  FILE *binfile,
       *txtfile;

  if ( argc != 4 || decimals < 1 ) {
    printf("Error with arguments.\n");
    exit (1);
  }

  /* opening files */
  binfile = fopen(argv[2],"r");
  txtfile = fopen(argv[3],"w");
  if ( binfile == NULL || txtfile == NULL ) {
    printf("There was a problem trying to open the files. Exiting.\n");
    exit(1);
  }

  /* reading and writing 3. to file */
  fread(piStr, sizeof(char), 2, binfile);
  piStr[2] = '\0';
  fprintf(txtfile, "%s", piStr);

  while ( charsRead < decimals ) { /* begin while - charsRead */
    if ( chunkSize > (decimals - charsRead) ) {
      chunkSize = decimals - charsRead;
    }
    chars = fread(piStr, sizeof(char), chunkSize, binfile);
    piStr[chars] = '\0';
    fprintf(txtfile, "%s", piStr);
    charsRead += chunkSize;
  } /* end while - charsRead */
  /* closing files */
  fclose(binfile);
  fclose(txtfile);

  return 0;
} /* end function - main */
