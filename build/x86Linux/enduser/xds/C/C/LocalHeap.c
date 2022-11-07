/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)LocalHeap.c Nov  7 22:55:49 2022" */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef LocalHeap_H_
#include "LocalHeap.h"
#endif
#define LocalHeap_C_
#ifndef Storage_H_
#include "Storage.h"
#endif
#ifndef xrBlockManager_H_
#include "xrBlockManager.h"
#endif
#ifndef xrMM_H_
#include "xrMM.h"
#endif
#ifndef xmRTS_H_
#include "xmRTS.h"
#endif

#define LocalHeap_ALIGN 4

#define LocalHeap_PADDING 4

#define LocalHeap_BlockSize 4093

#define LocalHeap_MaxFree 128

struct FreeRecord;

typedef struct FreeRecord * FreePtr;


struct FreeRecord {
   FreePtr next;
};

struct BlockRecord;

typedef struct BlockRecord * BlockPtr;


struct BlockRecord {
   BlockPtr next;
   X2C_INT32 n;
   X2C_INT32 v[4093];
};

struct _0;


struct _0 {
   X2C_INT32 Used;
   X2C_BOOLEAN Split;
   FreePtr Headers[128];
   BlockPtr Current;
   X2C_INT32 NFree;
   BlockPtr Large;
};


static void Collect0(void)
{
   if (!xrMM_GCAUTO) return;
   xrMM_HeapUnlock();
   xrMM_GCInvoker = 0;
   xrMM_StackEnd4GC = 0;
   xrMM_SizeToAlloc = 16384UL;
   xrMM_COLLECTOR();
   xrMM_HeapLock();
} /* end Collect() */


static X2C_ADDRESS alloc(void)
{
   X2C_ADDRESS p;
   if (X2C_busymem+16384UL>X2C_maxmem) p = 0;
   else {
      p = xrBlockManager_alloc();
      X2C_busymem += 16384UL;
      X2C_busylheap += 16384UL;
   }
   return p;
} /* end alloc() */


static X2C_ADDRESS allocBlock(void)
{
   X2C_ADDRESS p;
   X2C_CARD32 tryCnt;
   xrMM_HeapLock();
   tryCnt = 0UL;
   for (;;) {
      p = alloc();
      if (p || tryCnt==2UL) break;
      xrMM_DoDefrag = tryCnt==1UL;
      Collect0();
      ++tryCnt;
   }
   xrMM_HeapUnlock();
   return p;
} /* end allocBlock() */


static void freeBlock(X2C_ADDRESS adr, X2C_BOOLEAN destroy)
{
   X2C_busymem -= 16384UL;
   X2C_busylheap -= 16384UL;
   xrBlockManager_free(adr);
} /* end freeBlock() */


extern void LocalHeap_ALLOCATE(LocalHeap_heapID h, X2C_ADDRESS * p,
                X2C_INT32 n)
{
   BlockPtr q;
   FreePtr r;
   X2C_INT32 i;
   X2C_BOOLEAN w;
   struct _0 * anonym;
   { /* with */
      struct _0 * anonym = (struct _0 *)h;
      n = X2C_DIV((n+4L)-1L,4L);
      if (n<128L && anonym->Headers[n]) {
         *p = (X2C_ADDRESS)anonym->Headers[n];
         anonym->Headers[n] = anonym->Headers[n]->next;
         anonym->Used += n;
         X2C_usedlheap += (X2C_CARD32)(n*4L);
      }
      else if (n<=anonym->NFree) {
         anonym->NFree -= n;
         *p = (X2C_ADDRESS) &anonym->Current->v[anonym->NFree];
         anonym->Used += n;
         X2C_usedlheap += (X2C_CARD32)(n*4L);
      }
      else if (n>4093L) {
         Storage_ALLOCATE((X2C_ADDRESS *) &q, 8UL+(X2C_CARD32)n*4UL);
         if (q==0) {
            *p = 0;
            return;
         }
         q->n = n;
         q->next = anonym->Large;
         anonym->Large = q;
         *p = (X2C_ADDRESS) &q->v[0U];
      }
      else {
         w = 0;
         for (;;) {
            if ((n>=128L || w) || !anonym->Split) {
               q = (BlockPtr)allocBlock();
               if (q) {
                  q->n = 4093L;
                  q->next = anonym->Current;
                  anonym->Current = q;
                  anonym->NFree = 4093L-n;
                  *p = (X2C_ADDRESS) &q->v[anonym->NFree];
                  anonym->Split = 0;
                  anonym->Used += n;
                  X2C_usedlheap += (X2C_CARD32)(n*4L);
                  return;
               }
               if (n>=128L) {
                  *p = 0;
                  return;
               }
            }
            for (i = n+1L; i<=127L; i++) {
               if (anonym->Headers[i]) {
                  *p = (X2C_ADDRESS)anonym->Headers[i];
                  anonym->Headers[i] = anonym->Headers[i]->next;
                  r = (FreePtr)(X2C_ADDRESS)((X2C_ADDRESS)*p+(X2C_INT32)
                (X2C_CARD32)(n*4L));
                  r->next = anonym->Headers[i-n];
                  anonym->Headers[i-n] = r;
                  anonym->Split = 1;
                  anonym->Used += n;
                  X2C_usedlheap += (X2C_CARD32)(n*4L);
                  return;
               }
            } /* end for */
            if (w || !anonym->Split) {
               *p = 0;
               return;
            }
            anonym->Split = 1;
            w = 1;
         }
      }
   }
} /* end ALLOCATE() */


extern void LocalHeap_DEALLOCATE(LocalHeap_heapID h, X2C_ADDRESS * p,
                X2C_INT32 n)
{
   FreePtr q;
   struct _0 * anonym;
   { /* with */
      struct _0 * anonym = (struct _0 *)h;
      n = X2C_DIV((n+4L)-1L,4L);
      if (n<128L) {
         q = (FreePtr)*p;
         q->next = anonym->Headers[n];
         anonym->Headers[n] = q;
      }
      anonym->Used -= n;
      X2C_usedlheap -= (X2C_CARD32)(n*4L);
      *p = 0;
   }
} /* end DEALLOCATE() */


extern void LocalHeap_DEALLOCATE_ALL(LocalHeap_heapID h)
{
   X2C_INT32 i;
   BlockPtr q;
   BlockPtr p;
   struct _0 * anonym;
   { /* with */
      struct _0 * anonym = (struct _0 *)h;
      p = anonym->Current->next;
      while (p) {
         q = p->next;
         freeBlock((X2C_ADDRESS)p, 0);
         p = q;
      }
      anonym->NFree = anonym->Current->n;
      anonym->Current->next = 0;
      while (anonym->Large) {
         q = anonym->Large->next;
         Storage_DEALLOCATE((X2C_ADDRESS *) &anonym->Large,
                8UL+(X2C_CARD32)anonym->Large->n*4UL);
         anonym->Large = q;
      }
      for (i = 0L; i<=127L; i++) {
         anonym->Headers[i] = 0;
      } /* end for */
      X2C_usedlheap -= (X2C_CARD32)(anonym->Used*4L);
      anonym->Used = 0L;
      anonym->Split = 0;
   }
} /* end DEALLOCATE_ALL() */


extern void LocalHeap_Create(LocalHeap_heapID * h)
{
   X2C_INT32 i;
   struct _0 * anonym;
   Storage_ALLOCATE((X2C_ADDRESS *)h, 532UL);
   { /* with */
      struct _0 * anonym = (struct _0 *)*h;
      for (i = 0L; i<=127L; i++) {
         anonym->Headers[i] = 0;
      } /* end for */
      anonym->Current = (BlockPtr)allocBlock();
      anonym->Current->n = 4093L;
      anonym->Current->next = 0;
      anonym->NFree = 4093L;
      anonym->Split = 0;
      anonym->Used = 0L;
      anonym->Large = 0;
   }
} /* end Create() */


extern void LocalHeap_Destroy(LocalHeap_heapID h)
{
   LocalHeap_DEALLOCATE_ALL(h);
   freeBlock((X2C_ADDRESS)((struct _0 *)h)->Current, 1);
   Storage_DEALLOCATE((X2C_ADDRESS *) &h, 532UL);
} /* end Destroy() */


extern void LocalHeap_BEGIN(void)
{
   static int LocalHeap_init = 0;
   if (LocalHeap_init) return;
   LocalHeap_init = 1;
   if (sizeof(LocalHeap_heapID)!=4) X2C_ASSERT(0);
   if (sizeof(FreePtr)!=4) X2C_ASSERT(0);
   if (sizeof(struct FreeRecord)!=4) X2C_ASSERT(0);
   if (sizeof(BlockPtr)!=4) X2C_ASSERT(0);
   if (sizeof(struct BlockRecord)!=16380) X2C_ASSERT(0);
   if (sizeof(struct _0)!=532) X2C_ASSERT(0);
   xrMM_BEGIN();
   xrBlockManager_BEGIN();
   Storage_BEGIN();
}

