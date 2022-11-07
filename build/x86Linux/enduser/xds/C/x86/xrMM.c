/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)xrMM.c Nov  7 22:55:32 2022" */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef xrMM_H_
#include "xrMM.h"
#endif
#define xrMM_C_
#ifndef xmRTS_H_
#include "xmRTS.h"
#endif
#ifndef xrBlockManager_H_
#include "xrBlockManager.h"
#endif
#ifndef xrDTree_H_
#include "xrDTree.h"
#endif
#ifndef xosMalloc_H_
#include "xosMalloc.h"
#endif
#include "X2C.h"
#ifndef xrtsOS_H_
#include "xrtsOS.h"
#endif





X2C_CARD32 xrMM_all_tags = 0x1FC007UL;
X2C_CARD32 xrMM_BOFS_MASK = 0xFFE00000UL;
X2C_CARD32 xrMM_SZ_MASK = 0x3FF8UL;
xrMM_Block xrMM_f_blocks[22];
xrMM_Block xrMM_b_blocks[22];
X2C_CARD32 xrMM_parts[21];
X2C_CARD32 xrMM_expusedmem;
X2C_BOOLEAN xrMM_DoDefrag;
X2C_BOOLEAN xrMM_GCAUTO;
X2C_INT32 xrMM_GCTHRESCNT;
X2C_BOOLEAN xrMM_O2MM_init;
xrMM_GarbageCollector xrMM_COLLECTOR;
X2C_BOOLEAN xrMM_FloatingHeaplimit;
X2C_BOOLEAN xrMM_X2C_AlwaysDefrag;
X2C_ADDRESS xrMM_blk_min;
X2C_ADDRESS xrMM_blk_max;
X2C_CARD32 xrMM_blockno;
X2C_TD xrMM_cur_td;
X2C_INT32 xrMM_cur_offs;
X2C_BOOLEAN xrMM_anchorTracing;
X2C_CARD32 xrMM_anchorWeightThreshold;
X2C_BOOLEAN xrMM_heapTracing;
X2C_CARD32 xrMM_heapTracingThreshold;
X2C_Coroutine xrMM_GCInvoker;
X2C_ADDRESS xrMM_StackEnd4GC;
X2C_CARD32 xrMM_SizeToAlloc;
X2C_CARD32 xrMM_UsedMemAtGCStart;
X2C_CARD32 xrMM_UsedMemAtGCEnd;
#define xrMM_AdrLss X2C_adr_lss

#define xrMM_AdrGtr X2C_adr_gtr

#define xrMM_GAP_SIZE 128

static X2C_CARD32 xrMM_MaxSmall = 160UL;

static X2C_CARD32 xrMM_MinLarge = 16168UL;

#define xrMM_malloc X2C_malloc

#define xrMM_free X2C_free


extern void xrMM_HeapLock(void)
{
} /* end HeapLock() */


extern void xrMM_HeapUnlock(void)
{
} /* end HeapUnlock() */


extern X2C_CARD32 xrMM_Align(X2C_CARD32 size)
{
   X2C_CARD32 i;
   i = (size+15UL)/8UL;
   return i*8UL;
} /* end Align() */


extern void xrMM_SetNil(X2C_ADDRESS a, size_t size)
{
   X2C_ZEROMEM(a, (size+3U)/4U);
} /* end SetNil() */


extern void xrMM_SetGap(X2C_ADDRESS a)
{
   X2C_CARD32 * p;
   X2C_CARD32 i;
   p = (X2C_CARD32 *)a;
   for (i = 0UL; i<=31UL; i++) {
      p[i] = 0x084761853UL;
   } /* end for */
} /* end SetGap() */


extern X2C_CARD32 xrMM_getHpObjSize(X2C_LINK obj)
{
   return (X2C_CARD32)((X2C_CARD32)obj->_0.size&0x3FF8UL);
} /* end getHpObjSize() */


static void stampObjAsFree(X2C_LINK obj, X2C_CARD32 size)
{
   obj->_0.size = (X2C_CARD32)(obj->_0.tags&0xFFE00000UL|0x20000UL)+size;
} /* end stampObjAsFree() */


extern X2C_ADDRESS xrMM_getFirstBlockAdr(xrMM_Block b)
{
   return (X2C_ADDRESS)(xrMM_Block)((X2C_ADDRESS)b+(X2C_INT32)40L);
} /* end getFirstBlockAdr() */


extern X2C_ADDRESS xrMM_getLastBlockAdr1(xrMM_Block b)
{
   return (X2C_ADDRESS)(xrMM_Block)((X2C_ADDRESS)(xrMM_Block)((X2C_ADDRESS)
                b+(X2C_INT32)40L)+(X2C_INT32)(X2C_INT32)b->size);
} /* end getLastBlockAdr1() */


extern xrMM_Block xrMM_getLargeObjBlock(X2C_LINK largeObj)
{
   return (xrMM_Block)(X2C_LINK)((X2C_ADDRESS)largeObj-(X2C_INT32)40L);
} /* end getLargeObjBlock() */

#define xrMM_BOFS_BIT 18


static xrMM_Block getObjBlock(X2C_LINK obj)
{
   X2C_CARD32 ofs;
   ofs = (X2C_CARD32)X2C_LSH((X2C_CARD32)obj->_0.size&0xFFE00000UL,32,-18);
   return (xrMM_Block)(X2C_LINK)((X2C_ADDRESS)obj-(X2C_INT32)(X2C_INT32)ofs);
                
} /* end getObjBlock() */


extern void xrMM_setObjOfsLen(X2C_LINK * obj, X2C_CARD32 size,
                X2C_CARD32 ofs)
{
   (*obj)->_0.size = (X2C_CARD32)X2C_LSH((X2C_CARD32)ofs,32,18)+size;
} /* end setObjOfsLen() */


static X2C_LINK splitFreeObj(X2C_LINK obj, X2C_CARD32 size)
{
   X2C_LINK rem;
   X2C_CARD32 remOfs;
   X2C_CARD32 remSize;
   rem = (X2C_LINK)((X2C_ADDRESS)obj+(X2C_INT32)(X2C_INT32)size);
   remOfs = (X2C_CARD32)(obj->_0.tags&0xFFFFC007UL)+(X2C_CARD32)
                X2C_LSH((X2C_CARD32)size,32,18);
   remSize = xrMM_getHpObjSize(obj)-size;
   rem->_0.size = remOfs+remSize;
   obj->_0.size -= remSize;
   return rem;
} /* end splitFreeObj() */


static X2C_ADDRESS rt_alloc(X2C_CARD32 size)
{
   if (size==16384UL) return xrBlockManager_alloc();
   else return X2C_malloc(size);
   return 0;
} /* end rt_alloc() */


extern void xrMM_NewBlock(X2C_CARD8 root, xrMM_Block * b, X2C_CARD32 size)
{
   X2C_CARD32 msz;
   X2C_ADDRESS m;
   msz = size+48UL;
   if (X2C_busymem+msz>X2C_maxmem) m = 0;
   else m = rt_alloc(msz);
   if (m==0) {
      *b = 0;
      return;
   }
   *b = (xrMM_Block)m;
   if (xrMM_blk_min==0 || X2C_adr_lss(m, xrMM_blk_min)) xrMM_blk_min = m;
   m = (X2C_ADDRESS)((X2C_ADDRESS)m+(X2C_INT32)msz);
   if (xrMM_blk_max==0 || X2C_adr_gtr(m, xrMM_blk_max)) xrMM_blk_max = m;
   (*b)->size = size;
   (*b)->fsum = size;
   (*b)->list = 0;
   (*b)->root = root;
   if (X2C_IN((X2C_INT32)root,32,0x200001UL)) {
      (*b)->mem = (X2C_ADDRESS)(xrMM_Block)((X2C_ADDRESS)*b+(X2C_INT32)
                (X2C_INT32)size);
   }
   else (*b)->mem = xrMM_getFirstBlockAdr(*b);
   (*b)->magic = 305419896UL;
   X2C_busymem += (*b)->size+48UL;
   (*b)->next = xrMM_f_blocks[root]->next;
   (*b)->prev = xrMM_f_blocks[root];
   (*b)->prev->next = *b;
   (*b)->next->prev = *b;
} /* end NewBlock() */


extern void xrMM_MakeBusy(xrMM_Block b)
{
   if (b->list) X2C_ASSERT_F(102UL);
   b->next->prev = b->prev;
   b->prev->next = b->next;
   b->next = xrMM_b_blocks[b->root]->next;
   b->prev = xrMM_b_blocks[b->root];
   b->prev->next = b;
   b->next->prev = b;
} /* end MakeBusy() */


extern void xrMM_MakeFree(xrMM_Block b)
{
   b->next->prev = b->prev;
   b->prev->next = b->next;
   b->next = xrMM_f_blocks[b->root]->next;
   b->prev = xrMM_f_blocks[b->root];
   b->prev->next = b;
   b->next->prev = b;
} /* end MakeFree() */

static X2C_CARD32 xrMM_POOL_SIZE = 2048UL;

struct freeObjDesc;

typedef struct freeObjDesc * freeObj;


struct freeObjDesc {
   struct X2C_LINK_STR link;
   freeObj prev;
   freeObj next;
};

static struct freeObjDesc dummy_fo[2048];

static freeObj pool[2048];


static X2C_CARD32 getRootBySize(X2C_CARD32 size)
{
   return (size-1UL)/8UL;
} /* end getRootBySize() */


static X2C_CARD32 getRoot(X2C_LINK obj)
{
   return getRootBySize(xrMM_getHpObjSize(obj));
} /* end getRoot() */


static X2C_LINK extractFromPool(X2C_CARD32 root)
{
   freeObj obj;
   obj = pool[root]->next;
   obj->next->prev = obj->prev;
   obj->prev->next = obj->next;
   return (X2C_LINK)obj;
} /* end extractFromPool() */


static void splitNonPooledFreeObj(X2C_LINK obj, X2C_CARD32 size)
{
   xrMM_foManager_add(splitFreeObj(obj, size));
} /* end splitNonPooledFreeObj() */


static X2C_LINK splitNewBlock(X2C_CARD32 size)
{
   X2C_LINK f;
   xrMM_Block x;
   xrMM_NewBlock(0U, &x, 16336UL);
   if (x==0) f = 0;
   else {
      f = (X2C_LINK)xrMM_getFirstBlockAdr(x);
      xrMM_setObjOfsLen(&f, 16336UL, (X2C_ADDRESS)f-(X2C_ADDRESS)x);
      f->_0.tags |= 0x20000UL;
      splitNonPooledFreeObj(f, size);
   }
   return f;
} /* end splitNewBlock() */


extern void xrMM_foManager_add(X2C_LINK obj)
{
   freeObj fo;
   X2C_CARD32 root;
   fo = (freeObj)obj;
   root = getRoot(obj);
   fo->next = pool[root]->next;
   fo->prev = pool[root];
   fo->prev->next = fo;
   fo->next->prev = fo;
   xrDTree_ins(root);
} /* end foManager_add() */


extern void xrMM_foManager_del(X2C_LINK obj)
{
   freeObj fo;
   fo = (freeObj)obj;
   fo->next->prev = fo->prev;
   fo->prev->next = fo->next;
   xrDTree_del(getRoot(obj));
} /* end foManager_del() */

#define xrMM_LDV_Snowman_pad 3


static X2C_LINK foManager_get(X2C_CARD32 size)
{
   X2C_CARD32 root;
   X2C_CARD32 g_root;
   X2C_LINK obj;
   root = getRootBySize(size);
   if (pool[root]->next==pool[root]) {
      g_root = xrDTree_find(root);
      if (g_root==X2C_max_longcard) obj = splitNewBlock(size);
      else {
         obj = extractFromPool(g_root);
         if (g_root-root>3UL) splitNonPooledFreeObj(obj, size);
      }
   }
   else {
      obj = extractFromPool(root);
      xrDTree_del(root);
   }
   return obj;
} /* end foManager_get() */


static void foManager_init(void)
{
   X2C_CARD32 i;
   xrDTree_init();
   for (i = 0UL; i<=2047UL; i++) {
      dummy_fo[i].prev = &dummy_fo[i];
      dummy_fo[i].next = dummy_fo[i].prev;
      pool[i] = &dummy_fo[i];
   } /* end for */
} /* end foManager_init() */


static void small_alloc(X2C_CARD8 root, X2C_LINK * l, xrMM_Block * z,
                X2C_CARD32 size)
{
   xrMM_Block y;
   xrMM_Block x;
   y = xrMM_f_blocks[root];
   x = y->next;
   if (x==y) {
      xrMM_NewBlock(root, &x, 16336UL);
      if (x==0) {
         *z = 0;
         *l = 0;
         return;
      }
   }
   if (x->list==0) {
      *l = (X2C_LINK)x->mem;
      x->mem = (X2C_ADDRESS)(X2C_LINK)((X2C_ADDRESS)*l+(X2C_INT32)(X2C_INT32)
                size);
   }
   else {
      *l = x->list;
      x->list = (*l)->_.next;
      (*l)->_0.tags &= ~0x20000UL;
   }
   x->fsum -= size;
   if (x->fsum<size && x->list==0) xrMM_MakeBusy(x);
   *z = x;
} /* end small_alloc() */


static void large_alloc(X2C_LINK * l, xrMM_Block * x, X2C_CARD32 size)
{
   xrMM_NewBlock(21U, x, size);
   if (*x==0) *l = 0;
   else {
      *l = (X2C_LINK)xrMM_getFirstBlockAdr(*x);
      (*l)->_0.tags = 0UL;
   }
} /* end large_alloc() */


static void Collect0(X2C_CARD32 sz)
{
   if (!xrMM_GCAUTO) return;
   xrMM_GCInvoker = 0;
   xrMM_StackEnd4GC = 0;
   xrMM_SizeToAlloc = sz;
   xrMM_COLLECTOR();
} /* end Collect() */


extern void xrMM_allocate(X2C_LINK * l, X2C_CARD32 size, X2C_BOOLEAN clean)
{
   X2C_CARD32 sz;
   xrMM_Block b;
   X2C_CARD32 n;
   X2C_CARD32 tryCnt;
   xrMM_HeapLock();
   sz = xrMM_Align(size);
   if (sz<=160UL) {
      n = sz/8UL;
      tryCnt = 0UL;
      for (;;) {
         small_alloc((X2C_CARD8)n, l, &b, sz);
         if (*l) break;
         if (tryCnt==2UL) {
            xrMM_HeapUnlock();
            return;
         }
         xrMM_DoDefrag = tryCnt==1UL;
         Collect0(sz);
         ++tryCnt;
      }
      xrMM_setObjOfsLen(l, sz, (X2C_ADDRESS)*l-(X2C_ADDRESS)b);
   }
   else if (sz>16168UL) {
      tryCnt = 0UL;
      for (;;) {
         large_alloc(l, &b, sz);
         if (*l) break;
         if (tryCnt==2UL) {
            xrMM_HeapUnlock();
            return;
         }
         xrMM_DoDefrag = tryCnt==1UL;
         Collect0(sz);
         ++tryCnt;
      }
      b->fsum = sz;
      (*l)->_0.tags = 0UL;
   }
   else {
      tryCnt = 0UL;
      for (;;) {
         *l = foManager_get(sz);
         if (*l) break;
         if (tryCnt==2UL) {
            xrMM_HeapUnlock();
            return;
         }
         xrMM_DoDefrag = tryCnt==1UL;
         Collect0(sz);
         ++tryCnt;
      }
      sz = xrMM_getHpObjSize(*l);
   }
   if (clean) {
      X2C_ZEROMEM((X2C_ADDRESS)(X2C_LINK)((X2C_ADDRESS)*l+(X2C_INT32)8L),
                (sz-8UL)/4UL);
   }
   (*l)->_0.tags &= ~0x20000UL;
   (*l)->_.td = x2c_td_null;
   (*l)->_0.tags |= 0x8000UL;
   X2C_usedmem += sz;
   ++X2C_objects;
   xrMM_HeapUnlock();
} /* end allocate() */


static void rt_free(X2C_ADDRESS adr, X2C_CARD32 size)
{
   if (size==16384UL) xrBlockManager_free(adr);
   else X2C_free(adr, size);
} /* end rt_free() */


static void _free_block(xrMM_Block x)
{
   X2C_CARD32 blockSize;
   blockSize = x->size;
   x->next->prev = x->prev;
   x->prev->next = x->next;
   X2C_busymem -= blockSize+48UL;
   rt_free((X2C_ADDRESS)x, blockSize+48UL);
} /* end _free_block() */


extern void xrMM_free_block(xrMM_Block x)
{
   xrMM_HeapLock();
   _free_block(x);
   xrMM_HeapUnlock();
} /* end free_block() */


extern void xrMM_dealloc(X2C_LINK objd)
{
   xrMM_Block x;
   X2C_CARD32 size;
   X2C_LINK _1stObj;
   X2C_LINK _2ndObj;
   X2C_LINK rObj;
   X2C_CARD32 eom;
   X2C_ADDRESS tmp;
   size = xrMM_getHpObjSize(objd);
   x = getObjBlock(objd);
   xrMM_HeapLock();
   if ((X2C_CARD32)x->root==0UL) {
      _1stObj = (X2C_LINK)xrMM_getFirstBlockAdr(x);
      _2ndObj = (X2C_LINK)((X2C_ADDRESS)_1stObj+(X2C_INT32)(X2C_INT32)
                xrMM_getHpObjSize(_1stObj));
      if (objd==_2ndObj && (0x20000UL & _1stObj->_0.tags)) {
         xrMM_foManager_del(_1stObj);
         _1stObj->_0.size += size;
         objd = _1stObj;
      }
      eom = *(X2C_CARD32 *)(tmp = xrMM_getLastBlockAdr1(x),&tmp);
      for (;;) {
         rObj = (X2C_LINK)((X2C_ADDRESS)objd+(X2C_INT32)(X2C_INT32)
                xrMM_getHpObjSize(objd));
         if (*(X2C_CARD32 *) &rObj>=eom || (0x20000UL & rObj->_0.tags)==0) {
            break;
         }
         objd->_0.size += xrMM_getHpObjSize(rObj);
         xrMM_foManager_del(rObj);
      }
      if (xrMM_getHpObjSize(objd)==16336UL) _free_block(x);
      else {
         stampObjAsFree(objd, xrMM_getHpObjSize(objd));
         xrMM_foManager_add(objd);
      }
   }
   else if ((X2C_CARD32)x->root==21UL) _free_block(x);
   else {
      x->fsum += size;
      if (x->fsum==x->size) _free_block(x);
      else {
         objd->_.next = x->list;
         x->list = objd;
         stampObjAsFree(objd, xrMM_getHpObjSize(objd));
      }
   }
   xrMM_HeapUnlock();
} /* end dealloc() */


static void CheckOneBlock(xrMM_Block head)
{
} /* end CheckOneBlock() */


extern void xrMM_CheckHeap(void)
{
   X2C_CARD32 i;
   xrMM_Block b;
   X2C_CARD32 no;
   no = 0UL;
   for (i = 0UL; i<=21UL; i++) {
      b = xrMM_f_blocks[i]->next;
      while (b!=xrMM_f_blocks[i]) {
         if (i!=21UL) CheckOneBlock(b);
         b = b->next;
         ++no;
      }
      b = xrMM_b_blocks[i]->next;
      while (b!=xrMM_b_blocks[i]) {
         CheckOneBlock(b);
         b = b->next;
         ++no;
      }
   } /* end for */
} /* end CheckHeap() */


extern void X2C_InitDesc(xrMM_Dynarr d, size_t * size, size_t lens[],
                size_t dims)
{
   X2C_CARD32 i;
   X2C_CARD32 tmp;
   d->n[(dims-1U)*2U] = lens[0UL];
   tmp = dims-1U;
   i = 1UL;
   if (i<=tmp) for (;; i++) {
      *size =  *size*lens[dims-i];
      d->n[i*2UL-1UL] = *size;
      d->n[(dims-i)*2UL-2UL] = lens[i];
      if (i==tmp) break;
   } /* end for */
   *size =  *size*lens[0UL];
} /* end X2C_InitDesc() */


struct D {
   X2C_ADDRESS a;
   size_t n[1];
};


extern size_t xrMM_DynarrDescSize(size_t i)
{
   return 8U+i*2U*4U;
} /* end DynarrDescSize() */


extern void xrMM_stampAsNonConservative(X2C_ADDRESS obj)
{
   X2C_LINK l;
   l = (X2C_LINK)(X2C_ADDRESS)((X2C_ADDRESS)obj-(X2C_INT32)8UL);
   if ((l->_0.tags&0xFFE00000UL)==0UL) l->_0.tags |= 0x4UL;
} /* end stampAsNonConservative() */

static void DummyCollector(void);


static void DummyCollector(void)
{
} /* end DummyCollector() */

static X2C_ADDRESS null_offs[1];

static X2C_ADDRESS ptr_offs[2];

static struct X2C_MD_STR mod_desc;

typedef X2C_CHAR * str;


extern void xrMM_ini_type_desc(X2C_TD * x, X2C_CHAR nm[], X2C_CARD32 nm_len,
                X2C_CARD32 sz, X2C_ADDRESS offs)
{
   X2C_INT32 i;
   size_t len;
   str X0;
   *x = (X2C_TD)X2C_malloc(112UL);
   if (*x==0) X2C_TRAP_F((X2C_INT32)X2C_noMemoryException);
   (*x)->offs = (X2C_ppVOID)offs;
   (*x)->size = sz;
   len = X2C_LENGTH(nm,nm_len)+1UL;
   (*x)->name = (X2C_pCHAR)X2C_malloc(len);
   X0 = (str)(*x)->name;
   if (X0==0) X2C_TRAP_F((X2C_INT32)X2C_noMemoryException);
   X2C_COPY(nm,nm_len,X0,10000u);
   (*x)->module = &mod_desc;
   (*x)->methods = 0;
   (*x)->level = 0;
   for (i = 0L; i<=15L; i++) {
      (*x)->base[i] = 0;
   } /* end for */
   (*x)->proc = 0;
   (*x)->succ = 0;
   (*x)->link = 0;
   (*x)->tail = 0;
   (*x)->res = 0x093678150UL;
   (*x)->next = mod_desc.types;
   mod_desc.types = *x;
} /* end ini_type_desc() */

static struct xrMM_BlockDesc BlocksHeap[44];


extern X2C_BOOLEAN X2C_GC_INIT(X2C_BOOLEAN auto0, X2C_CARD32 thres,
                X2C_CARD32 heap)
{
   X2C_CARD32 j;
   X2C_CARD32 i;
   xrMM_Block x;
   x = (xrMM_Block) &i;
   memset((X2C_ADDRESS) &x,0,4UL);
   if (x) X2C_ASSERT_F(100UL);
   xrMM_FloatingHeaplimit = 0;
   if (heap==0UL) {
      xrMM_FloatingHeaplimit = 1;
      heap = 10485760UL;
   }
   X2C_InitHeap(heap, 0);
   if (!xrBlockManager_init(16384UL)) {
      XDSLIB_INITIALIZATION_FAILED = 1;
      return 0;
   }
   if (heap>0UL && (X2C_CARD32)heap>1073741824UL) heap = 1073741824UL;
   foManager_init();
   xrMM_O2MM_init = 0;
   xrMM_COLLECTOR = DummyCollector;
   xrMM_DoDefrag = 0;
   xrMM_GCAUTO = auto0;
   xrMM_GCTHRESCNT = 0L;
   xrMM_anchorTracing = 0;
   xrMM_anchorWeightThreshold = 0UL;
   xrMM_heapTracing = 0;
   xrMM_heapTracingThreshold = 0UL;
   xrMM_X2C_AlwaysDefrag = 0;
   if (thres<=0UL) X2C_threshold = X2C_max_longcard;
   else X2C_threshold = thres;
   if (heap<=0UL) X2C_maxmem = X2C_max_longcard;
   else X2C_maxmem = heap;
   X2C_MODULES = 0;
   ptr_offs[0U] = X2C_BASE;
   ptr_offs[1U] = X2C_OFS_END;
   null_offs[0U] = X2C_OFS_END;
   mod_desc.types = 0;
   xrMM_ini_type_desc(&x2c_td_ptr, "$PTR", 5ul, 4UL, (X2C_ADDRESS)ptr_offs);
   xrMM_ini_type_desc(&x2c_td_null, "$NULL", 6ul, 1UL,
                (X2C_ADDRESS)null_offs);
   j = 0UL;
   for (i = 0UL; i<=21UL; i++) {
      x = &BlocksHeap[i*2UL];
      x->prev = x;
      x->next = x;
      x->size = 0UL;
      x->root = (X2C_CARD8)i;
      x->fsum = 0UL;
      x->list = 0;
      x->magic = 0UL;
      xrMM_f_blocks[i] = x;
      x = &BlocksHeap[i*2UL+1UL];
      x->prev = x;
      x->next = x;
      x->size = 0UL;
      x->root = (X2C_CARD8)i;
      x->fsum = 0UL;
      x->list = 0;
      x->magic = 0UL;
      xrMM_b_blocks[i] = x;
   } /* end for */
   for (i = 1UL; i<=20UL; i++) {
      xrMM_parts[i] = 16336UL/(i*8UL);
   } /* end for */
   X2C_objects = 0UL;
   X2C_usedmem = 0UL;
   X2C_busymem = 0UL;
   X2C_busylheap = 0UL;
   return 1;
} /* end X2C_GC_INIT() */


extern void X2C_GC_INCREASE(X2C_BOOLEAN auto0, X2C_CARD32 thres,
                X2C_CARD32 heap)
{
   if (heap==0UL) {
      xrMM_FloatingHeaplimit = 1;
      heap = 10485760UL;
   }
   if (heap>0UL && (X2C_CARD32)heap>1073741824UL) heap = 1073741824UL;
   if (thres<=0UL) X2C_threshold = X2C_max_longcard;
   else if (X2C_threshold<(X2C_CARD32)thres) X2C_threshold = thres;
   xrMM_GCAUTO = auto0 || xrMM_GCAUTO;
   if (heap>0UL && X2C_maxmem<(X2C_CARD32)heap) {
      X2C_maxmem = heap;
      X2C_InitHeap(heap, 1);
   }
} /* end X2C_GC_INCREASE() */


extern void X2C_COLLECT(void)
{
   xrMM_HeapLock();
   xrMM_GCInvoker = 0;
   xrMM_StackEnd4GC = 0;
   xrMM_SizeToAlloc = 0UL;
   xrMM_COLLECTOR();
   xrMM_HeapUnlock();
} /* end X2C_COLLECT() */


extern void X2C_MemoryManager_exit(void)
{
   xrBlockManager_exit();
   X2C_DestroyHeap();
} /* end X2C_MemoryManager_exit() */


extern void xrMM_BEGIN(void)
{
   static int xrMM_init = 0;
   if (xrMM_init) return;
   xrMM_init = 1;
   if (sizeof(struct xrMM__D0)!=64) X2C_ASSERT(0);
   if (sizeof(xrMM_Block)!=4) X2C_ASSERT(0);
   if (sizeof(struct xrMM_BlockDesc)!=36) X2C_ASSERT(0);
   if (sizeof(xrMM_Dynarr)!=4) X2C_ASSERT(0);
   if (sizeof(xrMM_GarbageCollector)!=4) X2C_ASSERT(0);
   if (sizeof(freeObj)!=4) X2C_ASSERT(0);
   if (sizeof(struct freeObjDesc)!=16) X2C_ASSERT(0);
   xrDTree_BEGIN();
   xrBlockManager_BEGIN();
}
