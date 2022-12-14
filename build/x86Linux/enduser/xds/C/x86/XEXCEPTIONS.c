/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)XEXCEPTIONS.c Nov 19  1:11:33 2022" */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef XEXCEPTIONS_H_
#include "XEXCEPTIONS.h"
#endif
#define XEXCEPTIONS_C_
#ifndef xmRTS_H_
#include "xmRTS.h"
#endif
#include "X2C.h"
#ifndef EXCEPTIONS_H_
#include "EXCEPTIONS.h"
#endif
#ifndef M2EXCEPTION_H_
#include "M2EXCEPTION.h"
#endif

static EXCEPTIONS_ExceptionSource rts;

static EXCEPTIONS_ExceptionSource assert;

static X2C_CARD32 XEXCEPTIONS_Fault = 14UL;


extern X2C_CARD8 XEXCEPTIONS_RTSException(void)
{
   X2C_CARD32 n;
   if (!EXCEPTIONS_IsExceptionalExecut()) {
      EXCEPTIONS_RAISE(rts, 14UL, "Not an exceptional execution", 29ul);
   }
   if (!EXCEPTIONS_IsCurrentSource(rts)) {
      EXCEPTIONS_RAISE(rts, 14UL, "Not an RTS exception source", 28ul);
   }
   n = EXCEPTIONS_CurrentNumber(rts);
   if (n<=14UL) EXCEPTIONS_RAISE(rts, 14UL, "Not an RTS exception", 21ul);
   if (n==X2C_guardException) return XEXCEPTIONS_typeGuardException;
   else if (n==X2C_noMemoryException) return XEXCEPTIONS_noMemoryException;
   else if (n==X2C_castError) return XEXCEPTIONS_typeCastException;
   else if (n==X2C_UserBreak) return XEXCEPTIONS_userBreakException;
   else if (n==X2C_unreachDLL) return XEXCEPTIONS_unreachableDLLExce;
   else return XEXCEPTIONS_internalRTSExcepti;
   return 0;
} /* end RTSException() */


extern X2C_BOOLEAN XEXCEPTIONS_IsRTSException(void)
{
   X2C_CARD32 n;
   if (EXCEPTIONS_IsCurrentSource(rts)) {
      n = EXCEPTIONS_CurrentNumber(rts);
      return n>14UL;
   }
   return 0;
} /* end IsRTSException() */


extern X2C_BOOLEAN XEXCEPTIONS_IsAssertException(void)
{
   return EXCEPTIONS_IsCurrentSource(assert);
} /* end IsAssertException() */


extern X2C_CARD32 XEXCEPTIONS_AssertCode(void)
{
   if (!EXCEPTIONS_IsExceptionalExecut()) {
      EXCEPTIONS_RAISE(rts, 14UL, "Not an exceptional execution", 29ul);
   }
   if (!EXCEPTIONS_IsCurrentSource(assert)) {
      EXCEPTIONS_RAISE(rts, 14UL, "Not an ASSERT exception source", 31ul);
   }
   return EXCEPTIONS_CurrentNumber(rts);
} /* end AssertCode() */


extern void XEXCEPTIONS_BEGIN(void)
{
   static int XEXCEPTIONS_init = 0;
   if (XEXCEPTIONS_init) return;
   XEXCEPTIONS_init = 1;
   M2EXCEPTION_BEGIN();
   EXCEPTIONS_BEGIN();
   rts = (EXCEPTIONS_ExceptionSource)X2C_rtsSource;
   assert = (EXCEPTIONS_ExceptionSource)X2C_assertSrc;
}

