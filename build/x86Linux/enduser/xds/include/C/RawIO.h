/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#ifndef RawIO_H_
#define RawIO_H_
#ifndef X2C_H_
#include "X2C.h"
#endif
#ifndef IOChan_H_
#include "IOChan.h"
#endif

extern void RawIO_Read(IOChan_ChanId, X2C_LOC [], X2C_CARD32);

extern void RawIO_Write(IOChan_ChanId, X2C_LOC [], X2C_CARD32);


extern void RawIO_BEGIN(void);


#endif /* RawIO_H_ */
