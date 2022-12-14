/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)LongComplexMath.c Nov 19  1:11:33 2022" */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef LongComplexMath_H_
#include "LongComplexMath.h"
#endif
#define LongComplexMath_C_
#ifndef EXCEPTIONS_H_
#include "EXCEPTIONS.h"
#endif
#ifndef LongMath_H_
#include "LongMath.h"
#endif

X2C_LONGCOMPLEX LongComplexMath_i = {0.0,1.0};
X2C_LONGCOMPLEX LongComplexMath_one = {1.0,0.0};
X2C_LONGCOMPLEX LongComplexMath_zero = {0.0,0.0};
#define LongComplexMath_name "LongComplexMath."

#define LongComplexMath_pi 3.1415926535898

static EXCEPTIONS_ExceptionSource source;


extern X2C_LONGREAL LongComplexMath_abs(X2C_LONGCOMPLEX z)
{
   return LongMath_sqrt(z.re*z.re+z.im*z.im);
} /* end abs() */


extern X2C_LONGREAL LongComplexMath_arg(X2C_LONGCOMPLEX z)
{
   X2C_LONGREAL im;
   X2C_LONGREAL re;
   re = z.re;
   im = z.im;
   if (re>0.0) return LongMath_arctan(X2C_DIVL(im,re));
   if (re<0.0) {
      if (z.im>=0.0) return LongMath_arctan(X2C_DIVL(im,re))+3.1415926535898;
      else return LongMath_arctan(X2C_DIVL(im,re))-3.1415926535898;
   }
   if (im==0.0) {
      EXCEPTIONS_RAISE(source, 0UL, "LongComplexMath.arg: zero argument",
                35ul);
   }
   else if (im>0.0) return 1.5707963267949;
   else return (-1.5707963267949);
   X2C_TRAP(X2C_RETURN_TRAP);
   return 0;
} /* end arg() */


extern X2C_LONGCOMPLEX LongComplexMath_conj(X2C_LONGCOMPLEX z)
{
   X2C_LONGCOMPLEX tmp;
   return (tmp.re = z.re,tmp.im = -z.im,tmp);
} /* end conj() */

static X2C_LONGCOMPLEX _cnst = {0.0,0.0};

extern X2C_LONGCOMPLEX LongComplexMath_power(X2C_LONGCOMPLEX base,
                X2C_LONGREAL exponent)
{
   X2C_LONGREAL y;
   X2C_LONGREAL x;
   X2C_LONGCOMPLEX tmp;
   if (CPLX_LCMP(base,_cnst)==0 && exponent>0.0) return _cnst;
   x = LongMath_power(LongComplexMath_abs(base), exponent);
   y = exponent*LongComplexMath_arg(base);
   return (tmp.re = x*LongMath_cos(y),tmp.im = x*LongMath_sin(y),tmp);
} /* end power() */


extern X2C_LONGCOMPLEX LongComplexMath_sqrt(X2C_LONGCOMPLEX z)
{
   X2C_LONGREAL y;
   X2C_LONGREAL x;
   X2C_LONGCOMPLEX tmp;
   if (CPLX_LCMP(z,_cnst)==0) return z;
   x = LongMath_sqrt(LongComplexMath_abs(z));
   y = X2C_DIVL(LongComplexMath_arg(z),2.0);
   return (tmp.re = x*LongMath_cos(y),tmp.im = x*LongMath_sin(y),tmp);
} /* end sqrt() */


extern X2C_LONGCOMPLEX LongComplexMath_exp(X2C_LONGCOMPLEX z)
{
   X2C_LONGREAL x;
   X2C_LONGCOMPLEX tmp;
   x = LongMath_exp(z.re);
   return (tmp.re = x*LongMath_cos(z.im),tmp.im = x*LongMath_sin(z.im),tmp);
} /* end exp() */


extern X2C_LONGCOMPLEX LongComplexMath_ln(X2C_LONGCOMPLEX z)
{
   X2C_LONGCOMPLEX tmp;
   return (tmp.re = LongMath_ln(LongComplexMath_abs(z)),
                tmp.im = LongComplexMath_arg(z),tmp);
} /* end ln() */


extern X2C_LONGCOMPLEX LongComplexMath_sin(X2C_LONGCOMPLEX z)
{
   X2C_LONGREAL emb;
   X2C_LONGREAL eb;
   X2C_LONGCOMPLEX tmp;
   eb = LongMath_exp(z.im);
   emb = X2C_DIVL(1.0,eb);
   return (tmp.re = X2C_DIVL(LongMath_sin(z.re)*(emb+eb),2.0),
                tmp.im = -(0.5*LongMath_cos(z.re)*(emb-eb)),tmp);
} /* end sin() */


extern X2C_LONGCOMPLEX LongComplexMath_cos(X2C_LONGCOMPLEX z)
{
   X2C_LONGREAL emb;
   X2C_LONGREAL eb;
   X2C_LONGCOMPLEX tmp;
   eb = LongMath_exp(z.im);
   emb = X2C_DIVL(1.0,eb);
   return (tmp.re = X2C_DIVL(LongMath_cos(z.re)*(emb+eb),2.0),
                tmp.im = X2C_DIVL(LongMath_sin(z.re)*(emb-eb),2.0),tmp);
} /* end cos() */


extern X2C_LONGCOMPLEX LongComplexMath_tan(X2C_LONGCOMPLEX z)
{
   X2C_LONGREAL y;
   X2C_LONGREAL x;
   X2C_LONGREAL emb;
   X2C_LONGREAL eb;
   X2C_LONGREAL cos0;
   X2C_LONGREAL sin0;
   X2C_LONGCOMPLEX tmp;
   if (CPLX_LCMP(z,_cnst)==0) return _cnst;
   sin0 = LongMath_sin(z.re);
   cos0 = LongMath_cos(z.re);
   eb = LongMath_exp(z.im);
   emb = X2C_DIVL(1.0,eb);
   x = cos0*(emb+eb);
   y = sin0*(emb-eb);
   x = x*x+y*y;
   return (tmp.re = X2C_DIVL(4.0*sin0*cos0,x),
                tmp.im = X2C_DIVL((eb-emb)*(emb+eb),x),tmp);
} /* end tan() */


extern X2C_LONGCOMPLEX LongComplexMath_arcsin(X2C_LONGCOMPLEX z)
{
   X2C_LONGCOMPLEX c;
   X2C_LONGREAL rp;
   X2C_LONGREAL phi;
   X2C_LONGCOMPLEX tmp;
   c = (tmp.re = (1.0-z.re*z.re)+z.im*z.im,tmp.im = -(2.0*z.re*z.im),tmp);
   if (CPLX_LCMP(c,_cnst)==0) phi = 0.0;
   else phi = X2C_DIVL(LongComplexMath_arg(c),2.0);
   rp = LongMath_sqrt(LongComplexMath_abs(c));
   c = (tmp.re = -z.im+rp*LongMath_cos(phi),
                tmp.im = z.re+rp*LongMath_sin(phi),tmp);
   return (tmp.re = LongComplexMath_arg(c),
                tmp.im = -LongMath_ln(LongComplexMath_abs(c)),tmp);
} /* end arcsin() */


extern X2C_LONGCOMPLEX LongComplexMath_arccos(X2C_LONGCOMPLEX z)
{
   X2C_LONGCOMPLEX c;
   X2C_LONGREAL rp;
   X2C_LONGREAL phi;
   X2C_LONGCOMPLEX tmp;
   c = (tmp.re = (1.0-z.re*z.re)+z.im*z.im,tmp.im = -(2.0*z.re*z.im),tmp);
   if (CPLX_LCMP(c,_cnst)==0) phi = 0.0;
   else phi = X2C_DIVL(LongComplexMath_arg(c),2.0);
   rp = LongMath_sqrt(LongComplexMath_abs(c));
   c = (tmp.re = z.re-rp*LongMath_sin(phi),
                tmp.im = z.im+rp*LongMath_cos(phi),tmp);
   return (tmp.re = LongComplexMath_arg(c),
                tmp.im = -LongMath_ln(LongComplexMath_abs(c)),tmp);
} /* end arccos() */


extern X2C_LONGCOMPLEX LongComplexMath_arctan(X2C_LONGCOMPLEX z)
{
   X2C_LONGREAL den;
   X2C_LONGREAL a2;
   X2C_LONGREAL opb;
   X2C_LONGCOMPLEX c;
   X2C_LONGCOMPLEX tmp;
   opb = 1.0+z.im;
   a2 = z.re*z.re;
   den = opb*opb+a2;
   c = (tmp.re = X2C_DIVL((1.0-z.im)*opb-a2,den),tmp.im = X2C_DIVL(2.0*z.re,
                den),tmp);
   return (tmp.re = X2C_DIVL(LongComplexMath_arg(c),2.0),
                tmp.im = -(X2C_DIVL(LongMath_ln(LongComplexMath_abs(c)),
                2.0)),tmp);
} /* end arctan() */


extern X2C_LONGCOMPLEX LongComplexMath_polarToComplex(X2C_LONGREAL abs0,
                X2C_LONGREAL arg)
{
   X2C_LONGCOMPLEX tmp;
   return (tmp.re = abs0*LongMath_cos(arg),tmp.im = abs0*LongMath_sin(arg),
                tmp);
} /* end polarToComplex() */


extern X2C_LONGCOMPLEX LongComplexMath_scalarMult(X2C_LONGREAL scalar,
                X2C_LONGCOMPLEX z)
{
   X2C_LONGCOMPLEX tmp;
   return (tmp.re = z.re*scalar,tmp.im = z.im*scalar,tmp);
} /* end scalarMult() */


extern X2C_BOOLEAN LongComplexMath_IsCMathExcepti(void)
{
   return EXCEPTIONS_IsCurrentSource(source);
} /* end IsCMathException() */


extern void LongComplexMath_BEGIN(void)
{
   static int LongComplexMath_init = 0;
   if (LongComplexMath_init) return;
   LongComplexMath_init = 1;
   LongMath_BEGIN();
   EXCEPTIONS_BEGIN();
   EXCEPTIONS_AllocateSource(&source);
}

