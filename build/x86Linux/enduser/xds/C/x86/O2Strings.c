/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)O2Strings.c Nov  7 22:55:32 2022" */
/* Generated by XDS Oberon-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef O2Strings_H_
#include "O2Strings.h"
#endif
#define O2Strings_C_

extern struct X2C_MD_STR O2Strings_desc;

extern X2C_INT16 O2Strings_Length(X2C_CHAR stringVal[],
                X2C_CARD32 stringVal_len)
{
   return (X2C_INT16)X2C_LENGTH(stringVal,stringVal_len);
} /* end Length() */


extern void O2Strings_Insert(X2C_CHAR s[], X2C_CARD32 s_len, X2C_INT16 pos,
                X2C_CHAR d[], X2C_CARD32 d_len)
{
   X2C_INT32 n;
   X2C_INT32 i;
   X2C_INT32 rlen;
   X2C_INT32 tlen;
   X2C_INT32 slen;
   X2C_INT32 dlen;
   X2C_PCOPY((void **)&s,s_len);
   slen = X2C_LENGTH(s,s_len);
   if (slen==0L) goto label;
   dlen = X2C_LENGTH(d,d_len);
   if (pos<0 || (X2C_INT32)pos>dlen) goto label;
   tlen = d_len-1L;
   if (slen>tlen-(X2C_INT32)pos) slen = tlen-(X2C_INT32)pos;
   if (slen==0L) goto label;
   rlen = dlen-(X2C_INT32)pos;
   n = tlen-((X2C_INT32)pos+slen);
   if (rlen>n) rlen = n;
   d[(X2C_INT32)pos+slen+rlen] = 0x0U ;
   i = (X2C_INT32)pos+rlen;
   n = i+slen;
   while (rlen>0L) {
      --n;
      --i;
      d[n] = d[i];
      --rlen;
   }
   i = 0L;
   n = (X2C_INT32)pos;
   while (slen>0L) {
      d[n] = s[i];
      ++n;
      ++i;
      --slen;
   }
   label:;
   X2C_PFREE(s);
} /* end Insert() */


extern void O2Strings_Append(X2C_CHAR s[], X2C_CARD32 s_len, X2C_CHAR d[],
                X2C_CARD32 d_len)
{
   X2C_INT32 len;
   X2C_INT32 i;
   X2C_INT32 pos;
   X2C_PCOPY((void **)&s,s_len);
   pos = X2C_LENGTH(d,d_len);
   len = X2C_LENGTH(s,s_len);
   if (pos+len>=d_len) len = (d_len-pos)-1L;
   i = 0L;
   while (i<len) {
      d[pos] = s[i];
      ++i;
      ++pos;
   }
   d[pos] = 0x0U ;
   X2C_PFREE(s);
} /* end Append() */


extern void O2Strings_Delete(X2C_CHAR s[], X2C_CARD32 s_len, X2C_INT16 pos,
                X2C_INT16 n)
{
   X2C_INT32 i;
   X2C_INT32 slen;
   if (n==0) return;
   slen = X2C_LENGTH(s,s_len);
   if (pos>=0 && (X2C_INT32)pos<slen) {
      i = (X2C_INT32)(pos+n);
      while (i<slen) {
         s[pos] = s[i];
         ++pos;
         ++i;
      }
      s[pos] = 0x0U ;
   }
} /* end Delete() */


extern void O2Strings_Replace(X2C_CHAR s[], X2C_CARD32 s_len, X2C_INT16 pos,
                X2C_CHAR d[], X2C_CARD32 d_len)
{
   X2C_INT32 i;
   X2C_INT32 len;
   X2C_INT32 dlen;
   X2C_PCOPY((void **)&s,s_len);
   dlen = X2C_LENGTH(d,d_len);
   if ((X2C_INT32)pos>=dlen) goto label;
   len = X2C_LENGTH(s,s_len);
   if (len+(X2C_INT32)pos>dlen) len = dlen-(X2C_INT32)pos;
   i = 0L;
   while (i<len) {
      d[pos] = s[i];
      ++i;
      ++pos;
   }
   label:;
   X2C_PFREE(s);
} /* end Replace() */


extern void O2Strings_Extract(X2C_CHAR s[], X2C_CARD32 s_len, X2C_INT16 p,
                X2C_INT16 l, X2C_CHAR d[], X2C_CARD32 d_len)
{
   X2C_INT16 i;
   X2C_PCOPY((void **)&s,s_len);
   i = 0;
   while (((l>0 && (X2C_INT32)i<d_len-1L) && (X2C_INT32)p<s_len) && s[p]) {
      d[i] = s[p];
      --l;
      ++i;
      ++p;
   }
   d[i] = 0x0U ;
   X2C_PFREE(s);
} /* end Extract() */


extern X2C_INT16 O2Strings_Pos(X2C_CHAR p[], X2C_CARD32 p_len, X2C_CHAR s[],
                X2C_CARD32 s_len, X2C_INT16 start)
{
   X2C_INT32 plen;
   X2C_INT32 slen;
   X2C_INT32 i;
   X2C_INT32 n;
   X2C_INT32 tmp;
   slen = X2C_LENGTH(s,s_len);
   plen = X2C_LENGTH(p,p_len);
   if (plen==0L || plen>slen) return -1;
   tmp = slen-plen;
   i = (X2C_INT32)start;
   if (i<=tmp) for (;; i++) {
      n = 0L;
      while (n<plen && s[i+n]==p[n]) ++n;
      if (n==plen) return (X2C_INT16)i;
      if (i==tmp) break;
   } /* end for */
   return -1;
} /* end Pos() */


extern void O2Strings_Cap(X2C_CHAR s[], X2C_CARD32 s_len)
{
   X2C_INT32 i;
   i = 0L;
   while (i<s_len && s[i]) {
      s[i] = X2C_CAP(s[i]);
      ++i;
   }
} /* end Cap() */


static void * O2Strings_offs[] = {
   X2C_OFS_END
};
static X2C_PROC O2Strings_cmds[] = { 0 };
static X2C_CHAR * O2Strings_cnms[] = { 0 };
struct X2C_MD_STR O2Strings_desc = {
  0, 0, "O2Strings",O2Strings_offs,O2Strings_cmds,O2Strings_cnms,0
};

extern void O2Strings_BEGIN(void)
{
   static int O2Strings_init = 0;
   if (O2Strings_init) return;
   O2Strings_init = 1;
   X2C_MODULE(&O2Strings_desc);
}

