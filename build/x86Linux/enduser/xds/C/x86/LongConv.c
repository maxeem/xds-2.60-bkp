/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)LongConv.c Nov  7 22:55:32 2022" */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef LongConv_H_
#include "LongConv.h"
#endif
#define LongConv_C_
#ifndef ConvTypes_H_
#include "ConvTypes.h"
#endif
#ifndef LongStr_H_
#include "LongStr.h"
#endif
#ifndef EXCEPTIONS_H_
#include "EXCEPTIONS.h"
#endif

static EXCEPTIONS_ExceptionSource source;

#define LongConv_ok ConvTypes_valid

#define LongConv_inv ConvTypes_invalid

#define LongConv_pad ConvTypes_padding

#define LongConv_term ConvTypes_terminator

typedef X2C_CHAR string[128];


static void raise0(void)
{
   EXCEPTIONS_RAISE(source, 0UL, "RealConv.Exception", 19ul);
} /* end raise() */

static void WE(X2C_CHAR, X2C_CARD8 *, ConvTypes_ScanState *);


static void WE(X2C_CHAR ch, X2C_CARD8 * class0, ConvTypes_ScanState * next)
{
   *class0 = ConvTypes_valid;
   if ((X2C_CARD8)ch>='0' && (X2C_CARD8)ch<='9') {
      *next = (ConvTypes_ScanState)WE;
   }
   else *class0 = ConvTypes_terminator;
} /* end WE() */

static void SE(X2C_CHAR, X2C_CARD8 *, ConvTypes_ScanState *);


static void SE(X2C_CHAR ch, X2C_CARD8 * class0, ConvTypes_ScanState * next)
{
   *class0 = ConvTypes_valid;
   if ((X2C_CARD8)ch>='0' && (X2C_CARD8)ch<='9') {
      *next = (ConvTypes_ScanState)WE;
   }
   else {
      *class0 = ConvTypes_invalid;
      *next = (ConvTypes_ScanState)SE;
   }
} /* end SE() */

static void E(X2C_CHAR, X2C_CARD8 *, ConvTypes_ScanState *);


static void E(X2C_CHAR ch, X2C_CARD8 * class0, ConvTypes_ScanState * next)
{
   *class0 = ConvTypes_valid;
   if (ch=='-' || ch=='+') *next = (ConvTypes_ScanState)SE;
   else if ((X2C_CARD8)ch>='0' && (X2C_CARD8)ch<='9') {
      *next = (ConvTypes_ScanState)WE;
   }
   else {
      *class0 = ConvTypes_invalid;
      *next = (ConvTypes_ScanState)E;
   }
} /* end E() */

static void F(X2C_CHAR, X2C_CARD8 *, ConvTypes_ScanState *);


static void F(X2C_CHAR ch, X2C_CARD8 * class0, ConvTypes_ScanState * next)
{
   *class0 = ConvTypes_valid;
   if ((X2C_CARD8)ch>='0' && (X2C_CARD8)ch<='9') {
      *next = (ConvTypes_ScanState)F;
   }
   else if (ch=='E') *next = (ConvTypes_ScanState)E;
   else *class0 = ConvTypes_terminator;
} /* end F() */

static void P(X2C_CHAR, X2C_CARD8 *, ConvTypes_ScanState *);


static void P(X2C_CHAR ch, X2C_CARD8 * class0, ConvTypes_ScanState * next)
{
   *class0 = ConvTypes_valid;
   if ((X2C_CARD8)ch>='0' && (X2C_CARD8)ch<='9') {
      *next = (ConvTypes_ScanState)P;
   }
   else if (ch=='.') *next = (ConvTypes_ScanState)F;
   else if (ch=='E') *next = (ConvTypes_ScanState)E;
   else *class0 = ConvTypes_terminator;
} /* end P() */

static void RS(X2C_CHAR, X2C_CARD8 *, ConvTypes_ScanState *);


static void RS(X2C_CHAR ch, X2C_CARD8 * class0, ConvTypes_ScanState * next)
{
   *class0 = ConvTypes_invalid;
   *next = (ConvTypes_ScanState)RS;
   if ((X2C_CARD8)ch>='0' && (X2C_CARD8)ch<='9') {
      *class0 = ConvTypes_valid;
      *next = (ConvTypes_ScanState)P;
   }
} /* end RS() */


extern void LongConv_ScanReal(X2C_CHAR ch, X2C_CARD8 * class0,
                ConvTypes_ScanState * next)
{
   *class0 = ConvTypes_valid;
   if (ch==' ') {
      *class0 = ConvTypes_padding;
      *next = (ConvTypes_ScanState)LongConv_ScanReal;
   }
   else if (ch=='-' || ch=='+') *next = (ConvTypes_ScanState)RS;
   else if ((X2C_CARD8)ch>='0' && (X2C_CARD8)ch<='9') {
      *next = (ConvTypes_ScanState)P;
   }
   else {
      *class0 = ConvTypes_invalid;
      *next = (ConvTypes_ScanState)LongConv_ScanReal;
   }
} /* end ScanReal() */


extern X2C_CARD8 LongConv_FormatReal(X2C_CHAR str[], X2C_CARD32 str_len)
{
   X2C_CARD8 res;
   X2C_LONGREAL real;
   X2C_CARD8 LongConv_FormatReal_ret;
   X2C_PCOPY((void **)&str,str_len);
   LongStr_StrToReal(str, str_len, &real, &res);
   LongConv_FormatReal_ret = res;
   X2C_PFREE(str);
   return LongConv_FormatReal_ret;
} /* end FormatReal() */


extern X2C_LONGREAL LongConv_ValueReal(X2C_CHAR str[], X2C_CARD32 str_len)
{
   X2C_CARD8 res;
   X2C_LONGREAL real;
   X2C_LONGREAL LongConv_ValueReal_ret;
   X2C_PCOPY((void **)&str,str_len);
   LongStr_StrToReal(str, str_len, &real, &res);
   if (res && res!=ConvTypes_strOutOfRange) raise0();
   LongConv_ValueReal_ret = real;
   X2C_PFREE(str);
   return LongConv_ValueReal_ret;
} /* end ValueReal() */


static X2C_CARD32 chk(X2C_CHAR str[], X2C_CARD32 str_len)
{
   if (str[0UL]=='?') X2C_ABORT();
   return X2C_LENGTH(str,str_len);
} /* end chk() */


extern X2C_CARD32 LongConv_LengthFloatReal(X2C_LONGREAL real,
                X2C_CARD32 sigFigs)
{
   string str;
   LongStr_RealToFloat(real, sigFigs, str, 128ul);
   return chk(str, 128ul);
} /* end LengthFloatReal() */


extern X2C_CARD32 LongConv_LengthEngReal(X2C_LONGREAL real,
                X2C_CARD32 sigFigs)
{
   string str;
   LongStr_RealToEng(real, sigFigs, str, 128ul);
   return chk(str, 128ul);
} /* end LengthEngReal() */


extern X2C_CARD32 LongConv_LengthFixedReal(X2C_LONGREAL real,
                X2C_INT32 place)
{
   string str;
   LongStr_RealToFixed(real, place, str, 128ul);
   return chk(str, 128ul);
} /* end LengthFixedReal() */


extern X2C_BOOLEAN LongConv_IsRConvException(void)
{
   return EXCEPTIONS_IsCurrentSource(source);
} /* end IsRConvException() */


extern void LongConv_BEGIN(void)
{
   static int LongConv_init = 0;
   if (LongConv_init) return;
   LongConv_init = 1;
   if (sizeof(string)!=128) X2C_ASSERT(0);
   EXCEPTIONS_BEGIN();
   LongStr_BEGIN();
   ConvTypes_BEGIN();
   EXCEPTIONS_AllocateSource(&source);
}

