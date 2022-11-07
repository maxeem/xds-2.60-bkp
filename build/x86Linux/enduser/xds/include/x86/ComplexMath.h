/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#ifndef ComplexMath_H_
#define ComplexMath_H_
#ifndef X2C_H_
#include "X2C.h"
#endif

extern X2C_LONGCOMPLEX ComplexMath_i;

extern X2C_LONGCOMPLEX ComplexMath_one;

extern X2C_LONGCOMPLEX ComplexMath_zero;

extern X2C_REAL ComplexMath_abs(X2C_COMPLEX);

extern X2C_REAL ComplexMath_arg(X2C_COMPLEX);

extern X2C_COMPLEX ComplexMath_conj(X2C_COMPLEX);

extern X2C_COMPLEX ComplexMath_power(X2C_COMPLEX, X2C_REAL);

extern X2C_COMPLEX ComplexMath_sqrt(X2C_COMPLEX);

extern X2C_COMPLEX ComplexMath_exp(X2C_COMPLEX);

extern X2C_COMPLEX ComplexMath_ln(X2C_COMPLEX);

extern X2C_COMPLEX ComplexMath_sin(X2C_COMPLEX);

extern X2C_COMPLEX ComplexMath_cos(X2C_COMPLEX);

extern X2C_COMPLEX ComplexMath_tan(X2C_COMPLEX);

extern X2C_COMPLEX ComplexMath_arcsin(X2C_COMPLEX);

extern X2C_COMPLEX ComplexMath_arccos(X2C_COMPLEX);

extern X2C_COMPLEX ComplexMath_arctan(X2C_COMPLEX);

extern X2C_COMPLEX ComplexMath_polarToComplex(X2C_REAL, X2C_REAL);

extern X2C_COMPLEX ComplexMath_scalarMult(X2C_REAL, X2C_COMPLEX);

extern X2C_BOOLEAN ComplexMath_IsCMathException(void);


extern void ComplexMath_BEGIN(void);


#endif /* ComplexMath_H_ */
