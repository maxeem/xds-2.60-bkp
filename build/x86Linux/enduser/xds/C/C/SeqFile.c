/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)SeqFile.c Nov 19  1:11:49 2022" */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef SeqFile_H_
#include "SeqFile.h"
#endif
#define SeqFile_C_
#ifndef IOChan_H_
#include "IOChan.h"
#endif
#ifndef ChanConsts_H_
#include "ChanConsts.h"
#endif
#ifndef IOLink_H_
#include "IOLink.h"
#endif
#ifndef xDevData_H_
#include "xDevData.h"
#endif
#ifndef xrInt64_H_
#include "xrInt64.h"
#endif
#ifndef xlibOS_H_
#include "xlibOS.h"
#endif
#ifndef xmRTS_H_
#include "xmRTS.h"
#endif

X2C_CARD8 SeqFile_read = 0x1U;
X2C_CARD8 SeqFile_write = 0x2U;
X2C_CARD8 SeqFile_old = 0x4U;
X2C_CARD8 SeqFile_text = 0x8U;
X2C_CARD8 SeqFile_raw = 0x10U;
static IOLink_DeviceId did;


static void doOpenWrite(IOLink_DeviceTablePtr x, xDevData_FileName fn,
                X2C_CARD8 flags, X2C_CARD8 * res)
{
   X2C_OSFHANDLE f;
   X2C_CARD32 tags;
   if ((0x4U & flags)==0 && X2C_Exists((X2C_pCHAR)fn->Adr)) {
      *res = ChanConsts_fileExists;
      return;
   }
   flags |= 0x2U;
   if ((0x10U & flags)==0) flags |= 0x8U;
   if ((0x1U & flags)) tags = 0x1UL;
   else tags = 0UL;
   if ((0x8U & flags)) tags = tags|0x8UL;
   if ((0x10U & flags)) tags = tags|0x10UL;
   tags = tags|0x2UL|0x4UL;
   *res = X2C_fOpen(&f, fn->Adr, tags);
   if (*res) return;
   xDevData_Open(x, f, fn, flags, xDevData_bmFull, res);
   if (*res) X2C_fClose(&f);
} /* end doOpenWrite() */


extern void SeqFile_OpenWrite(IOChan_ChanId * cid, X2C_CHAR name[],
                X2C_CARD32 name_len, X2C_CARD8 flags, X2C_CARD8 * res)
{
   xDevData_FileName fn;
   IOLink_DeviceTablePtr x;
   X2C_PCOPY((void **)&name,name_len);
   if ((0x4U & flags)==0 && X2C_Exists((X2C_pCHAR)name)) {
      *res = ChanConsts_fileExists;
      goto label;
   }
   xDevData_MakeName(&fn, name, name_len, res);
   if (*res) goto label;
   IOLink_MakeChan(did, cid);
   if (*cid==IOChan_InvalidChan()) {
      *res = ChanConsts_outOfChans;
      goto label;
   }
   x = IOLink_DeviceTablePtrValue(*cid, did, IOChan_notAvailable, "", 1ul);
   doOpenWrite(x, fn, flags, res);
   if (*res==ChanConsts_opened) xDevData_SetMode(x, 0);
   else {
      xDevData_UnMakeName(&fn);
      IOLink_UnMakeChan(did, cid);
   }
   label:;
   X2C_PFREE(name);
} /* end OpenWrite() */


extern void SeqFile_OpenAppend(IOChan_ChanId * cid, X2C_CHAR name[],
                X2C_CARD32 name_len, X2C_CARD8 flags, X2C_CARD8 * res)
{
   X2C_OSFHANDLE f;
   X2C_CARD32 tags;
   struct X2C_int64 pos;
   xDevData_FileName fn;
   IOLink_DeviceTablePtr x;
   X2C_INT32 r;
   X2C_PCOPY((void **)&name,name_len);
   if ((0x10U & flags)==0) flags |= 0x8U;
   flags = flags|0x2U|0x4U;
   xDevData_MakeName(&fn, name, name_len, res);
   if (*res) goto label;
   IOLink_MakeChan(did, cid);
   if (*cid==IOChan_InvalidChan()) {
      *res = ChanConsts_outOfChans;
      xDevData_UnMakeName(&fn);
      goto label;
   }
   if ((0x1U & flags)) tags = 0x1UL;
   else tags = 0UL;
   if ((0x8U & flags)) tags = tags|0x8UL;
   if ((0x10U & flags)) tags = tags|0x10UL;
   tags = tags|0x2UL;
   if (!X2C_Exists((X2C_pCHAR)fn->Adr)) tags = tags|0x4UL;
   *res = X2C_fOpen(&f, fn->Adr, tags);
   if (*res) {
      IOLink_UnMakeChan(did, cid);
      xDevData_UnMakeName(&fn);
      goto label;
   }
   X2C_CARDTO64(&pos, 0UL);
   r = X2C_fSeek(f, &pos, 2);
   x = IOLink_DeviceTablePtrValue(*cid, did, IOChan_notAvailable, "", 1ul);
   if (r) xDevData_SoftError(x, *(X2C_WORD *) &r);
   xDevData_Open(x, f, fn, flags, xDevData_bmFull, res);
   if (*res==ChanConsts_opened) xDevData_SetMode(x, 0);
   else {
      xDevData_UnMakeName(&fn);
      X2C_fClose(&f);
      IOLink_UnMakeChan(did, cid);
   }
   label:;
   X2C_PFREE(name);
} /* end OpenAppend() */


extern void SeqFile_OpenRead(IOChan_ChanId * cid, X2C_CHAR name[],
                X2C_CARD32 name_len, X2C_CARD8 flags, X2C_CARD8 * res)
{
   X2C_OSFHANDLE f;
   X2C_CARD32 tags;
   xDevData_FileName fn;
   IOLink_DeviceTablePtr x;
   X2C_PCOPY((void **)&name,name_len);
   if ((0x10U & flags)==0) flags |= 0x8U;
   flags = flags|0x1U|0x4U;
   xDevData_MakeName(&fn, name, name_len, res);
   if (*res) goto label;
   IOLink_MakeChan(did, cid);
   if (*cid==IOChan_InvalidChan()) {
      *res = ChanConsts_outOfChans;
      xDevData_UnMakeName(&fn);
      goto label;
   }
   if ((0x2U & flags)) tags = 0x2UL;
   else tags = 0UL;
   if ((0x8U & flags)) tags = tags|0x8UL;
   if ((0x10U & flags)) tags = tags|0x10UL;
   tags = tags|0x1UL;
   *res = X2C_fOpen(&f, fn->Adr, tags);
   if (*res) {
      IOLink_UnMakeChan(did, cid);
      xDevData_UnMakeName(&fn);
      goto label;
   }
   x = IOLink_DeviceTablePtrValue(*cid, did, IOChan_notAvailable, "", 1ul);
   xDevData_Open(x, f, fn, flags, xDevData_bmFull, res);
   if (*res==ChanConsts_opened) xDevData_SetMode(x, 1);
   else {
      xDevData_UnMakeName(&fn);
      IOLink_UnMakeChan(did, cid);
   }
   label:;
   X2C_PFREE(name);
} /* end OpenRead() */


extern X2C_BOOLEAN SeqFile_IsSeqFile(IOChan_ChanId cid)
{
   IOLink_DeviceTablePtr x;
   xDevData_DevData dd;
   if (IOLink_IsDevice(cid, did)) {
      x = IOLink_DeviceTablePtrValue(cid, did, IOChan_notAvailable, "", 1ul);
      dd = (xDevData_DevData)x->cd;
      return X2C_fGetFileType(dd->cf)==0;
   }
   return 0;
} /* end IsSeqFile() */


extern void SeqFile_Reread(IOChan_ChanId cid)
{
   IOLink_DeviceTablePtr x;
   struct X2C_int64 null;
   x = IOLink_DeviceTablePtrValue(cid, did, IOChan_notAvailable, "", 1ul);
   X2C_CARDTO64(&null, 0UL);
   xDevData_SetPos(x, null);
   xDevData_SetMode(x, 1);
} /* end Reread() */


extern void SeqFile_Rewrite(IOChan_ChanId cid)
{
   xDevData_DevData f;
   IOLink_DeviceTablePtr x;
   X2C_CARD8 res;
   xDevData_FileName fn;
   X2C_CARD8 flags;
   X2C_INT32 r;
   xDevData_FileName anonym;
   x = IOLink_DeviceTablePtrValue(cid, did, IOChan_notAvailable, "", 1ul);
   f = xDevData_GetDevData(x);
   flags = f->flags|0x4U;
   anonym = f->name;
   xDevData_MakeName(&fn, anonym->Adr, anonym->Len0, &res);
   if (res==ChanConsts_opened) {
      xDevData_Close(x);
      r = X2C_fClose(&f->cf);
      if (r) xDevData_SoftError(x, *(X2C_WORD *) &r);
      doOpenWrite(x, fn, flags, &res);
   }
   if (res) xDevData_ForbidAll(x);
   else xDevData_SetMode(x, 0);
} /* end Rewrite() */


extern void SeqFile_Close(IOChan_ChanId * cid)
{
   IOLink_DeviceTablePtr x;
   xDevData_DevData f;
   X2C_OSFHANDLE cf;
   x = IOLink_DeviceTablePtrValue(*cid, did, IOChan_notAvailable, "", 1ul);
   f = xDevData_GetDevData(x);
   cf = f->cf;
   xDevData_Close(x);
   X2C_fClose(&cf);
   IOLink_UnMakeChan(did, cid);
} /* end Close() */


extern void SeqFile_BEGIN(void)
{
   static int SeqFile_init = 0;
   if (SeqFile_init) return;
   SeqFile_init = 1;
   xDevData_BEGIN();
   IOLink_BEGIN();
   IOChan_BEGIN();
   ChanConsts_BEGIN();
   xDevData_GetDID(&did);
}

