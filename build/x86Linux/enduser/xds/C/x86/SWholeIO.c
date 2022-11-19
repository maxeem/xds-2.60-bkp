/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)SWholeIO.c Nov 19  1:11:33 2022" */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef SWholeIO_H_
#include "SWholeIO.h"
#endif
#define SWholeIO_C_
#ifndef WholeIO_H_
#include "WholeIO.h"
#endif
#ifndef StdChans_H_
#include "StdChans.h"
#endif


extern void SWholeIO_ReadInt(X2C_INT32 * int0)
{
   WholeIO_ReadInt(StdChans_InChan(), int0);
} /* end ReadInt() */


extern void SWholeIO_WriteInt(X2C_INT32 int0, X2C_CARD32 width)
{
   WholeIO_WriteInt(StdChans_OutChan(), int0, width);
} /* end WriteInt() */


extern void SWholeIO_ReadCard(X2C_CARD32 * card)
{
   WholeIO_ReadCard(StdChans_InChan(), card);
} /* end ReadCard() */


extern void SWholeIO_WriteCard(X2C_CARD32 card, X2C_CARD32 width)
{
   WholeIO_WriteCard(StdChans_OutChan(), card, width);
} /* end WriteCard() */


extern void SWholeIO_BEGIN(void)
{
   static int SWholeIO_init = 0;
   if (SWholeIO_init) return;
   SWholeIO_init = 1;
   StdChans_BEGIN();
   WholeIO_BEGIN();
}

