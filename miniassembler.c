/*--------------------------------------------------------------------*/
/* miniassembler.c                                                    */
/* Author: Bob Dondero, Donna Gabai                                   */
/*--------------------------------------------------------------------*/

#include "miniassembler.h"
#include <assert.h>
#include <stddef.h>

/*--------------------------------------------------------------------*/
/* Modify *puiDest in place,
   setting uiNumBits starting at uiDestStartBit (where 0 indicates
   the least significant bit) with bits taken from uiSrc,
   starting at uiSrcStartBit.
   uiSrcStartBit indicates the rightmost bit in the field.
   setField sets the appropriate bits in *puiDest to 1.
   setField never unsets any bits in *puiDest.                        */
static void setField(unsigned int uiSrc, unsigned int uiSrcStartBit,
                     unsigned int *puiDest, unsigned int uiDestStartBit,
                     unsigned int uiNumBits)
{
   unsigned int uiOnes;
   unsigned int i;
   uiOnes = 0;

   /* create a binary string of 1s that is uiNumBits long */
   for(i = 0; i < uiNumBits; i++){
      uiOnes = (uiOnes << 1) | 1;
   }

   /* Set uiOnes to the correct position to get correct uiSrc bits */
   uiOnes = uiOnes << uiSrcStartBit;

   /* Isolate relavent bits in uiSrc */
   uiSrc = uiSrc & uiOnes;

   /* 0 out the value we went to the right*/
   uiSrc = uiSrc >> uiSrcStartBit;

   /* set uiSrc to correct position */
   uiSrc = uiSrc << uiDestStartBit;

   /* Add on bits from source to destination */
   *puiDest = *puiDest | uiSrc;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_mov(unsigned int uiReg, int iImmed)
{
   unsigned int uiInstr;
    
   /* Base instruction code */
   uiInstr = 0x52800000;

  /* register to be inserted in instruction */
   setField(uiReg, 0, &uiInstr, 0, 5);


   setField(iImmed, 0, &uiInstr, 5, 16); /* set iImmed */

   return uiInstr;


}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_movX(unsigned int uiReg, int iImmed)
{
   unsigned int uiInstr;
    
   /* Base instruction code */
   uiInstr = 0xD2800000;

  /* register to be inserted in instruction */
   setField(uiReg, 0, &uiInstr, 0, 5);


   setField(iImmed, 0, &uiInstr, 5, 16); /* set iImmed */

   return uiInstr;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_adr(unsigned int uiReg, unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr;
   unsigned int uiDisp;

   /* Base Instruction Code */
   uiInstr = 0x10000000;

   /* register to be inserted in instruction */
   setField(uiReg, 0, &uiInstr, 0, 5);

   /* displacement to be split into immlo and immhi and inserted */
   uiDisp = (unsigned int)(ulAddr - ulAddrOfThisInstr);

   setField(uiDisp, 0, &uiInstr, 29, 2); /* set immlo */
   setField(uiDisp, 2, &uiInstr, 5, 19); /* set immhi */

   return uiInstr;
}

/*--------------------------------------------------------------------*/

   unsigned int MiniAssembler_strb(unsigned int uiFromReg,
   unsigned int uiToReg)
{
   unsigned int uiInstr;
   
   /* Base instruction code */
   uiInstr= 0x39000000;

   /* dest register to be inserted in instruction */
   setField(uiFromReg, 0, &uiInstr, 0, 5);

   /* source register to be inserted in instruction */
   setField(uiToReg, 0, &uiInstr, 5, 5);


   return uiInstr;

}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_b(unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr;
   int uiDisp;

   /* Base instruction code */
   uiInstr= 0x14000000;

   /* displacement */
   uiDisp = (int)((long)ulAddr - (long)ulAddrOfThisInstr);

   /* Right shift 2 so that the assembly convert it a multiple of 4, not us */
   uiDisp = uiDisp >> 2;

   setField((unsigned int)uiDisp, 0, &uiInstr, 0, 26); /* set imm26 */

   return uiInstr;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_bl(unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr;
   int uiDisp;

   /* Base instruction code */
   uiInstr= 0x94000000;

   /* displacement */
   uiDisp = (int)((long)ulAddr - (long)ulAddrOfThisInstr);

   /* Right shift 2 so that the assembly convert it a multiple of 4, not us */
   uiDisp = uiDisp >> 2;

   setField((unsigned int)uiDisp, 0, &uiInstr, 0, 26); /* set imm26 */

   return uiInstr;
}
