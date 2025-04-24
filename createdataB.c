/*--------------------------------------------------------------------*/
/* Produces a file called dataB with the student name, a nullbyte,    */
/* padding to overrun the stack, and the address of the instruction   */
/* in main to get a B, the latter of which will overwrite getName's   */
/* stored x30.                                                        */
/*                                                                    */
/* Authors: Maxwell Lloyd and Venus Dinari                            */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){
   FILE *psFile;
   unsigned long ulData;
   int i;

   psFile = fopen("dataB", "w");
   
   /* Writes the student's names */
   ulData = 0x0123456789abcdef;
   fwrite(&ulData, sizeof(unsigned long), 1, psFile);

   /* Writes the null byte at the end of the students names*/
   for (i = 0; i < 5; i++)
      putc('\0', psFile); /* Writes '00000000' */

   fclose(psFile);

   

   return 0;
}