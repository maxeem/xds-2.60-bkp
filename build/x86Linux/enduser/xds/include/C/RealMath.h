/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#ifndef RealMath_H_
#define RealMath_H_
#ifndef X2C_H_
#include "X2C.h"
#endif

#define RealMath_pi 3.141592

#define RealMath_exp1 2.718281

extern X2C_REAL RealMath_sqrt(X2C_REAL);

extern X2C_REAL RealMath_exp(X2C_REAL);

extern X2C_REAL RealMath_ln(X2C_REAL);

extern X2C_REAL RealMath_sin(X2C_REAL);

extern X2C_REAL RealMath_cos(X2C_REAL);

extern X2C_REAL RealMath_tan(X2C_REAL);

extern X2C_REAL RealMath_arcsin(X2C_REAL);

extern X2C_REAL RealMath_arccos(X2C_REAL);

extern X2C_REAL RealMath_arctan(X2C_REAL);

extern X2C_REAL RealMath_power(X2C_REAL, X2C_REAL);

extern X2C_INT32 RealMath_round(X2C_REAL);

extern X2C_BOOLEAN RealMath_IsRMathException(void);


extern void RealMath_BEGIN(void);


#endif /* RealMath_H_ */
