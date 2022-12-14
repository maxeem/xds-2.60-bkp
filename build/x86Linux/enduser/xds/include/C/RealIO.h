/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#ifndef RealIO_H_
#define RealIO_H_
#ifndef X2C_H_
#include "X2C.h"
#endif
#ifndef IOChan_H_
#include "IOChan.h"
#endif

extern void RealIO_ReadReal(IOChan_ChanId, X2C_REAL *);

extern void RealIO_WriteFloat(IOChan_ChanId, X2C_REAL, X2C_CARD32,
                X2C_CARD32);

extern void RealIO_WriteEng(IOChan_ChanId, X2C_REAL, X2C_CARD32, X2C_CARD32);

extern void RealIO_WriteFixed(IOChan_ChanId, X2C_REAL, X2C_INT32,
                X2C_CARD32);

extern void RealIO_WriteReal(IOChan_ChanId, X2C_REAL, X2C_CARD32);


extern void RealIO_BEGIN(void);


#endif /* RealIO_H_ */
