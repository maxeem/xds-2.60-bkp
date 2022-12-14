/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)LowLong.c Nov 19  1:11:33 2022" */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef LowLong_H_
#include "LowLong.h"
#endif
#define LowLong_C_
#ifndef EXCEPTIONS_H_
#include "EXCEPTIONS.h"
#endif
#include "xMath.h"

static EXCEPTIONS_ExceptionSource source;


static void raise0(void)
{
   EXCEPTIONS_RAISE(source, 0UL, "LowLong.lowException", 21ul);
} /* end raise() */


extern X2C_INT32 LowLong_exponent(X2C_LONGREAL x)
{
   int i;
   x = X2C_frexp(x, &i);
   return i;
} /* end exponent() */


extern X2C_LONGREAL LowLong_fraction(X2C_LONGREAL x)
{
   int i;
   return X2C_frexp(x, &i);
} /* end fraction() */


extern X2C_LONGREAL LowLong_sign(X2C_LONGREAL x)
{
   if (x<0.0) return (-1.0);
   else if (x==0.0) return 0.0;
   else return 1.0;
   return 0;
} /* end sign() */


extern X2C_LONGREAL LowLong_succ(X2C_LONGREAL x)
{
   return x+LowLong_ulp(x);
} /* end succ() */


extern X2C_LONGREAL LowLong_ulp(X2C_LONGREAL x)
{
   X2C_CARD32 * pb;
   pb = (X2C_CARD32 *) &x;
   *pb |= 0x1UL;
   return fabs(x-LowLong_trunc(x, 51L));
} /* end ulp() */


extern X2C_LONGREAL LowLong_pred(X2C_LONGREAL x)
{
   return x-LowLong_ulp(x);
} /* end pred() */


extern X2C_LONGREAL LowLong_intpart(X2C_LONGREAL x)
{
   X2C_LONGREAL y;
   x = X2C_modf(x, &y);
   return y;
} /* end intpart() */


extern X2C_LONGREAL LowLong_fractpart(X2C_LONGREAL x)
{
   X2C_LONGREAL y;
   return X2C_modf(x, &y);
} /* end fractpart() */


extern X2C_LONGREAL LowLong_scale(X2C_LONGREAL x, X2C_INT32 n)
{
   return X2C_ldexp(x, n);
} /* end scale() */


extern X2C_LONGREAL LowLong_trunc(X2C_LONGREAL x, X2C_INT32 n)
{
   X2C_CARD32 * pb;
   if (n<=0L) raise0();
   if (n>=52L) return x;
   pb = (X2C_CARD32 *) &x;
   if (n<20L) {
      pb[0UL] = 0UL;
      pb[1UL] = pb[1UL]&~(X2C_SET(0U,(20L-n)-1L,32));
   }
   else pb[0UL] = pb[0UL]&~(X2C_SET(0U,(52L-n)-1L,32));
   return x;
} /* end trunc() */


extern X2C_LONGREAL LowLong_round(X2C_LONGREAL x, X2C_INT32 n)
{
   return LowLong_trunc(x, n);
} /* end round() */


extern X2C_LONGREAL LowLong_synthesize(X2C_INT32 n, X2C_LONGREAL x)
{
   return X2C_ldexp(x, n);
} /* end synthesize() */


extern void LowLong_setMode(X2C_CARD8 m)
{
   X2C_CARD32 r;
   r = X2C_controlfp((X2C_CARD32)m, (X2C_CARD32)0x3FUL);
} /* end setMode() */


extern X2C_CARD8 LowLong_currentMode(void)
{
   return (X2C_CARD8)X2C_controlfp(0UL, 0UL);
} /* end currentMode() */


extern X2C_BOOLEAN LowLong_IsLowException(void)
{
   return EXCEPTIONS_IsCurrentSource(source);
} /* end IsLowException() */


extern void LowLong_BEGIN(void)
{
   static int LowLong_init = 0;
   if (LowLong_init) return;
   LowLong_init = 1;
   if (sizeof(X2C_CARD8)!=1) X2C_ASSERT(0);
   EXCEPTIONS_BEGIN();
   EXCEPTIONS_AllocateSource(&source);
}

