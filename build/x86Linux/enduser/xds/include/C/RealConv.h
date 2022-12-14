/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#ifndef RealConv_H_
#define RealConv_H_
#ifndef X2C_H_
#include "X2C.h"
#endif
#ifndef ConvTypes_H_
#include "ConvTypes.h"
#endif

typedef enum ConvTypes_ConvResults RealConv_ConvResults;

extern void RealConv_ScanReal(X2C_CHAR, X2C_CARD8 *, ConvTypes_ScanState *);

extern X2C_CARD8 RealConv_FormatReal(X2C_CHAR [], X2C_CARD32);

extern X2C_REAL RealConv_ValueReal(X2C_CHAR [], X2C_CARD32);

extern X2C_CARD32 RealConv_LengthFloatReal(X2C_REAL, X2C_CARD32);

extern X2C_CARD32 RealConv_LengthEngReal(X2C_REAL, X2C_CARD32);

extern X2C_CARD32 RealConv_LengthFixedReal(X2C_REAL, X2C_INT32);

extern X2C_BOOLEAN RealConv_IsRConvException(void);


extern void RealConv_BEGIN(void);


#endif /* RealConv_H_ */
