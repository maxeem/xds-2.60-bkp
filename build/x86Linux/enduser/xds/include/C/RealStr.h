/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#ifndef RealStr_H_
#define RealStr_H_
#ifndef X2C_H_
#include "X2C.h"
#endif
#ifndef ConvTypes_H_
#include "ConvTypes.h"
#endif

typedef X2C_REAL RealStr_float;

typedef enum ConvTypes_ConvResults RealStr_ConvResults;

extern void RealStr_StrToReal(X2C_CHAR [], X2C_CARD32, X2C_REAL *,
                X2C_CARD8 *);

extern void RealStr_RealToFloat(X2C_REAL, X2C_CARD32, X2C_CHAR [],
                X2C_CARD32);

extern void RealStr_RealToEng(X2C_REAL, X2C_CARD32, X2C_CHAR [], X2C_CARD32);

extern void RealStr_RealToFixed(X2C_REAL, X2C_INT32, X2C_CHAR [],
                X2C_CARD32);

extern void RealStr_RealToStr(X2C_REAL, X2C_CHAR [], X2C_CARD32);


extern void RealStr_BEGIN(void);


#endif /* RealStr_H_ */
