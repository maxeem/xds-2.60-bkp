/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)Strings.c Nov  7 22:55:49 2022" */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef Strings_H_
#include "Strings.h"
#endif
#define Strings_C_
#ifndef xmRTS_H_
#include "xmRTS.h"
#endif


extern X2C_CARD32 Strings_Length(X2C_CHAR stringVal[],
                X2C_CARD32 stringVal_len)
{
   return X2C_LENGTH(stringVal,stringVal_len);
} /* end Length() */


extern X2C_BOOLEAN Strings_CanAssignAll(X2C_CARD32 sourceLength,
                X2C_CHAR destination[], X2C_CARD32 destination_len)
{
   return sourceLength<=(destination_len-1)+1UL;
} /* end CanAssignAll() */


extern void Strings_Assign(X2C_CHAR s[], X2C_CARD32 s_len, X2C_CHAR d[],
                X2C_CARD32 d_len)
{
   X2C_CARD32 h;
   X2C_CARD32 i;
   X2C_PCOPY((void **)&s,s_len);
   h = s_len-1;
   if (h>d_len-1) h = d_len-1;
   i = 0UL;
   while (i<=h && s[i]) {
      d[i] = s[i];
      ++i;
   }
   if (i<=d_len-1) d[i] = 0;
   X2C_PFREE(s);
} /* end Assign() */


extern X2C_BOOLEAN Strings_CanExtractAll(X2C_CARD32 slen, X2C_CARD32 pos,
                X2C_CARD32 len, X2C_CHAR d[], X2C_CARD32 d_len)
{
   return pos+len<=slen && len<=(d_len-1)+1UL;
} /* end CanExtractAll() */


extern void Strings_Extract(X2C_CHAR s[], X2C_CARD32 s_len, X2C_CARD32 p,
                X2C_CARD32 len, X2C_CHAR d[], X2C_CARD32 d_len)
{
   X2C_CARD32 i;
   X2C_PCOPY((void **)&s,s_len);
   i = 0UL;
   while (((len>0UL && i<=d_len-1) && p<=s_len-1) && s[p]) {
      d[i] = s[p];
      --len;
      ++i;
      ++p;
   }
   if (i<=d_len-1) d[i] = 0;
   X2C_PFREE(s);
} /* end Extract() */


extern X2C_BOOLEAN Strings_CanDeleteAll(X2C_CARD32 slen, X2C_CARD32 pos,
                X2C_CARD32 len)
{
   return pos+len<=slen;
} /* end CanDeleteAll() */


extern void Strings_Delete(X2C_CHAR s[], X2C_CARD32 s_len, X2C_CARD32 pos,
                X2C_CARD32 len)
{
   X2C_CARD32 i;
   X2C_CARD32 slen;
   if (len==0UL) return;
   slen = X2C_LENGTH(s,s_len);
   if (pos<slen) {
      i = pos+len;
      while (i<slen) {
         s[pos] = s[i];
         ++pos;
         ++i;
      }
      s[pos] = 0;
   }
} /* end Delete() */


extern X2C_BOOLEAN Strings_CanInsertAll(X2C_CARD32 slen, X2C_CARD32 pos,
                X2C_CHAR d[], X2C_CARD32 d_len)
{
   X2C_CARD32 dlen;
   dlen = X2C_LENGTH(d,d_len);
   return pos<=dlen && slen+dlen<=(d_len-1)+1UL;
} /* end CanInsertAll() */


extern void Strings_Insert(X2C_CHAR s[], X2C_CARD32 s_len, X2C_CARD32 pos,
                X2C_CHAR d[], X2C_CARD32 d_len)
{
   X2C_CARD32 n;
   X2C_CARD32 i;
   X2C_CARD32 rlen;
   X2C_CARD32 tlen;
   X2C_CARD32 slen;
   X2C_CARD32 dlen;
   X2C_PCOPY((void **)&s,s_len);
   slen = X2C_LENGTH(s,s_len);
   if (slen==0UL) goto label;
   dlen = X2C_LENGTH(d,d_len);
   if (pos>dlen) goto label;
   tlen = (d_len-1)+1UL;
   if (slen>tlen-pos) slen = tlen-pos;
   if (slen==0UL) goto label;
   rlen = dlen-pos;
   n = tlen-(pos+slen);
   if (rlen>n) rlen = n;
   if (pos+slen+rlen<tlen) d[pos+slen+rlen] = 0;
   i = pos+rlen;
   n = i+slen;
   while (rlen>0UL) {
      --n;
      --i;
      d[n] = d[i];
      --rlen;
   }
   i = 0UL;
   n = pos;
   while (slen>0UL) {
      d[n] = s[i];
      ++n;
      ++i;
      --slen;
   }
   label:;
   X2C_PFREE(s);
} /* end Insert() */


extern X2C_BOOLEAN Strings_CanReplaceAll(X2C_CARD32 slen, X2C_CARD32 pos,
                X2C_CHAR d[], X2C_CARD32 d_len)
{
   return slen+pos<=X2C_LENGTH(d,d_len);
} /* end CanReplaceAll() */


extern void Strings_Replace(X2C_CHAR s[], X2C_CARD32 s_len, X2C_CARD32 pos,
                X2C_CHAR d[], X2C_CARD32 d_len)
{
   X2C_CARD32 i;
   X2C_CARD32 len;
   X2C_CARD32 dlen;
   X2C_PCOPY((void **)&s,s_len);
   dlen = X2C_LENGTH(d,d_len);
   if (pos>=dlen) goto label;
   len = X2C_LENGTH(s,s_len);
   if (len+pos>dlen) len = dlen-pos;
   i = 0UL;
   while (i<len) {
      d[pos] = s[i];
      ++i;
      ++pos;
   }
   label:;
   X2C_PFREE(s);
} /* end Replace() */


extern X2C_BOOLEAN Strings_CanAppendAll(X2C_CARD32 slen, X2C_CHAR d[],
                X2C_CARD32 d_len)
{
   return X2C_LENGTH(d,d_len)+slen<=(d_len-1)+1UL;
} /* end CanAppendAll() */


extern void Strings_Append(X2C_CHAR s[], X2C_CARD32 s_len, X2C_CHAR d[],
                X2C_CARD32 d_len)
{
   X2C_CARD32 len;
   X2C_CARD32 i;
   X2C_CARD32 pos;
   X2C_PCOPY((void **)&s,s_len);
   pos = X2C_LENGTH(d,d_len);
   len = X2C_LENGTH(s,s_len);
   if (pos+len>(d_len-1)+1UL) len = ((d_len-1)+1UL)-pos;
   i = 0UL;
   while (i<len) {
      d[pos] = s[i];
      ++i;
      ++pos;
   }
   if (pos<=d_len-1) d[pos] = 0;
   X2C_PFREE(s);
} /* end Append() */


extern X2C_BOOLEAN Strings_CanConcatAll(X2C_CARD32 s1len, X2C_CARD32 s2len,
                X2C_CHAR d[], X2C_CARD32 d_len)
{
   return s1len+s2len<=(d_len-1)+1UL;
} /* end CanConcatAll() */


extern void Strings_Concat(X2C_CHAR s1[], X2C_CARD32 s1_len, X2C_CHAR s2[],
                X2C_CARD32 s2_len, X2C_CHAR d[], X2C_CARD32 d_len)
{
   X2C_PCOPY((void **)&s1,s1_len);
   X2C_PCOPY((void **)&s2,s2_len);
   Strings_Assign(s1, s1_len, d, d_len);
   Strings_Append(s2, s2_len, d, d_len);
   X2C_PFREE(s1);
   X2C_PFREE(s2);
} /* end Concat() */


extern X2C_CARD8 Strings_Compare(X2C_CHAR s1[], X2C_CARD32 s1_len,
                X2C_CHAR s2[], X2C_CARD32 s2_len)
{
   X2C_CARD32 i;
   X2C_CHAR c2;
   X2C_CHAR c1;
   i = 0UL;
   for (;;) {
      if (i<=s1_len-1) c1 = s1[i];
      else c1 = 0;
      if (i<=s2_len-1) c2 = s2[i];
      else c2 = 0;
      if ((X2C_CARD8)c1>(X2C_CARD8)c2) return Strings_greater;
      if ((X2C_CARD8)c1<(X2C_CARD8)c2) return Strings_less;
      if (c1==0) {
         if (c2==0) return Strings_equal0;
         else return Strings_less;
      }
      ++i;
   }
   return 0;
} /* end Compare() */


extern X2C_BOOLEAN Strings_Equal(X2C_CHAR s1[], X2C_CARD32 s1_len,
                X2C_CHAR s2[], X2C_CARD32 s2_len)
{
   return Strings_Compare(s1, s1_len, s2, s2_len)==Strings_equal0;
} /* end Equal() */


extern void Strings_FindDiff(X2C_CHAR s1[], X2C_CARD32 s1_len, X2C_CHAR s2[],
                 X2C_CARD32 s2_len, X2C_BOOLEAN * diff, X2C_CARD32 * pos)
{
   X2C_CARD32 i;
   X2C_CHAR c2;
   X2C_CHAR c1;
   *diff = 0;
   i = 0UL;
   for (;;) {
      if (i<=s1_len-1) c1 = s1[i];
      else c1 = 0;
      if (i<=s2_len-1) c2 = s2[i];
      else c2 = 0;
      if (c1!=c2) {
         *diff = 1;
         *pos = i;
         return;
      }
      if (c1==0) return;
      ++i;
   }
} /* end FindDiff() */


extern void Strings_Capitalize(X2C_CHAR s[], X2C_CARD32 s_len)
{
   X2C_CARD32 i;
   i = 0UL;
   while (i<=s_len-1 && s[i]) {
      s[i] = X2C_CAP(s[i]);
      ++i;
   }
} /* end Capitalize() */


extern void Strings_FindNext(X2C_CHAR p[], X2C_CARD32 p_len, X2C_CHAR s[],
                X2C_CARD32 s_len, X2C_CARD32 start, X2C_BOOLEAN * done,
                X2C_CARD32 * pos)
{
   X2C_CARD32 plen;
   X2C_CARD32 slen;
   X2C_CARD32 i;
   X2C_CARD32 n;
   X2C_CARD32 tmp;
   *done = 0;
   slen = X2C_LENGTH(s,s_len);
   plen = X2C_LENGTH(p,p_len);
   if (plen==0UL || plen>slen) return;
   tmp = slen-plen;
   i = start;
   if (i<=tmp) for (;; i++) {
      n = 0UL;
      while (n<plen && s[i+n]==p[n]) ++n;
      if (n==plen) {
         *done = 1;
         *pos = i;
         return;
      }
      if (i==tmp) break;
   } /* end for */
} /* end FindNext() */


extern void Strings_FindPrev(X2C_CHAR p[], X2C_CARD32 p_len, X2C_CHAR s[],
                X2C_CARD32 s_len, X2C_CARD32 start, X2C_BOOLEAN * done,
                X2C_CARD32 * pos)
{
   X2C_CARD32 plen;
   X2C_CARD32 slen;
   X2C_CARD32 i;
   X2C_CARD32 n;
   *done = 0;
   slen = X2C_LENGTH(s,s_len);
   plen = X2C_LENGTH(p,p_len);
   if (plen==0UL || plen>slen) return;
   if (start>slen-plen) start = slen-plen;
   for (i = start;; i--) {
      n = 0UL;
      while (n<plen && s[i+n]==p[n]) ++n;
      if (n==plen) {
         *done = 1;
         *pos = i;
         return;
      }
      if (i==0UL) break;
   } /* end for */
} /* end FindPrev() */


extern void Strings_BEGIN(void)
{
   static int Strings_init = 0;
   if (Strings_init) return;
   Strings_init = 1;
   if (sizeof(Strings_String1)!=1) X2C_ASSERT(0);
}
