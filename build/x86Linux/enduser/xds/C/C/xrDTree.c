/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)xrDTree.c Nov 19  1:11:49 2022" */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef xrDTree_H_
#include "xrDTree.h"
#endif
#define xrDTree_C_

X2C_CARD32 xrDTree_dTree[4096];
#define xrDTree_LEFT 0

#define xrDTree_RIGHT 1

#define xrDTree_ROOT_INDEX 1

static X2C_CARD32 jumpTable[4096];


extern void xrDTree_ins(X2C_CARD32 root)
{
   X2C_CARD32 count;
   X2C_CARD32 i;
   i = 2048UL+root;
   for (count = 0UL; count<=11UL; count++) {
      ++xrDTree_dTree[i];
      i = i/2UL;
   } /* end for */
} /* end ins() */


extern void xrDTree_del(X2C_CARD32 root)
{
   X2C_CARD32 count;
   X2C_CARD32 i;
   i = 2048UL+root;
   for (count = 0UL; count<=11UL; count++) {
      --xrDTree_dTree[i];
      i = i/2UL;
   } /* end for */
} /* end del() */


extern X2C_CARD32 xrDTree_find(X2C_CARD32 root)
{
   X2C_CARD32 i1;
   X2C_CARD32 i;
   i = 2048UL+root;
   if ((i&1UL)==0UL) ++i;
   while (xrDTree_dTree[i]==0UL) {
      i = jumpTable[i];
      if (i==X2C_max_longcard) return X2C_max_longcard;
   }
   i1 = i;
   while (i1) {
      --xrDTree_dTree[i1];
      i1 = i1/2UL;
   }
   while (i<2048UL) {
      i = i*2UL;
      if (xrDTree_dTree[i+0UL]==0UL) ++i;
      --xrDTree_dTree[i];
   }
   return i-2048UL;
} /* end find() */


extern void xrDTree_weakIns(X2C_CARD32 root)
{
   ++xrDTree_dTree[2048UL+root];
} /* end weakIns() */


extern void xrDTree_weakDel(X2C_CARD32 root)
{
   --xrDTree_dTree[2048UL+root];
} /* end weakDel() */


extern void xrDTree_recalc(void)
{
   X2C_CARD32 i;
   for (i = 2047UL; i>=1UL; i--) {
      xrDTree_dTree[i] = xrDTree_dTree[i*2UL+0UL]+xrDTree_dTree[i*2UL+1UL];
   } /* end for */
} /* end recalc() */

static X2C_CARD32 xrDTree_jumpLevelEnd = 1023UL;


static void initJumpTable(void)
{
   X2C_CARD32 root;
   X2C_CARD32 i;
   for (i = 1UL; i<=4095UL; i++) {
      jumpTable[i] = X2C_max_longcard;
   } /* end for */
   for (root = 1UL; root<=1023UL; root++) {
      i = root*2UL;
      while (i<2048UL) {
         i = i*2UL+1UL;
         jumpTable[i] = root*2UL+1UL;
      }
   } /* end for */
} /* end initJumpTable() */


static void initDTree(void)
{
   X2C_CARD32 i;
   for (i = 1UL; i<=4095UL; i++) {
      xrDTree_dTree[i] = 0UL;
   } /* end for */
} /* end initDTree() */


extern void xrDTree_init(void)
{
   initJumpTable();
   initDTree();
} /* end init() */


extern void xrDTree_BEGIN(void)
{
   static int xrDTree_init = 0;
   if (xrDTree_init) return;
   xrDTree_init = 1;
}

