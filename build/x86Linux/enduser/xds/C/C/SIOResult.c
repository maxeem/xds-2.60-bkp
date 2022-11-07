/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)SIOResult.c Nov  7 22:55:49 2022" */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef SIOResult_H_
#include "SIOResult.h"
#endif
#define SIOResult_C_
#ifndef IOConsts_H_
#include "IOConsts.h"
#endif
#ifndef IOChan_H_
#include "IOChan.h"
#endif
#ifndef StdChans_H_
#include "StdChans.h"
#endif


extern X2C_CARD8 SIOResult_ReadResult(void)
{
   return IOChan_ReadResult(StdChans_InChan());
} /* end ReadResult() */


extern void SIOResult_BEGIN(void)
{
   static int SIOResult_init = 0;
   if (SIOResult_init) return;
   SIOResult_init = 1;
   StdChans_BEGIN();
   IOChan_BEGIN();
   IOConsts_BEGIN();
}

