/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#ifndef ProgEnv_H_
#define ProgEnv_H_
#ifndef X2C_H_
#include "X2C.h"
#endif

extern X2C_CARD32 ProgEnv_ArgNumber(void);

extern void ProgEnv_GetArg(X2C_CARD32, X2C_CHAR [], X2C_CARD32);

extern X2C_CARD32 ProgEnv_ArgLength(X2C_CARD32);

extern void ProgEnv_ProgramName(X2C_CHAR [], X2C_CARD32);

extern X2C_CARD32 ProgEnv_ProgramNameLength(void);

extern void ProgEnv_String(X2C_CHAR [], X2C_CARD32, X2C_CHAR [], X2C_CARD32);

extern X2C_CARD32 ProgEnv_StringLength(X2C_CHAR [], X2C_CARD32);


extern void ProgEnv_BEGIN(void);


#endif /* ProgEnv_H_ */
