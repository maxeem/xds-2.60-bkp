/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#ifndef IO_H_
#define IO_H_
#ifndef X2C_H_
#include "X2C.h"
#endif

#define IO_MaxRdLength 256

#define IO_MaxWrLength 256

typedef void ( *IO_WrStrType)(X2C_CHAR [], X2C_CARD32);

typedef void ( *IO_RdStrType)(X2C_CHAR [], X2C_CARD32);

typedef X2C_CARD32 IO_CHARSET[8];

extern IO_RdStrType IO_RdStrRedirect;

extern IO_WrStrType IO_WrStrRedirect;

extern X2C_BOOLEAN IO_InputRedirected;

extern X2C_BOOLEAN IO_OutputRedirected;

extern X2C_BOOLEAN IO_RdLnOnWr;

extern X2C_BOOLEAN IO_Prompt;

extern IO_CHARSET IO_Separators;

extern X2C_BOOLEAN IO_OK;

extern X2C_BOOLEAN IO_ChopOff;

extern X2C_BOOLEAN IO_Eng;

extern X2C_CHAR IO_PrefixChar;

extern X2C_CHAR IO_SuffixChar;

extern void IO_RedirectInput(X2C_CHAR [], X2C_CARD32);

extern void IO_RedirectOutput(X2C_CHAR [], X2C_CARD32);

extern X2C_BOOLEAN IO_KeyPressed(void);

extern X2C_CHAR IO_RdKey(void);

#define IO_RdCharDirect IO_RdKey

extern void IO_RdStr(X2C_CHAR [], X2C_CARD32);

extern X2C_BOOLEAN IO_EndOfRd(X2C_BOOLEAN);

extern void IO_RdLn(void);

extern X2C_CHAR IO_RdChar(void);

extern X2C_BOOLEAN IO_RdBool(void);

extern X2C_INT8 IO_RdShtInt(void);

extern X2C_INT32 IO_RdInt(void);

extern X2C_INT32 IO_RdLngInt(void);

extern X2C_CARD8 IO_RdShtCard(void);

extern X2C_CARD32 IO_RdCard(void);

extern X2C_CARD32 IO_RdLngCard(void);

extern X2C_CARD8 IO_RdShtHex(void);

extern X2C_CARD32 IO_RdHex(void);

extern X2C_CARD32 IO_RdLngHex(void);

extern X2C_REAL IO_RdReal(void);

extern X2C_LONGREAL IO_RdLngReal(void);

extern void IO_RdItem(X2C_CHAR [], X2C_CARD32);

extern void IO_WrStr(X2C_CHAR [], X2C_CARD32);

extern void IO_WrStrAdj(X2C_CHAR [], X2C_CARD32, X2C_INT32);

extern void IO_WrLn(void);

extern void IO_WrChar(X2C_CHAR);

extern void IO_WrBool(X2C_BOOLEAN, X2C_INT32);

extern void IO_WrShtInt(X2C_INT8, X2C_INT32);

extern void IO_WrInt(X2C_INT32, X2C_INT32);

extern void IO_WrLngInt(X2C_INT32, X2C_INT32);

extern void IO_WrShtCard(X2C_CARD8, X2C_INT32);

extern void IO_WrCard(X2C_CARD32, X2C_INT32);

extern void IO_WrLngCard(X2C_CARD32, X2C_INT32);

extern void IO_WrShtHex(X2C_CARD8, X2C_INT32);

extern void IO_WrHex(X2C_CARD32, X2C_INT32);

extern void IO_WrLngHex(X2C_CARD32, X2C_INT32);

extern void IO_WrReal(X2C_REAL, X2C_CARD32, X2C_INT32);

extern void IO_WrLngReal(X2C_LONGREAL, X2C_CARD32, X2C_INT32);

extern void IO_WrFixReal(X2C_REAL, X2C_CARD32, X2C_INT32);

extern void IO_WrFixLngReal(X2C_LONGREAL, X2C_CARD32, X2C_INT32);

extern void IO_WrCharRep(X2C_CHAR, X2C_CARD32);

extern X2C_BOOLEAN IO_ThreadOK(void);


extern void IO_BEGIN(void);


#endif /* IO_H_ */
