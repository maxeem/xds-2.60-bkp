/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)Out.c Nov 19  1:11:32 2022" */
/* Generated by XDS Oberon-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef Out_H_
#include "Out.h"
#endif
#define Out_C_
#ifndef STextIO_H_
#include "STextIO.h"
#endif
#ifndef SWholeIO_H_
#include "SWholeIO.h"
#endif
#ifndef RealStr_H_
#include "RealStr.h"
#endif
#ifndef LongStr_H_
#include "LongStr.h"
#endif
#ifndef Strings_H_
#include "Strings.h"
#endif

extern struct X2C_MD_STR Out_desc;

extern void Out_Open(void)
{
} /* end Open() */


extern void Out_Char(X2C_CHAR ch)
{
   STextIO_WriteChar(ch);
} /* end Char() */


extern void Out_String(X2C_CHAR str[], X2C_CARD32 str_len)
{
   STextIO_WriteString(str, str_len);
} /* end String() */


extern void Out_Int(X2C_INT32 x, X2C_INT32 n)
{
   X2C_INT16 i;
   X2C_INT32 x0;
   X2C_CHAR a[11];
   i = 0;
   if (x<0L) {
      if (x==X2C_min_longint) {
         Out_String(" -2147483648", 13ul);
         return;
      }
      --n;
      x0 = -x;
   }
   else x0 = x;
   do {
      a[i] = (X2C_CHAR)(X2C_MOD(x0,10L)+48L);
      x0 = X2C_DIV(x0,10L);
      ++i;
   } while (x0);
   while (n>(X2C_INT32)i) {
      Out_Char(' ');
      --n;
   }
   if (x<0L) Out_Char('-');
   do {
      --i;
      Out_Char(a[i]);
   } while (i);
} /* end Int() */


static void ChangeReal(X2C_CHAR s[], X2C_CARD32 s_len, X2C_BOOLEAN long0)
{
   X2C_INT32 len;
   X2C_INT32 end;
   X2C_INT32 beg;
   X2C_INT32 i;
   len = X2C_LENGTH(s,s_len);
   i = 0L;
   while ((i<len && s[i]!='E') && s[i]!='.') ++i;
   if (i==len) Strings_Append(".0", 3ul, s, s_len);
   else if (s[i]=='E') {
      if (long0) s[i] = 'D';
      Strings_Insert(".0", 3ul, (X2C_CARD32)i, s, s_len);
   }
   else {
      ++i;
      beg = i;
      while (i<len && s[i]!='E') ++i;
      if (long0 && s[i]=='E') s[i] = 'D';
      --i;
      end = i;
      while (i>beg && s[i]=='0') --i;
      if (i<end) {
         Strings_Delete(s, s_len, (X2C_CARD32)(i+1L), (X2C_CARD32)(end-i));
      }
   }
} /* end ChangeReal() */


extern void Out_Real(X2C_REAL x, X2C_INT16 n)
{
   X2C_CHAR str[32];
   X2C_INT32 len;
   RealStr_RealToFloat(x, 6UL, str, 32ul);
   ChangeReal(str, 32ul, 0);
   len = X2C_LENGTH(str,32l);
   while ((X2C_INT32)n>len) {
      Out_Char(' ');
      --n;
   }
   Out_String(str, 32ul);
} /* end Real() */


extern void Out_LongReal(X2C_LONGREAL x, X2C_INT16 n)
{
   X2C_CHAR str[32];
   X2C_INT32 len;
   LongStr_RealToFloat(x, 15UL, str, 32ul);
   ChangeReal(str, 32ul, 1);
   len = X2C_LENGTH(str,32l);
   while ((X2C_INT32)n>len) {
      Out_Char(' ');
      --n;
   }
   Out_String(str, 32ul);
} /* end LongReal() */


extern void Out_Ln(void)
{
   STextIO_WriteLn();
} /* end Ln() */


static void * Out_offs[] = {
   X2C_OFS_END
};
static X2C_PROC Out_cmds[] = { Out_Ln,Out_Open,0 };
static X2C_CHAR * Out_cnms[] = { "Ln","Open",0 };
struct X2C_MD_STR Out_desc = {
  0, 0, "Out",Out_offs,Out_cmds,Out_cnms,0
};

extern void Out_BEGIN(void)
{
   static int Out_init = 0;
   if (Out_init) return;
   Out_init = 1;
   Strings_BEGIN();
   LongStr_BEGIN();
   RealStr_BEGIN();
   SWholeIO_BEGIN();
   STextIO_BEGIN();
   X2C_MODULE(&Out_desc);
}

