/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#ifndef IOResult_H_
#define IOResult_H_
#ifndef X2C_H_
#include "X2C.h"
#endif
#ifndef IOConsts_H_
#include "IOConsts.h"
#endif
#ifndef IOChan_H_
#include "IOChan.h"
#endif

typedef enum IOConsts_ReadResults IOResult_ReadResults;

extern X2C_CARD8 IOResult_ReadResult(IOChan_ChanId);


extern void IOResult_BEGIN(void);


#endif /* IOResult_H_ */
