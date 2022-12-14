/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#ifndef XPrs_H_
#define XPrs_H_
#ifndef X2C_H_
#include "X2C.h"
#endif
#ifndef COROUTINES_H_
#include "COROUTINES.h"
#endif

#define XPrs_MAGIC 0x5FEB 

enum XPrs_State {XPrs_st_waiting, XPrs_st_ready, XPrs_st_passive};


struct XPrs_ProcessDesc;

typedef struct XPrs_ProcessDesc * XPrs_Process;


struct XPrs_ProcessDesc {
   X2C_CARD32 magic;
   XPrs_Process bck;
   XPrs_Process fwd;
   X2C_ADDRESS param;
   X2C_ADDRESS info;
   COROUTINES_COROUTINE body;
   X2C_INT32 urgency;
   X2C_ADDRESS wsp;
   X2C_CARD32 wsp_size;
   X2C_CARD8 state;
   X2C_PROC execBody;
};

extern XPrs_Process XPrs_current;


extern void XPrs_BEGIN(void);


#endif /* XPrs_H_ */
