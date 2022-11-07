/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)XIOChan.c Nov  7 22:55:32 2022" */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef XIOChan_H_
#include "XIOChan.h"
#endif
#define XIOChan_C_
#ifndef IOChan_H_
#include "IOChan.h"
#endif
#ifndef xDevData_H_
#include "xDevData.h"
#endif
#ifndef IOLink_H_
#include "IOLink.h"
#endif
#ifndef xrInt64_H_
#include "xrInt64.h"
#endif
#ifndef xlibOS_H_
#include "xlibOS.h"
#endif

static IOLink_DeviceId did;


extern void XIOChan_Truncate(IOChan_ChanId cid)
{
   IOLink_DeviceTablePtr x;
   xDevData_DevData d;
   struct X2C_int64 pos;
   int res;
   x = IOLink_DeviceTablePtrValue(cid, did, IOChan_notAvailable, "XIOChan.Tru\
ncate", 17ul);
   d = (xDevData_DevData)x->cd;
   xDevData_CurrentPos(x, &pos);
   IOChan_Flush(cid);
   X2C_fSeek(d->cf, &pos, 0);
   res = X2C_fChSize(d->cf);
   if (res) xDevData_SoftError(x, *(X2C_WORD *) &res);
} /* end Truncate() */


extern void XIOChan_BEGIN(void)
{
   static int XIOChan_init = 0;
   if (XIOChan_init) return;
   XIOChan_init = 1;
   IOLink_BEGIN();
   xDevData_BEGIN();
   IOChan_BEGIN();
   xDevData_GetDID(&did);
}

