/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)MathR.c Nov 19  1:11:49 2022" */
/* Generated by XDS Oberon-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef MathR_H_
#include "MathR.h"
#endif
#define MathR_C_
#ifndef EXCEPTIONS_H_
#include "EXCEPTIONS.h"
#endif
#include "xMath.h"
#ifndef Strings_H_
#include "Strings.h"
#endif

extern struct X2C_MD_STR MathR_desc;
static EXCEPTIONS_ExceptionSource source;


static void raise0(X2C_INT16 n, const X2C_CHAR s[], X2C_CARD32 s_len)
{
   X2C_CHAR m[80];
   Strings_Concat("MathR.", 7ul, s, s_len, m, 80ul);
   EXCEPTIONS_RAISE(source, (X2C_CARD32)(X2C_CARD16)n, m, 80ul);
} /* end raise() */


extern X2C_REAL MathR_sqrt(X2C_REAL x)
{
   if (x<0.0f) raise0(0, "sqrt: negative argument", 24ul);
   return X2C_sqrt(x);
} /* end sqrt() */


extern X2C_REAL MathR_exp(X2C_REAL x)
{
   return X2C_exp(x);
} /* end exp() */


extern X2C_REAL MathR_ln(X2C_REAL x)
{
   if (x<=0.0f) raise0(1, "ln: negative or zero argument", 30ul);
   return X2C_ln(x);
} /* end ln() */


extern X2C_REAL MathR_sin(X2C_REAL x)
{
   return X2C_sin(x);
} /* end sin() */


extern X2C_REAL MathR_cos(X2C_REAL x)
{
   return X2C_cos(x);
} /* end cos() */


extern X2C_REAL MathR_tan(X2C_REAL x)
{
   return X2C_tan(x);
} /* end tan() */


extern X2C_REAL MathR_arcsin(X2C_REAL x)
{
   if ((X2C_REAL)fabs(x)>1.0f) {
      raise0(2, "arcsin: argument is not in range -1.0 .. 1.0", 45ul);
   }
   return X2C_arcsin(x);
} /* end arcsin() */


extern X2C_REAL MathR_arccos(X2C_REAL x)
{
   if ((X2C_REAL)fabs(x)>1.0f) {
      raise0(3, "arccos: argument is not in range -1.0 .. 1.0", 45ul);
   }
   return X2C_arccos(x);
} /* end arccos() */


extern X2C_REAL MathR_arctan(X2C_REAL x)
{
   return X2C_arctan(x);
} /* end arctan() */


extern X2C_REAL MathR_power(X2C_REAL base, X2C_REAL exponent)
{
   if (base<=0.0f) raise0(4, "power: negative or zero base", 29ul);
   return X2C_pow(base, exponent);
} /* end power() */


extern X2C_REAL MathR_round(X2C_REAL x)
{
   return X2C_floor(x+0.5f);
} /* end round() */


extern X2C_REAL MathR_log(X2C_REAL x, X2C_REAL base)
{
   if (base<=0.0f) raise0(5, "log: negative or zero base", 27ul);
   if (x<=0.0f) raise0(6, "log: negative or zero argument", 31ul);
   return X2C_DIVR(X2C_ln(x),X2C_ln(base));
} /* end log() */


extern X2C_REAL MathR_arctan2(X2C_REAL x, X2C_REAL y)
{
   if (x==0.0f && y==0.0f) raise0(7, "arctan2: zero arguments", 24ul);
   return X2C_arctan2(y, x);
} /* end arctan2() */


extern X2C_REAL MathR_sinh(X2C_REAL x)
{
   return X2C_sinh(x);
} /* end sinh() */


extern X2C_REAL MathR_cosh(X2C_REAL x)
{
   return X2C_cosh(x);
} /* end cosh() */


extern X2C_REAL MathR_tanh(X2C_REAL x)
{
   return X2C_tanh(x);
} /* end tanh() */


extern X2C_REAL MathR_arcsinh(X2C_REAL x)
{
   return X2C_arcsinh(x);
} /* end arcsinh() */


extern X2C_REAL MathR_arccosh(X2C_REAL x)
{
   if (x<1.0f) raise0(8, "arccosh: argument is less then 1.0", 35ul);
   return X2C_arccosh(x);
} /* end arccosh() */


extern X2C_REAL MathR_arctanh(X2C_REAL x)
{
   if (x<0.0f || x>=1.0f) {
      raise0(9, "arctanh: argument is not in range 0.0 .. 1.0", 45ul);
   }
   return X2C_arctanh(x);
} /* end arctanh() */


static void * MathR_offs[] = {
   X2C_OFS_END
};
static X2C_PROC MathR_cmds[] = { 0 };
static X2C_CHAR * MathR_cnms[] = { 0 };
struct X2C_MD_STR MathR_desc = {
  0, 0, "MathR",MathR_offs,MathR_cmds,MathR_cnms,0
};

extern void MathR_BEGIN(void)
{
   static int MathR_init = 0;
   if (MathR_init) return;
   MathR_init = 1;
   Strings_BEGIN();
   EXCEPTIONS_BEGIN();
   X2C_MODULE(&MathR_desc);
   EXCEPTIONS_AllocateSource(&source);
}

