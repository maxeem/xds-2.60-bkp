/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)GeneralUserExceptions.c Nov 19  1:11:49 2022" */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef GeneralUserExceptions_H_
#include "GeneralUserExceptions.h"
#endif
#define GeneralUserExceptions_C_
#ifndef EXCEPTIONS_H_
#include "EXCEPTIONS.h"
#endif

static X2C_CARD32 GeneralUserExceptions_Fault = 1UL;

static EXCEPTIONS_ExceptionSource Source;


extern void GeneralUserExceptions_RaiseGen(X2C_CARD8 exception,
                X2C_CHAR text[], X2C_CARD32 text_len)
{
   X2C_PCOPY((void **)&text,text_len);
   EXCEPTIONS_RAISE(Source, (X2C_CARD32)exception, text, text_len);
   X2C_PFREE(text);
} /* end RaiseGeneralException() */


extern X2C_BOOLEAN GeneralUserExceptions_IsGenera(void)
{
   return EXCEPTIONS_IsCurrentSource(Source);
} /* end IsGeneralException() */


extern X2C_CARD8 GeneralUserExceptions_General0(void)
{
   X2C_CARD32 n;
   if (!EXCEPTIONS_IsExceptionalExecut()) {
      EXCEPTIONS_RAISE(Source, 1UL, "No current exception", 21ul);
   }
   if (!EXCEPTIONS_IsCurrentSource(Source)) {
      EXCEPTIONS_RAISE(Source, 1UL, "Not general user exception source",
                34ul);
   }
   n = EXCEPTIONS_CurrentNumber(Source);
   return (X2C_CARD8)n;
} /* end GeneralException() */


extern void GeneralUserExceptions_BEGIN(void)
{
   static int GeneralUserExceptions_init = 0;
   if (GeneralUserExceptions_init) return;
   GeneralUserExceptions_init = 1;
   EXCEPTIONS_BEGIN();
   EXCEPTIONS_AllocateSource(&Source);
}

