/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#ifndef IOChan_H_
#define IOChan_H_
#ifndef X2C_H_
#include "X2C.h"
#endif
#ifndef IOConsts_H_
#include "IOConsts.h"
#endif

typedef void *IOChan_ChanId;

extern IOChan_ChanId IOChan_InvalidChan(void);

extern void IOChan_Look(IOChan_ChanId, X2C_CHAR *, X2C_CARD8 *);

extern void IOChan_Skip(IOChan_ChanId);

extern void IOChan_SkipLook(IOChan_ChanId, X2C_CHAR *, X2C_CARD8 *);

extern void IOChan_WriteLn(IOChan_ChanId);

extern void IOChan_TextRead(IOChan_ChanId, X2C_ADDRESS, X2C_CARD32,
                X2C_CARD32 *);

extern void IOChan_TextWrite(IOChan_ChanId, X2C_ADDRESS, X2C_CARD32);

extern void IOChan_RawRead(IOChan_ChanId, X2C_ADDRESS, X2C_CARD32,
                X2C_CARD32 *);

extern void IOChan_RawWrite(IOChan_ChanId, X2C_ADDRESS, X2C_CARD32);

extern void IOChan_GetName(IOChan_ChanId, X2C_CHAR [], X2C_CARD32);

extern void IOChan_Reset(IOChan_ChanId);

extern void IOChan_Flush(IOChan_ChanId);

extern void IOChan_SetReadResult(IOChan_ChanId, X2C_CARD8);

extern X2C_CARD8 IOChan_ReadResult(IOChan_ChanId);

extern X2C_CARD8 IOChan_CurrentFlags(IOChan_ChanId);

enum IOChan_ChanExceptions {IOChan_wrongDevice, 
   IOChan_notAvailable, 
   IOChan_skipAtEnd, 
   IOChan_softDeviceError, 
   IOChan_hardDeviceError, 
   IOChan_textParseError, 
   IOChan_notAChannel};


extern X2C_BOOLEAN IOChan_IsChanException(void);

extern X2C_CARD8 IOChan_ChanException(void);

typedef X2C_INT32 IOChan_DeviceErrNum;

extern X2C_INT32 IOChan_DeviceError(IOChan_ChanId);


extern void IOChan_BEGIN(void);


#endif /* IOChan_H_ */
