/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#ifndef xrBlockManager_H_
#define xrBlockManager_H_
#ifndef X2C_H_
#include "X2C.h"
#endif

extern X2C_BOOLEAN xrBlockManager_init(X2C_CARD32);

extern X2C_ADDRESS xrBlockManager_alloc(void);

extern void xrBlockManager_free(X2C_ADDRESS);

extern void xrBlockManager_exit(void);

#define xrBlockManager_heapLimit 0x40000000 


extern void xrBlockManager_BEGIN(void);


#endif /* xrBlockManager_H_ */
