/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)StdChans.c Nov 19  1:11:49 2022" */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef StdChans_H_
#include "StdChans.h"
#endif
#define StdChans_C_
#ifndef IOChan_H_
#include "IOChan.h"
#endif
#ifndef ChanConsts_H_
#include "ChanConsts.h"
#endif
#ifndef IOConsts_H_
#include "IOConsts.h"
#endif
#ifndef IOLink_H_
#include "IOLink.h"
#endif
#ifndef xDevData_H_
#include "xDevData.h"
#endif
#ifndef xlibOS_H_
#include "xlibOS.h"
#endif

static IOChan_ChanId stdinp;

static IOChan_ChanId stdout0;

static IOChan_ChanId stderr0;

static IOChan_ChanId inp0;

static IOChan_ChanId out;

static IOChan_ChanId err;

static IOChan_ChanId null;

static IOLink_DeviceId sdid;


extern IOChan_ChanId StdChans_StdInChan(void)
{
   return stdinp;
} /* end StdInChan() */


extern IOChan_ChanId StdChans_StdOutChan(void)
{
   return stdout0;
} /* end StdOutChan() */


extern IOChan_ChanId StdChans_StdErrChan(void)
{
   return stderr0;
} /* end StdErrChan() */


extern IOChan_ChanId StdChans_InChan(void)
{
   return inp0;
} /* end InChan() */


extern IOChan_ChanId StdChans_OutChan(void)
{
   return out;
} /* end OutChan() */


extern IOChan_ChanId StdChans_ErrChan(void)
{
   return err;
} /* end ErrChan() */


extern void StdChans_SetInChan(IOChan_ChanId cid)
{
   inp0 = cid;
} /* end SetInChan() */


extern void StdChans_SetOutChan(IOChan_ChanId cid)
{
   out = cid;
} /* end SetOutChan() */


extern void StdChans_SetErrChan(IOChan_ChanId cid)
{
   err = cid;
} /* end SetErrChan() */


extern IOChan_ChanId StdChans_NullChan(void)
{
   return null;
} /* end NullChan() */

static void look(IOLink_DeviceTablePtr, X2C_CHAR *, X2C_CARD8 *);


static void look(IOLink_DeviceTablePtr x, X2C_CHAR * c, X2C_CARD8 * r)
{
   x->result = IOConsts_endOfInput;
   *r = x->result;
   *c = 0;
} /* end look() */

static void skip(IOLink_DeviceTablePtr);


static void skip(IOLink_DeviceTablePtr x)
{
   x->result = IOConsts_endOfInput;
} /* end skip() */

static void read0(IOLink_DeviceTablePtr, X2C_ADDRESS, X2C_CARD32,
                X2C_CARD32 *);


static void read0(IOLink_DeviceTablePtr x, X2C_ADDRESS a, X2C_CARD32 max0,
                X2C_CARD32 * n)
{
   x->result = IOConsts_endOfInput;
} /* end read() */

static void write0(IOLink_DeviceTablePtr, X2C_ADDRESS, X2C_CARD32);


static void write0(IOLink_DeviceTablePtr x, X2C_ADDRESS a, X2C_CARD32 max0)
{
} /* end write() */


static void Ini(IOLink_DeviceTablePtr x)
{
   x->flags = 0x3U;
   x->doLook = look;
   x->doSkip = skip;
   x->doSkipLook = look;
   x->doTextRead = read0;
   x->doTextWrite = write0;
   x->doLnWrite = skip;
   x->doRawRead = read0;
   x->doRawWrite = write0;
} /* end Ini() */


static void Open(IOChan_ChanId * cid, int what, X2C_CARD8 flags)
{
   X2C_OSFHANDLE f;
   xDevData_FileName fn;
   X2C_CARD8 res;
   if (X2C_fGetStd(&f, what)) {
      *cid = null;
      return;
   }
   xDevData_MakeName(&fn, "", 1ul, &res);
   IOLink_MakeChan(sdid, cid);
   if (*cid!=IOChan_InvalidChan()) {
      xDevData_Open(IOLink_DeviceTablePtrValue(*cid, sdid,
                IOChan_notAvailable, "", 1ul), f, fn, flags, xDevData_bmLine,
                 &res);
   }
} /* end Open() */


static void OpenChannels(void)
{
   X2C_CARD8 ops;
   if (X2C_IsMixAllowed()) ops = 0x18U;
   else ops = 0x8U;
   Open(&stdinp, 0, 0x1U|ops);
   Open(&stdout0, 1, 0x2U|ops);
   Open(&stderr0, 2, 0x2U|ops);
   inp0 = stdinp;
   out = stdout0;
   err = stderr0;
} /* end OpenChannels() */


extern X2C_BOOLEAN StdChans_Synchronize(void)
{
   X2C_BOOLEAN res1;
   X2C_BOOLEAN res0;
   res0 = xDevData_SynchronizePos(IOLink_DeviceTablePtrValue(out, sdid,
                IOChan_notAvailable, "", 1ul));
   res1 = xDevData_SynchronizePos(IOLink_DeviceTablePtrValue(err, sdid,
                IOChan_notAvailable, "", 1ul));
   return res0 || res1;
} /* end Synchronize() */


extern void StdChans_BEGIN(void)
{
   static int StdChans_init = 0;
   if (StdChans_init) return;
   StdChans_init = 1;
   xDevData_BEGIN();
   IOConsts_BEGIN();
   ChanConsts_BEGIN();
   IOLink_BEGIN();
   IOChan_BEGIN();
   IOLink_AllocateDeviceId(&sdid);
   IOLink_MakeChan(sdid, &null);
   if (null!=IOChan_InvalidChan()) {
      Ini(IOLink_DeviceTablePtrValue(null, sdid, IOChan_notAvailable, "",
                1ul));
   }
   OpenChannels();
}

