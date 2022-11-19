/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)XRaise.c Nov 19  1:11:33 2022" */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef XRaise_H_
#include "XRaise.h"
#endif
#define XRaise_C_
#ifndef xrtsOS_H_
#include "xrtsOS.h"
#endif


extern void XRaise_RAISE(X2C_CARD32 no, X2C_CHAR msg[], X2C_CARD32 msg_len)
{
   X2C_PCOPY((void **)&msg,msg_len);
   X2C_StdOutN();
   X2C_StdOut("*** EXCEPTION: ", 15UL);
   X2C_StdOut(msg, X2C_LENGTH(msg,msg_len));
   X2C_StdOut(" ***", 4UL);
   X2C_StdOutN();
   X2C_StdOutFlush();
   X2C_PFREE(msg);
} /* end RAISE() */


extern void XRaise_BEGIN(void)
{
   static int XRaise_init = 0;
   if (XRaise_init) return;
   XRaise_init = 1;
}

