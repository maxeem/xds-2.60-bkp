/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#ifndef WholeStr_H_
#define WholeStr_H_
#ifndef X2C_H_
#include "X2C.h"
#endif
#ifndef ConvTypes_H_
#include "ConvTypes.h"
#endif

typedef enum ConvTypes_ConvResults WholeStr_ConvResults;

extern void WholeStr_StrToInt(X2C_CHAR [], X2C_CARD32, X2C_INT32 *,
                X2C_CARD8 *);

extern void WholeStr_IntToStr(X2C_INT32, X2C_CHAR [], X2C_CARD32);

extern void WholeStr_StrToCard(X2C_CHAR [], X2C_CARD32, X2C_CARD32 *,
                X2C_CARD8 *);

extern void WholeStr_CardToStr(X2C_CARD32, X2C_CHAR [], X2C_CARD32);


extern void WholeStr_BEGIN(void);


#endif /* WholeStr_H_ */
