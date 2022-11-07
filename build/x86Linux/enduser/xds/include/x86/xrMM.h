/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#ifndef xrMM_H_
#define xrMM_H_
#ifndef X2C_H_
#include "X2C.h"
#endif
#ifndef xmRTS_H_
#include "xmRTS.h"
#endif

#define xrMM_BlockSize 16384

#define xrMM_Max 20

#define xrMM_NORMAL 0

#define xrMM_LARGE 21

#define xrMM_MaxDim 8

typedef void ( *xrMM_GarbageCollector)(void);

typedef X2C_CARD32 xrMM_CARD32;

typedef size_t xrMM_SIZE_T;

struct xrMM_BlockDesc;

typedef struct xrMM_BlockDesc * xrMM_Block;


struct xrMM_BlockDesc {
   X2C_CARD32 size;
   xrMM_Block next;
   xrMM_Block prev;
   xrMM_Block snxt;
   X2C_CARD32 fsum;
   X2C_LINK list;
   X2C_ADDRESS mem;
   X2C_CARD32 magic;
   X2C_CARD8 root;
   X2C_BOOLEAN fixed;
};

struct xrMM__D0;

typedef struct xrMM__D0 * xrMM_Dynarr;


struct xrMM__D0 {
   X2C_ADDRESS a;
   size_t n[15];
};

#define xrMM_LINK_SZ sizeof(struct X2C_LINK_STR)

#define xrMM_PAD_SZ sizeof(struct X2C_LINK_STR)

#define xrMM_BLOCK_SZ ((((sizeof(struct xrMM_BlockDesc)+sizeof(struct X2C_LIN\
K_STR)+sizeof(struct X2C_LINK_STR))-1UL)/sizeof(struct X2C_LINK_STR))*sizeof(\
struct X2C_LINK_STR))

#define xrMM_MEMORY_OFS ((((sizeof(struct xrMM_BlockDesc)+sizeof(struct X2C_L\
INK_STR)+sizeof(struct X2C_LINK_STR))-1UL)/sizeof(struct X2C_LINK_STR))*sizeo\
f(struct X2C_LINK_STR)-sizeof(struct X2C_LINK_STR))

#define xrMM_SmallBlockSize (16384UL-(((sizeof(struct xrMM_BlockDesc)+sizeof(\
struct X2C_LINK_STR)+sizeof(struct X2C_LINK_STR))-1UL)/sizeof(struct X2C_LINK\
_STR))*sizeof(struct X2C_LINK_STR))

#define xrMM_NormalBlockSize (16384UL-(((sizeof(struct xrMM_BlockDesc)+sizeof\
(struct X2C_LINK_STR)+sizeof(struct X2C_LINK_STR))-1UL)/sizeof(struct X2C_LIN\
K_STR))*sizeof(struct X2C_LINK_STR))

#define xrMM__sysbit 14

#define xrMM__expbit 15

#define xrMM__markbit 16

#define xrMM__free 17

#define xrMM__moved 18

#define xrMM__stack 19

#define xrMM__unmovable 20

#define xrMM__unused0 0

#define xrMM__unused1 1

#define xrMM__notstack 2

extern X2C_CARD32 xrMM_all_tags;

extern X2C_CARD32 xrMM_BOFS_MASK;

extern X2C_CARD32 xrMM_SZ_MASK;

#define xrMM_MAGIC_B 0x12345678 

#define xrMM_MAGIC_T 0x093678150

#define xrMM_MAGIC_G 0x084761853

extern xrMM_Block xrMM_f_blocks[22];

extern xrMM_Block xrMM_b_blocks[22];

extern X2C_CARD32 xrMM_parts[21];

extern X2C_CARD32 xrMM_expusedmem;

extern X2C_BOOLEAN xrMM_DoDefrag;

extern X2C_BOOLEAN xrMM_GCAUTO;

extern X2C_INT32 xrMM_GCTHRESCNT;

extern X2C_BOOLEAN xrMM_O2MM_init;

extern xrMM_GarbageCollector xrMM_COLLECTOR;

extern X2C_BOOLEAN xrMM_FloatingHeaplimit;

extern X2C_BOOLEAN xrMM_X2C_AlwaysDefrag;

#define xrMM_InitialFloatingMaxMem 10485760

#define xrMM_MinFloatingMaxMem 1048576

extern void xrMM_allocate(X2C_LINK *, X2C_CARD32, X2C_BOOLEAN);

extern void xrMM_free_block(xrMM_Block);

extern void xrMM_dealloc(X2C_LINK);

extern void xrMM_foManager_add(X2C_LINK);

extern void xrMM_foManager_del(X2C_LINK);

extern void X2C_InitDesc(xrMM_Dynarr, size_t *, size_t [], size_t);

extern size_t xrMM_DynarrDescSize(size_t);

extern void xrMM_SetNil(X2C_ADDRESS, size_t);

extern void xrMM_MakeFree(xrMM_Block);

extern void xrMM_MakeBusy(xrMM_Block);

extern X2C_CARD32 xrMM_Align(X2C_CARD32);

extern void xrMM_CheckHeap(void);

extern X2C_ADDRESS xrMM_getFirstBlockAdr(xrMM_Block);

extern X2C_ADDRESS xrMM_getLastBlockAdr1(xrMM_Block);

extern xrMM_Block xrMM_getLargeObjBlock(X2C_LINK);

extern void xrMM_NewBlock(X2C_CARD8, xrMM_Block *, X2C_CARD32);

extern void xrMM_setObjOfsLen(X2C_LINK *, X2C_CARD32, X2C_CARD32);

extern X2C_ADDRESS xrMM_blk_min;

extern X2C_ADDRESS xrMM_blk_max;

#define xrMM_GAP_LEN 32

extern X2C_CARD32 xrMM_blockno;

extern X2C_TD xrMM_cur_td;

extern X2C_INT32 xrMM_cur_offs;

extern X2C_CARD32 xrMM_getHpObjSize(X2C_LINK);

extern void xrMM_SetGap(X2C_ADDRESS);

extern void xrMM_ini_type_desc(X2C_TD *, X2C_CHAR [], X2C_CARD32, X2C_CARD32,
                 X2C_ADDRESS);

extern X2C_BOOLEAN xrMM_anchorTracing;

extern X2C_CARD32 xrMM_anchorWeightThreshold;

extern X2C_BOOLEAN xrMM_heapTracing;

extern X2C_CARD32 xrMM_heapTracingThreshold;

extern void xrMM_stampAsNonConservative(X2C_ADDRESS);

extern void X2C_COLLECT(void);

extern X2C_BOOLEAN X2C_GC_INIT(X2C_BOOLEAN, X2C_CARD32, X2C_CARD32);

extern void X2C_GC_INCREASE(X2C_BOOLEAN, X2C_CARD32, X2C_CARD32);

extern void xrMM_HeapLock(void);

extern void xrMM_HeapUnlock(void);

extern void X2C_MemoryManager_exit(void);

extern X2C_Coroutine xrMM_GCInvoker;

extern X2C_ADDRESS xrMM_StackEnd4GC;

extern X2C_CARD32 xrMM_SizeToAlloc;

extern X2C_CARD32 xrMM_UsedMemAtGCStart;

extern X2C_CARD32 xrMM_UsedMemAtGCEnd;


extern void xrMM_BEGIN(void);


#endif /* xrMM_H_ */
