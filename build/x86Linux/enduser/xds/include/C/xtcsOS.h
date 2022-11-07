/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
#ifndef xtcsOS_H_
#define xtcsOS_H_
#include "X2C.h"
#include "xmRTS.h"
#include "xlibOS.h"
#include "xPOSIX.h"

#define printf printf

extern void X2C_EnvString(X2C_pCHAR, X2C_pCHAR, X2C_CARD32);

extern X2C_pCHAR X2C_GetProgramName(void);

extern X2C_ADDRESS X2C_malloc(X2C_CARD32);

extern void X2C_free(X2C_ADDRESS, X2C_CARD32);

extern void X2C_StdOutS(X2C_CHAR [], X2C_CARD32);

extern void X2C_StdOutD(X2C_CARD32, X2C_CARD32);

extern void X2C_StdOutN(void);

extern void X2C_DecToStr(X2C_CHAR [], X2C_CARD32 *, X2C_CARD32);

extern void X2C_HexToStr(X2C_CHAR [], X2C_CARD32 *, X2C_CARD32);

typedef void *X2C_OSFILE;

extern X2C_BOOLEAN X2C_Exists(X2C_pCHAR);

extern int X2C_Remove(X2C_pCHAR);

extern int X2C_Rename(X2C_pCHAR, X2C_pCHAR);

extern int X2C_FileOpenRead(X2C_OSFILE *, X2C_CHAR []);

extern int X2C_FileOpenWrite(X2C_OSFILE *, X2C_CHAR []);

extern int X2C_FileClose(X2C_OSFILE);

extern int X2C_FileRead(X2C_OSFILE, X2C_ADDRESS, X2C_CARD32 *);

extern int X2C_FileWrite(X2C_OSFILE, X2C_ADDRESS, X2C_CARD32 *);

extern void X2C_atexit(X2C_EXIT_PROC);

typedef struct X2C_TimeStruct X2C_TimeStruct;

extern void X2C_GetTime(struct X2C_TimeStruct *);

extern void X2C_TimeSecAdd(struct X2C_TimeStruct, X2C_CARD32,
                struct X2C_TimeStruct *);


#endif /* xtcsOS_H_ */
