/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)FormStr.c Nov 19  1:11:49 2022" */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef FormStr_H_
#include "FormStr.h"
#endif
#define FormStr_C_
#ifndef FormOut_H_
#include "FormOut.h"
#endif

typedef X2C_CHAR * Str;

struct desc_rec;


struct desc_rec {
   Str str;
   X2C_CARD32 high;
   X2C_CARD32 pos;
};

typedef struct desc_rec * desc_ptr;

static void format_app(X2C_ADDRESS, const X2C_CHAR [], X2C_CARD32,
                X2C_INT32);


static void format_app(X2C_ADDRESS x, const X2C_CHAR s[], X2C_CARD32 s_len,
                X2C_INT32 l)
{
   desc_ptr ptr;
   X2C_CARD32 i;
   X2C_CARD32 p;
   X2C_CARD32 h;
   ptr = (desc_ptr)x;
   p = ptr->pos;
   i = 0UL;
   h = p+(X2C_CARD32)l;
   if (h>ptr->high) h = ptr->high;
   if (p<h) {
      do {
         ptr->str[p] = s[i];
         ++i;
         ++p;
      } while (p!=h);
   }
   ptr->pos = p;
} /* end format_app() */


extern void FormStr_print(X2C_CHAR s[], X2C_CARD32 s_len, X2C_CHAR f[],
                X2C_CARD32 f_len, X2C_LOC x[], X2C_CARD32 x_len)
{
   struct desc_rec r;
   X2C_PCOPY((void **)&f,f_len);
   r.pos = 0UL;
   r.high = s_len-1;
   r.str = (Str)s;
   FormOut_format((X2C_ADDRESS) &r, (FormOut_write_proc)format_app, f, f_len,
                 '0', (X2C_ADDRESS)x, x_len);
   if (r.pos<=s_len-1) s[r.pos] = 0;
   X2C_PFREE(f);
} /* end print() */


extern void FormStr_append(X2C_CHAR s[], X2C_CARD32 s_len, X2C_CHAR f[],
                X2C_CARD32 f_len, X2C_LOC x[], X2C_CARD32 x_len)
{
   struct desc_rec r;
   X2C_PCOPY((void **)&f,f_len);
   r.pos = X2C_LENGTH(s,s_len);
   r.high = s_len-1;
   r.str = (Str)s;
   FormOut_format((X2C_ADDRESS) &r, (FormOut_write_proc)format_app, f, f_len,
                 '0', (X2C_ADDRESS)x, x_len);
   if (r.pos<=s_len-1) s[r.pos] = 0;
   X2C_PFREE(f);
} /* end append() */


extern void FormStr_image(X2C_CHAR s[], X2C_CARD32 s_len, X2C_CARD32 * pos,
                X2C_CHAR f[], X2C_CARD32 f_len, X2C_LOC x[],
                X2C_CARD32 x_len)
{
   struct desc_rec r;
   X2C_PCOPY((void **)&f,f_len);
   r.pos = *pos;
   r.high = s_len-1;
   r.str = (Str)s;
   FormOut_format((X2C_ADDRESS) &r, (FormOut_write_proc)format_app, f, f_len,
                 '0', (X2C_ADDRESS)x, x_len);
   if (r.pos<=s_len-1) s[r.pos] = 0;
   *pos = r.pos;
   X2C_PFREE(f);
} /* end image() */

#define FormStr_O 48

#define FormStr_A 65

#define FormStr_B 66

#define FormStr_C 67

#define FormStr_H 72

#define FormStr_Dovfl 214748364


static X2C_BOOLEAN Fin(X2C_CHAR str[], X2C_CARD32 str_len, X2C_CARD32 n)
{
   X2C_CHAR ch;
   if (n>str_len-1) return 1;
   ch = X2C_CAP(str[n]);
   return !(((X2C_CARD8)ch>='0' && (X2C_CARD8)ch<='9' || (X2C_CARD8)
                ch>='A' && (X2C_CARD8)ch<='F') || ch=='H');
} /* end Fin() */


static X2C_INT32 Sgn(X2C_BOOLEAN Plus, X2C_INT32 x)
{
   if (x==X2C_min_longint || Plus) return x;
   else return -x;
   return 0;
} /* end Sgn() */


extern void FormStr_iscan(X2C_INT32 * num, X2C_CHAR str[],
                X2C_CARD32 str_len, X2C_CARD32 * pos, X2C_BOOLEAN * done)
{
   X2C_BOOLEAN Plus;
   X2C_CHAR c;
   X2C_INT32 dig;
   X2C_INT32 ch;
   X2C_INT32 t;
   X2C_INT32 Hval;
   X2C_INT32 Dval;
   X2C_INT32 Oval;
   X2C_BOOLEAN h;
   X2C_BOOLEAN d;
   X2C_BOOLEAN o;
   X2C_BOOLEAN Dec_;
   X2C_BOOLEAN Oct_;
   *done = 0;
   if (*pos>str_len-1) return;
   while (*pos<=str_len-1 && str[*pos]==' ') ++*pos;
   if (*pos>str_len-1 || str[*pos]==0) return;
   Plus = str[*pos]!='-';
   if (!Plus || str[*pos]=='+') ++*pos;
   if (Fin(str, str_len, *pos) || !X2C_IN((X2C_CARD32)(X2C_CARD8)str[*pos]-48UL,
                32,0x3FFUL) && Fin(str, str_len, *pos+1UL)) return;
   Oval = 0L;
   Dval = 0L;
   Hval = 0L;
   Oct_ = 1;
   Dec_ = 1;
   o = 1;
   d = 1;
   h = 1;
   for (;;) {
      if (*pos<=str_len-1) {
         c = str[*pos];
         c = X2C_CAP(c);
         ch = (X2C_INT32)(X2C_CARD32)(X2C_CARD8)c;
      }
      else ch = 0L;
      if (X2C_IN(ch-48L,32,0xFFUL)) dig = ch-48L;
      else if (X2C_IN(ch-48L,32,0x300UL)) {
         dig = ch-48L;
         Oct_ = 0;
      }
      else {
         if ((ch==66L || ch==67L) && Fin(str, str_len, *pos+1UL)) {
            *num = Sgn(Plus, Oval);
            if (o && Oct_) {
               ++*pos;
               *done = 1;
               return;
            }
            else if (Oct_) return;
            else return;
         }
         if (X2C_IN(ch-65L,32,0x3FUL)) {
            dig = (10L+ch)-65L;
            Oct_ = 0;
            Dec_ = 0;
         }
         else if (ch==72L) {
            *num = Sgn(Plus, Hval);
            if (h) {
               ++*pos;
               *done = 1;
               return;
            }
            else return;
         }
         else {
            *num = Sgn(Plus, Dval);
            if (d && Dec_) {
               *done = 1;
               return;
            }
            else if (Dec_) return;
            else return;
         }
      }
      if (h) {
         h = ((X2C_CARD32)Hval&0xF0000000UL)==0UL;
         if (h) Hval = (X2C_INT32)((X2C_CARD32)(Hval<<4)|(X2C_CARD32)dig);
      }
      if (d && Dec_) {
         if (dig==9L) t = 1L;
         else t = 0L;
         if (Dval==214748364L && dig==8L) Dval = X2C_min_longint;
         else if (Dval+t>214748364L) d = 0;
         else Dval = Dval*10L+dig;
      }
      if (o && Oct_) {
         o = ((X2C_CARD32)Oval&0xE0000000UL)==0UL;
         if (o) Oval = (X2C_INT32)((X2C_CARD32)(Oval<<3)|(X2C_CARD32)dig);
      }
      ++*pos;
   }
} /* end iscan() */


extern void FormStr_BEGIN(void)
{
   static int FormStr_init = 0;
   if (FormStr_init) return;
   FormStr_init = 1;
   FormOut_BEGIN();
}

