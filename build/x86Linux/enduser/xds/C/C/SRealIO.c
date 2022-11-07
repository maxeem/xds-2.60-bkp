/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)SRealIO.c Nov  7 22:55:49 2022" */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef SRealIO_H_
#include "SRealIO.h"
#endif
#define SRealIO_C_
#ifndef RealIO_H_
#include "RealIO.h"
#endif
#ifndef StdChans_H_
#include "StdChans.h"
#endif


extern void SRealIO_ReadReal(X2C_REAL * real)
{
   RealIO_ReadReal(StdChans_InChan(), real);
} /* end ReadReal() */


extern void SRealIO_WriteFloat(X2C_REAL real, X2C_CARD32 sigFigs,
                X2C_CARD32 width)
{
   RealIO_WriteFloat(StdChans_OutChan(), real, sigFigs, width);
} /* end WriteFloat() */


extern void SRealIO_WriteEng(X2C_REAL real, X2C_CARD32 sigFigs,
                X2C_CARD32 width)
{
   RealIO_WriteEng(StdChans_OutChan(), real, sigFigs, width);
} /* end WriteEng() */


extern void SRealIO_WriteFixed(X2C_REAL real, X2C_INT32 place,
                X2C_CARD32 width)
{
   RealIO_WriteFixed(StdChans_OutChan(), real, place, width);
} /* end WriteFixed() */


extern void SRealIO_WriteReal(X2C_REAL real, X2C_CARD32 width)
{
   RealIO_WriteReal(StdChans_OutChan(), real, width);
} /* end WriteReal() */


extern void SRealIO_BEGIN(void)
{
   static int SRealIO_init = 0;
   if (SRealIO_init) return;
   SRealIO_init = 1;
   StdChans_BEGIN();
   RealIO_BEGIN();
}

