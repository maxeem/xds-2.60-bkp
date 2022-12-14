/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)WholeStr.c Nov 19  1:11:49 2022" */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef WholeStr_H_
#include "WholeStr.h"
#endif
#define WholeStr_C_
#ifndef ConvTypes_H_
#include "ConvTypes.h"
#endif
#ifndef CharClass_H_
#include "CharClass.h"
#endif

#define WholeStr_ok ConvTypes_strAllRight


extern void WholeStr_StrToInt(X2C_CHAR s[], X2C_CARD32 s_len,
                X2C_INT32 * val, X2C_CARD8 * res)
{
   X2C_CARD32 ord;
   X2C_CARD32 n;
   X2C_CARD32 i;
   X2C_BOOLEAN neg;
   X2C_PCOPY((void **)&s,s_len);
   i = 0UL;
   while (i<=s_len-1 && CharClass_IsWhiteSpace(s[i])) ++i;
   if (i>s_len-1 || s[i]==0) {
      *res = ConvTypes_strEmpty;
      goto label;
   }
   neg = s[i]=='-';
   if (neg || s[i]=='+') ++i;
   if (i>s_len-1 || !CharClass_IsNumeric(s[i])) {
      *res = ConvTypes_strWrongFormat;
      goto label;
   }
   n = 0UL;
   *res = ConvTypes_strAllRight;
   while (i<=s_len-1 && CharClass_IsNumeric(s[i])) {
      if (*res==ConvTypes_strAllRight) {
         ord = (X2C_CARD32)(X2C_CARD8)s[i]-48UL;
         if (n>(X2C_max_longcard-ord)/10UL) {
            *res = ConvTypes_strOutOfRange;
            if (neg) *val = X2C_min_longint;
            else *val = X2C_max_longint;
         }
         else n = n*10UL+ord;
      }
      ++i;
   }
   if (i<=s_len-1 && s[i]) *res = ConvTypes_strWrongFormat;
   else if (*res==ConvTypes_strAllRight) {
      if (neg) {
         if (n>0x080000000UL) *res = ConvTypes_strOutOfRange;
         else if (n==0x080000000UL) *val = X2C_min_longint;
         else *val = -(X2C_INT32)n;
      }
      else if (n>2147483647UL) *res = ConvTypes_strOutOfRange;
      else *val = (X2C_INT32)n;
   }
   label:;
   X2C_PFREE(s);
} /* end StrToInt() */


extern void WholeStr_StrToCard(X2C_CHAR s[], X2C_CARD32 s_len,
                X2C_CARD32 * val, X2C_CARD8 * res)
{
   X2C_CARD32 ord;
   X2C_CARD32 n;
   X2C_CARD32 i;
   X2C_PCOPY((void **)&s,s_len);
   i = 0UL;
   while (i<=s_len-1 && CharClass_IsWhiteSpace(s[i])) ++i;
   if (i>s_len-1 || s[i]==0) {
      *res = ConvTypes_strEmpty;
      goto label;
   }
   if (!CharClass_IsNumeric(s[i])) {
      *res = ConvTypes_strWrongFormat;
      goto label;
   }
   n = 0UL;
   *res = ConvTypes_strAllRight;
   while (i<=s_len-1 && CharClass_IsNumeric(s[i])) {
      if (*res==ConvTypes_strAllRight) {
         ord = (X2C_CARD32)(X2C_CARD8)s[i]-48UL;
         if (n>(X2C_max_longcard-ord)/10UL) {
            *res = ConvTypes_strOutOfRange;
            *val = X2C_max_longcard;
         }
         else n = n*10UL+ord;
      }
      ++i;
   }
   if (i<=s_len-1 && s[i]) *res = ConvTypes_strWrongFormat;
   else if (*res==ConvTypes_strAllRight) *val = n;
   label:;
   X2C_PFREE(s);
} /* end StrToCard() */


static void AppendCard(X2C_CARD32 x, X2C_CARD32 n, X2C_CHAR str[],
                X2C_CARD32 str_len)
{
   X2C_CARD32 i;
   X2C_CHAR a[12];
   i = 0UL;
   do {
      a[i] = (X2C_CHAR)(x%10UL+48UL);
      x = x/10UL;
      ++i;
   } while (x);
   do {
      --i;
      str[n] = a[i];
      ++n;
   } while (!(n>str_len-1 || i==0UL));
   if (n<=str_len-1) str[n] = 0;
} /* end AppendCard() */


extern void WholeStr_CardToStr(X2C_CARD32 card, X2C_CHAR str[],
                X2C_CARD32 str_len)
{
   AppendCard(card, 0UL, str, str_len);
} /* end CardToStr() */


extern void WholeStr_IntToStr(X2C_INT32 int0, X2C_CHAR str[],
                X2C_CARD32 str_len)
{
   X2C_CARD32 n;
   X2C_CARD32 x;
   if (int0<0L) {
      n = 1UL;
      str[0UL] = '-';
      if (int0==X2C_min_longint) x = 0x080000000UL;
      else x = (X2C_CARD32) -int0;
   }
   else {
      n = 0UL;
      x = (X2C_CARD32)int0;
   }
   AppendCard(x, n, str, str_len);
} /* end IntToStr() */


extern void WholeStr_BEGIN(void)
{
   static int WholeStr_init = 0;
   if (WholeStr_init) return;
   WholeStr_init = 1;
   CharClass_BEGIN();
   ConvTypes_BEGIN();
}

