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

#include "mytime.h"

/*
  Function to retrieve time as a human readable string 
*/

char * strTime( time_t *mytime) { /* begin function - strTime */

  struct tm *calendar;
  calendar = gmtime(mytime);

  return asctime(calendar);

} /* end functin - strTime */
