/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)MathL.c Nov 19  1:11:49 2022" */
/* Generated by XDS Oberon-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef MathL_H_
#include "MathL.h"
#endif
#define MathL_C_
#ifndef EXCEPTIONS_H_
#include "EXCEPTIONS.h"
#endif
#include "xMath.h"
#ifndef Strings_H_
#include "Strings.h"
#endif

extern struct X2C_MD_STR MathL_desc;
static EXCEPTIONS_ExceptionSource source;


static void raise0(X2C_INT16 n, const X2C_CHAR s[], X2C_CARD32 s_len)
{
   X2C_CHAR m[80];
   Strings_Concat("MathL.", 7ul, s, s_len, m, 80ul);
   EXCEPTIONS_RAISE(source, (X2C_CARD32)(X2C_CARD16)n, m, 80ul);
} /* end raise() */


extern X2C_LONGREAL MathL_sqrt(X2C_LONGREAL x)
{
   if (x<0.0) raise0(0, "sqrt: negative argument", 24ul);
   return X2C_sqrtl(x);
} /* end sqrt() */


extern X2C_LONGREAL MathL_exp(X2C_LONGREAL x)
{
   return X2C_expl(x);
} /* end exp() */


extern X2C_LONGREAL MathL_ln(X2C_LONGREAL x)
{
   if (x<=0.0) raise0(1, "ln: negative or zero argument", 30ul);
   return X2C_lnl(x);
} /* end ln() */


extern X2C_LONGREAL MathL_sin(X2C_LONGREAL x)
{
   return X2C_sinl(x);
} /* end sin() */


extern X2C_LONGREAL MathL_cos(X2C_LONGREAL x)
{
   return X2C_cosl(x);
} /* end cos() */


extern X2C_LONGREAL MathL_tan(X2C_LONGREAL x)
{
   return X2C_tanl(x);
} /* end tan() */


extern X2C_LONGREAL MathL_arcsin(X2C_LONGREAL x)
{
   if (fabs(x)>1.0) {
      raise0(2, "arcsin: argument is not in range -1.0 .. 1.0", 45ul);
   }
   return X2C_arcsinl(x);
} /* end arcsin() */


extern X2C_LONGREAL MathL_arccos(X2C_LONGREAL x)
{
   if (fabs(x)>1.0) {
      raise0(3, "arccos: argument is not in range -1.0 .. 1.0", 45ul);
   }
   return X2C_arccosl(x);
} /* end arccos() */


extern X2C_LONGREAL MathL_arctan(X2C_LONGREAL x)
{
   return X2C_arctanl(x);
} /* end arctan() */


extern X2C_LONGREAL MathL_power(X2C_LONGREAL base, X2C_LONGREAL exponent)
{
   if (base<=0.0) raise0(4, "power: negative or zero base", 29ul);
   return X2C_powl(base, exponent);
} /* end power() */


extern X2C_LONGREAL MathL_round(X2C_LONGREAL x)
{
   return X2C_floorl(x+0.5);
} /* end round() */


extern X2C_LONGREAL MathL_log(X2C_LONGREAL x, X2C_LONGREAL base)
{
   if (base<=0.0) raise0(5, "log: negative or zero base", 27ul);
   if (x<=0.0) raise0(6, "log: negative or zero argument", 31ul);
   return X2C_DIVL(X2C_lnl(x),X2C_lnl(base));
} /* end log() */


extern X2C_LONGREAL MathL_arctan2(X2C_LONGREAL x, X2C_LONGREAL y)
{
   if (x==0.0 && y==0.0) raise0(7, "arctan2: zero arguments", 24ul);
   return X2C_arctan2l(y, x);
} /* end arctan2() */


extern X2C_LONGREAL MathL_sinh(X2C_LONGREAL x)
{
   return X2C_sinhl(x);
} /* end sinh() */


extern X2C_LONGREAL MathL_cosh(X2C_LONGREAL x)
{
   return X2C_coshl(x);
} /* end cosh() */


extern X2C_LONGREAL MathL_tanh(X2C_LONGREAL x)
{
   return X2C_tanhl(x);
} /* end tanh() */


extern X2C_LONGREAL MathL_arcsinh(X2C_LONGREAL x)
{
   return X2C_arcsinhl(x);
} /* end arcsinh() */


extern X2C_LONGREAL MathL_arccosh(X2C_LONGREAL x)
{
   if (x<1.0) raise0(8, "arccosh: argument is less then 1.0", 35ul);
   return X2C_arccoshl(x);
} /* end arccosh() */


extern X2C_LONGREAL MathL_arctanh(X2C_LONGREAL x)
{
   if (x<0.0 || x>=1.0) {
      raise0(9, "arctanh: argument is not in range 0.0 .. 1.0", 45ul);
   }
   return X2C_arctanhl(x);
} /* end arctanh() */


static void * MathL_offs[] = {
   X2C_OFS_END
};
static X2C_PROC MathL_cmds[] = { 0 };
static X2C_CHAR * MathL_cnms[] = { 0 };
struct X2C_MD_STR MathL_desc = {
  0, 0, "MathL",MathL_offs,MathL_cmds,MathL_cnms,0
};

extern void MathL_BEGIN(void)
{
   static int MathL_init = 0;
   if (MathL_init) return;
   MathL_init = 1;
   Strings_BEGIN();
   EXCEPTIONS_BEGIN();
   X2C_MODULE(&MathL_desc);
   EXCEPTIONS_AllocateSource(&source);
}

