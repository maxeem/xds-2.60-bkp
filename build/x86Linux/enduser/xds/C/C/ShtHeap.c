/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)ShtHeap.c Nov 19  1:11:54 2022" */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef ShtHeap_H_
#include "ShtHeap.h"
#endif
#define ShtHeap_C_
#ifndef EXCEPTIONS_H_
#include "EXCEPTIONS.h"
#endif
#ifndef Strings_H_
#include "Strings.h"
#endif

X2C_BOOLEAN ShtHeap_Clear;
X2C_BOOLEAN ShtHeap_Check;
X2C_BOOLEAN ShtHeap_Debug;
#define ShtHeap_HpMagic 0x0DEADFACE

#define ShtHeap_PMagic 0x0ACE0FACE

struct PCB;

typedef struct PCB * pPCB;


struct PCB {
   X2C_CARD32 magic;
   X2C_CARD32 isFree;
   X2C_CARD32 length;
   pPCB prevP;
   pPCB nextP;
   X2C_LOC memory[4];
};

#define ShtHeap_lPCB sizeof(struct PCB)

#define ShtHeap_ltPCB (sizeof(struct PCB)-4)

struct HCB;

typedef struct HCB * pHCB;


struct HCB {
   X2C_CARD32 magic;
   pPCB bFMList;
   pPCB eFMList;
   X2C_CARD32 total;
   X2C_ADDRESS limit;
};

#define ShtHeap_lHCB sizeof(struct HCB)

static EXCEPTIONS_ExceptionSource source;


static void RAISE(X2C_CARD32 n, const X2C_CHAR s[], X2C_CARD32 s_len)
{
   X2C_CHAR m[80];
   Strings_Concat("ShtHeap.", 9ul, s, s_len, m, 80ul);
   EXCEPTIONS_RAISE(source, n, m, 80ul);
} /* end RAISE() */


extern X2C_BOOLEAN ShtHeap_IsShtHeapException(void)
{
   return EXCEPTIONS_IsCurrentSource(source);
} /* end IsShtHeapException() */

static pHCB pHEAP;


static pPCB IncpPCB(X2C_ADDRESS p, X2C_CARD32 n)
{
   return (pPCB)(X2C_ADDRESS)((X2C_ADDRESS)p+(X2C_INT32)n);
} /* end IncpPCB() */


static pPCB CreateHPiece(X2C_ADDRESS P, X2C_CARD32 sz)
{
   pPCB pp;
   struct PCB * anonym;
   pp = (pPCB)P;
   { /* with */
      struct PCB * anonym = pp;
      anonym->magic = 0x0ACE0FACEUL;
      anonym->isFree = 1;
      anonym->nextP = 0;
      anonym->prevP = 0;
      anonym->length = sz;
   }
   return pp;
} /* end CreateHPiece() */


static void DelFPiece(pPCB pP)
{
   struct PCB * anonym;
   { /* with */
      struct PCB * anonym = pP;
      if (anonym->prevP) anonym->prevP->nextP = anonym->nextP;
      if (anonym->nextP) anonym->nextP->prevP = anonym->prevP;
      if (pP==pHEAP->bFMList) pHEAP->bFMList = anonym->nextP;
      if (pP==pHEAP->eFMList) pHEAP->eFMList = anonym->prevP;
   }
} /* end DelFPiece() */


static void MergeHPiece(pPCB * pObjP)
{
   pPCB pNextP;
   pPCB pPrevP;
   pPCB pP;
   pPrevP = 0;
   pP = IncpPCB((X2C_ADDRESS)pHEAP, sizeof(struct HCB));
   while (pP!=*pObjP) {
      pPrevP = pP;
      pP = IncpPCB((X2C_ADDRESS)pP, (sizeof(struct PCB)-4)+pP->length);
      if (*X2C_CAST(&pP,pPCB,X2C_CARD32,
                X2C_CARD32 *)>=*X2C_CAST(&pHEAP->limit,X2C_ADDRESS,
                X2C_CARD32,X2C_CARD32 *)) {
         RAISE(17UL, "Free: Argument is not pointer to heap or heap integrity\
 violation", 66ul);
      }
   }
   if (pPrevP && pPrevP->isFree) {
      DelFPiece(pPrevP);
      pPrevP->length += (*pObjP)->length+(sizeof(struct PCB)-4);
      pHEAP->total += sizeof(struct PCB)-4;
      *pObjP = pPrevP;
   }
   pNextP = IncpPCB((X2C_ADDRESS)*pObjP,
                (sizeof(struct PCB)-4)+(*pObjP)->length);
   if (*X2C_CAST(&pNextP,pPCB,X2C_CARD32,
                X2C_CARD32 *)<*X2C_CAST(&pHEAP->limit,X2C_ADDRESS,X2C_CARD32,
                X2C_CARD32 *) && pNextP->isFree) {
      DelFPiece(pNextP);
      (*pObjP)->length += pNextP->length+(sizeof(struct PCB)-4);
      pHEAP->total += sizeof(struct PCB)-4;
   }
} /* end MergeHPiece() */


static void InsHPiece(pPCB pfp)
{
   pPCB pPrevP;
   pPCB pP;
   X2C_CARD32 sz;
   struct HCB * anonym;
   pfp->isFree = 1;
   { /* with */
      struct HCB * anonym = pHEAP;
      sz = pfp->length;
      pP = anonym->bFMList;
      pPrevP = 0;
      while (pP && pP->length<sz) {
         pPrevP = pP;
         pP = pP->nextP;
      }
      pfp->prevP = pPrevP;
      pfp->nextP = pP;
      if (pPrevP==0) anonym->bFMList = pfp;
      else pPrevP->nextP = pfp;
      if (pP==0) anonym->eFMList = pfp;
      else pP->prevP = pfp;
   }
} /* end InsHPiece() */


extern void ShtHeap_Initialize(X2C_ADDRESS H, X2C_CARD32 sz)
{
   struct HCB * anonym;
   sz = (((sz+4UL)-1UL)/4UL)*4UL;
   if (sz<sizeof(struct HCB)+sizeof(struct PCB)) {
      RAISE(0UL, "Initialize: Size Too Small", 27ul);
   }
   pHEAP = (pHCB)H;
   { /* with */
      struct HCB * anonym = pHEAP;
      anonym->magic = 0x0DEADFACEUL;
      anonym->bFMList = 0;
      anonym->limit = (X2C_ADDRESS)((X2C_ADDRESS)H+(X2C_INT32)sz);
      sz -= (sizeof(struct PCB)-4)+sizeof(struct HCB);
      anonym->total = sz;
      InsHPiece(CreateHPiece((X2C_ADDRESS)((X2C_ADDRESS)H+(X2C_INT32)
                sizeof(struct HCB)), sz));
   }
} /* end Initialize() */


extern void ShtHeap_Allocate(X2C_ADDRESS H, X2C_ADDRESS * P, X2C_CARD32 sz)
{
   pPCB pP;
   X2C_CARD32 rest;
   pHEAP = (pHCB)H;
   if (pHEAP->magic!=0x0DEADFACEUL) {
      RAISE(0UL, "Allocate:  Argument is not pointer to heap", 43ul);
   }
   if (ShtHeap_Debug) ShtHeap_Test(H);
   sz = (((sz+4UL)-1UL)/4UL)*4UL;
   if (sz==0UL) RAISE(0UL, "Allocate: Size Too Small", 25ul);
   pP = pHEAP->bFMList;
   while (pP && pP->length<sz) pP = pP->nextP;
   if (pP==0) {
      if (ShtHeap_Check) RAISE(0UL, "Allocate: Out Of Memory", 24ul);
      else {
         *P = 0;
         return;
      }
   }
   DelFPiece(pP);
   if (pP->length>=4UL+sz+(sizeof(struct PCB)-4)) {
      rest = pP->length-(sz+(sizeof(struct PCB)-4));
      pP->length = rest;
      InsHPiece(pP);
      pP = IncpPCB((X2C_ADDRESS)pP, (sizeof(struct PCB)-4)+rest);
      pP = CreateHPiece((X2C_ADDRESS)pP, sz);
      pHEAP->total -= (sizeof(struct PCB)-4)+sz;
   }
   else pHEAP->total -= pP->length;
   pP->isFree = 0;
   *P = (X2C_ADDRESS)pP->memory;
   if (ShtHeap_Clear) memset(*P,(X2C_LOC)0U,pP->length);
} /* end Allocate() */


extern void ShtHeap_Free(X2C_ADDRESS H, X2C_ADDRESS * P, X2C_CARD32 sz)
{
   pPCB pP;
   pHEAP = (pHCB)H;
   pP = (pPCB)(X2C_ADDRESS)((X2C_ADDRESS)*P-(X2C_INT32)(sizeof(struct PCB)-4)
                );
   if (pHEAP->magic!=0x0DEADFACEUL) {
      RAISE(0UL, "Free: The first argument is not pointer to heap", 48ul);
   }
   if (pP->magic!=0x0ACE0FACEUL) {
      RAISE(0UL, "Free: The second argument is not pointer to block", 50ul);
   }
   if (pP->length<sz || pP->length>=sz+8UL+(sizeof(struct PCB)-4)) {
      RAISE(0UL, "Free: Invalid block size", 25ul);
   }
   if (ShtHeap_Debug) ShtHeap_Test(H);
   pHEAP->total += pP->length;
   MergeHPiece(&pP);
   InsHPiece(pP);
   *P = 0;
} /* end Free() */


extern X2C_CARD32 ShtHeap_Largest(X2C_ADDRESS H)
{
   pHEAP = (pHCB)H;
   if (pHEAP->magic!=0x0DEADFACEUL) {
      RAISE(0UL, "Largest: Argument is not pointer to heap", 41ul);
   }
   if (ShtHeap_Debug) ShtHeap_Test(H);
   if (pHEAP->eFMList==0) return 0UL;
   else return pHEAP->eFMList->length;
   return 0;
} /* end Largest() */


extern X2C_CARD32 ShtHeap_Total(X2C_ADDRESS H)
{
   struct HCB * anonym;
   pHEAP = (pHCB)H;
   { /* with */
      struct HCB * anonym = pHEAP;
      if (anonym->magic!=0x0DEADFACEUL) {
         RAISE(0UL, "Total: Argument is not pointer to heap", 39ul);
      }
      if (ShtHeap_Debug) ShtHeap_Test(H);
      if (anonym->bFMList==0) return 0UL;
      else return anonym->total;
   }
   return 0;
} /* end Total() */


extern void ShtHeap_Test(X2C_ADDRESS H)
{
   pPCB pPrevP;
   pPCB pP;
   pHEAP = (pHCB)H;
   if (pHEAP->magic!=0x0DEADFACEUL) {
      RAISE(0UL, "Test: Argument is not pointer to heap", 38ul);
   }
   if (pHEAP->total&3UL) RAISE(0UL, "Test: Non-aligned heap size", 28ul);
   pPrevP = 0;
   pP = pHEAP->bFMList;
   while (pP) {
      if (*X2C_CAST(&pP,pPCB,X2C_CARD32,
                X2C_CARD32 *)+pP->length+(sizeof(struct PCB)-4)
                >*X2C_CAST(&pHEAP->limit,X2C_ADDRESS,X2C_CARD32,
                X2C_CARD32 *)) {
         RAISE(0UL, "Test: Free block out of range", 30ul);
      }
      else if (*X2C_CAST(&pP,pPCB,X2C_CARD32,X2C_CARD32 *)&3UL) {
         RAISE(0UL, "Test: Non-aligned free block", 29ul);
      }
      else if (pP->length&3UL) {
         RAISE(0UL, "Test: Non-aligned free block size", 34ul);
      }
      else if (pPrevP && pPrevP->length>pP->length) {
         RAISE(0UL, "Test: Unordered free list", 26ul);
      }
      pPrevP = pP;
      pP = pP->nextP;
   }
   pP = IncpPCB((X2C_ADDRESS)pHEAP, sizeof(struct HCB));
   while (*X2C_CAST(&pP,pPCB,X2C_CARD32,
                X2C_CARD32 *)<*X2C_CAST(&pHEAP->limit,X2C_ADDRESS,X2C_CARD32,
                X2C_CARD32 *)) {
      if (pP->magic!=0x0ACE0FACEUL) {
         RAISE(17UL, "Test: Heap integrity violation", 31ul);
      }
      pP = IncpPCB((X2C_ADDRESS)pP, (sizeof(struct PCB)-4)+pP->length);
   }
} /* end Test() */


extern void ShtHeap_BEGIN(void)
{
   static int ShtHeap_init = 0;
   if (ShtHeap_init) return;
   ShtHeap_init = 1;
   Strings_BEGIN();
   EXCEPTIONS_BEGIN();
   EXCEPTIONS_AllocateSource(&source);
   ShtHeap_Clear = 0;
   ShtHeap_Check = 1;
   ShtHeap_Debug = 0;
}

