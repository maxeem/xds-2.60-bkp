/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)xrBlockManager.c Nov 19  1:11:49 2022" */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef xrBlockManager_H_
#include "xrBlockManager.h"
#endif
#define xrBlockManager_C_
#ifndef xosMalloc_H_
#include "xosMalloc.h"
#endif
#ifndef xosBalls_H_
#include "xosBalls.h"
#endif

static X2C_CARD32 bSize;


extern X2C_BOOLEAN xrBlockManager_init(X2C_CARD32 blockSize)
{
   bSize = blockSize;
   return 1;
} /* end init() */


extern X2C_ADDRESS xrBlockManager_alloc(void)
{
   return X2C_malloc(bSize);
} /* end alloc() */


extern void xrBlockManager_free(X2C_ADDRESS adr)
{
   X2C_free(adr, bSize);
} /* end free() */


extern void xrBlockManager_exit(void)
{
} /* end exit() */


extern void xrBlockManager_BEGIN(void)
{
   static int xrBlockManager_init = 0;
   if (xrBlockManager_init) return;
   xrBlockManager_init = 1;
}

