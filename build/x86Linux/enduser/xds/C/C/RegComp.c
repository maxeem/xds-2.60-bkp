/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)RegComp.c Nov 19  1:11:49 2022" */
/* Generated by XDS Oberon-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef RegComp_H_
#include "RegComp.h"
#endif
#define RegComp_C_

extern struct X2C_MD_STR RegComp_desc;
#define RegComp_str 0

#define RegComp_any 1

#define RegComp_set 2

#define RegComp_bra 3

#define RegComp_seq 4

#define RegComp_and 5

#define RegComp_or 6

#define RegComp_not 7

#define RegComp_par 8

#define RegComp_ok 0

#define RegComp_badParm 1


static X2C_PROC RegComp_RESULT_proc[] = {
   0
};
static void * RegComp_RESULT_offs[] = {
   X2C_OFS_END
};
struct X2C_TD_STR RegComp_RESULT_desc = {
   sizeof(struct RegComp_RESULT), "RESULT",
   &RegComp_desc, &RegComp_ExprDesc_desc, 0, 0,
   { &RegComp_RESULT_desc, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
   RegComp_RESULT_proc, RegComp_RESULT_offs, 0, 0, 0, &RegComp_RESULT_desc,
                0x93678150lu
};


static X2C_PROC RegComp_ExprDesc_proc[] = {
   0
};
static void * RegComp_ExprDesc_offs[] = {
   X2C_OFS(struct RegComp_ExprDesc,next),
   X2C_OFS(struct RegComp_ExprDesc,res),
   X2C_OFS(struct RegComp_ExprDesc,left),
   X2C_OFS(struct RegComp_ExprDesc,pat),
   X2C_OFS(struct RegComp_ExprDesc,leg),
   X2C_OFS_END
};
struct X2C_TD_STR RegComp_ExprDesc_desc = {
   sizeof(struct RegComp_ExprDesc), "ExprDesc",
   &RegComp_desc, 0, 0, 0,
   { &RegComp_ExprDesc_desc, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
   RegComp_ExprDesc_proc, RegComp_ExprDesc_offs, 0, 0, 0,
                &RegComp_ExprDesc_desc, 0x93678150lu
};


static void app(X2C_INT32 * res, RegComp_Expr * reg, RegComp_Expr r)
{
   RegComp_Expr t = 0;
   if (*reg==0) {
      *reg = r;
      return;
   }
   t = *reg;
   while (t->next) t = t->next;
   if (t->kind==4 && r->kind==4) *res = 1L;
   else t->next = r;
} /* end app() */


static RegComp_Expr new0(X2C_INT16 kind)
{
   RegComp_Expr n = 0;
   X2C_NEW(&RegComp_ExprDesc_desc,(X2C_ADDRESS*) &n,
                sizeof(struct RegComp_ExprDesc),0);
   n->kind = kind;
   n->nres = -1;
   n->next = 0;
   n->res = 0;
   n->left = 0;
   n->pat = 0;
   n->leg = 0;
   return n;
} /* end new() */


static RegComp_Expr app_new(X2C_INT32 * res, RegComp_Expr * reg,
                X2C_INT16 kind)
{
   RegComp_Expr n = 0;
   n = new0(kind);
   app(res, reg, n);
   return n;
} /* end app_new() */


static void dollar(X2C_CHAR expr[], X2C_CARD32 expr_len, X2C_INT32 * i,
                X2C_INT32 * res, RegComp_Expr n)
{
   X2C_CHAR ch;
   if (*res) return;
   if (*i>=expr_len-1L || expr[*i]!='$') return;
   ch = expr[*i+1L];
   if ('0'<=(X2C_CARD8)ch && (X2C_CARD8)ch<='9') {
      n->nres = (X2C_INT16)(X2C_CARD8)ch-48;
      *i += 2L;
   }
   else *res = 1L;
} /* end dollar() */


static X2C_CHAR char_code(X2C_INT32 * res, X2C_CHAR expr[],
                X2C_CARD32 expr_len, X2C_CHAR c, X2C_INT32 * j)
{
   X2C_INT16 n;
   c = (X2C_CHAR)((X2C_INT16)(X2C_CARD8)c-48);
   for (n = 0; n<=1; n++) {
      if ((*j<expr_len && '0'<=(X2C_CARD8)expr[*j]) && (X2C_CARD8)
                expr[*j]<='7') {
         c = (X2C_CHAR)(((X2C_INT16)(X2C_CARD8)c*8+(X2C_INT16)(X2C_CARD8)
                expr[*j])-48);
         ++*j;
      }
      else {
         *res = 1L;
         return c;
      }
   } /* end for */
   return c;
} /* end char_code() */


static X2C_CHAR esc(X2C_INT32 * res, X2C_CHAR expr[], X2C_CARD32 expr_len,
                X2C_INT32 * j)
{
   X2C_CHAR c;
   ++*j;
   c = expr[*j];
   ++*j;
   if ('0'<=(X2C_CARD8)c && (X2C_CARD8)c<='7') {
      return char_code(res, expr, expr_len, c, j);
   }
   else return c;
   return 0;
} /* end esc() */


static void incl(X2C_INT32 * res, X2C_CHAR from, RegComp_Expr n,
                X2C_BOOLEAN * range, X2C_CHAR ch)
{
   X2C_INT16 i;
   X2C_INT16 tmp;
   if (!*range) {
      n->leg[(X2C_INT16)X2C_DIV((X2C_INT16)(X2C_CARD8)ch,
                32)] |= (1UL<<((X2C_INT16)(X2C_CARD8)ch&31));
      return;
   }
   if ((X2C_CARD8)from>(X2C_CARD8)ch) {
      *res = 1L;
      return;
   }
   tmp = (X2C_INT16)(X2C_CARD8)ch;
   i = (X2C_INT16)(X2C_CARD8)from;
   if (i<=tmp) for (;; i++) {
      n->leg[(X2C_INT16)X2C_DIV(i,32)] |= (1UL<<(i&31));
      if (i==tmp) break;
   } /* end for */
   *range = 0;
} /* end incl() */


static void fill_set(X2C_INT32 * i, X2C_CHAR expr[], X2C_CARD32 expr_len,
                X2C_INT32 * res, RegComp_Expr n)
{
   X2C_CHAR from;
   X2C_BOOLEAN range;
   X2C_INT16 j;
   X2C_CHAR ch;
   X2C_CHAR q;
   X2C_BOOLEAN inv;
   if (*res) return;
   X2C_NEW(x2c_td_null,(X2C_ADDRESS*) &n->leg,32u,0);
   for (j = 0; j<=7; j++) {
      n->leg[j] = 0UL;
   } /* end for */
   range = 0;
   from = 0x0U ;
   ch = 0x0U ;
   if (expr[*i]=='[') q = ']';
   else {
      q = '}';
      n->kind = 3;
   }
   ++*i;
   inv = *i<expr_len && expr[*i]=='^';
   if (inv) ++*i;
   if (*i<expr_len && expr[*i]==q) {
      *res = 1L;
      return;
   }
   while (((*i<expr_len && expr[*i]!=q) && expr[*i]) && *res==0L) {
      if ((expr[*i]=='\\' && *i<expr_len-1L) && expr[*i+1L]) {
         ch = esc(res, expr, expr_len, i);
         incl(res, from, n, &range, ch);
      }
      else if ((expr[*i]=='-' && *i<expr_len-1L) && expr[*i+1L]!=q) {
         from = ch;
         range = 1;
         ++*i;
      }
      else {
         ch = expr[*i];
         incl(res, from, n, &range, ch);
         ++*i;
      }
   }
   if (*res) return;
   if ((*i>=expr_len || expr[*i]!=q) || range) *res = 1L;
   else {
      ++*i;
      if (!inv) return;
      for (j = 0; j<=7; j++) {
         n->leg[j] = n->leg[j]^0xFFFFFFFFUL;
      } /* end for */
   }
} /* end fill_set() */


static X2C_INT32 scan(RegComp_Expr n, X2C_INT32 * res, X2C_CHAR expr[],
                X2C_CARD32 expr_len, X2C_INT32 * i, X2C_BOOLEAN put)
{
   X2C_CHAR ch;
   X2C_INT32 j;
   X2C_INT32 c;
   struct RegComp__0 * anonym = 0;
   struct RegComp__0 * anonym0 = 0;
   j = *i;
   c = 0L;
   while (j<expr_len) {
      ch = expr[j];
      if (((((((((ch==0 || ch=='[') || ch=='*') || ch=='?') || ch=='{')
                || ch==')') || ch=='&') || ch=='|') || ch=='^') || ch=='$') {
         if (put) *i = j;
         return c;
      }
      if ((ch=='\\' && j<expr_len-1L) && expr[j+1L]) {
         ch = esc(res, expr, expr_len, &j);
         if (put) *(anonym = n->pat,&anonym->Adr[c]) = ch;
         ++c;
      }
      else {
         if (put) *(anonym0 = n->pat,&anonym0->Adr[c]) = expr[j];
         ++c;
         ++j;
      }
   }
   if (put) *i = j;
   return c;
} /* end scan() */


static void fill_str(X2C_INT32 * i, X2C_CHAR expr[], X2C_CARD32 expr_len,
                X2C_INT32 * res, RegComp_Expr n)
{
   struct RegComp__0 * anonym = 0;
   X2C_INDEX tmp[1];
   if (*res) return;
   X2C_NEW_OPEN(x2c_td_null,(X2C_ADDRESS*) &n->pat,1u,
                (tmp[0] = (size_t)(scan(n, res, expr, expr_len, i, 0)+1L),
                tmp),1u,0);
   *(anonym = n->pat,&anonym->Adr[scan(n, res, expr, expr_len, i, 1)]) = 0;
} /* end fill_str() */


static X2C_INT32 simple(X2C_CHAR expr[], X2C_CARD32 expr_len, X2C_INT32 * i,
                X2C_INT32 * res, RegComp_Expr * reg)
{
   RegComp_Expr n = 0;
   X2C_CHAR ch;
   if (*res) return *res;
   if (*i>expr_len-1L || expr[*i]==0) return 1L;
   for (;;) {
      if (*res || *i>expr_len-1L) break;
      ch = expr[*i];
      if (((((ch==0 || ch==')') || ch=='(') || ch=='|') || ch=='&')
                || ch=='^') break;
      if (ch=='*') {
         n = app_new(res, reg, 4);
         ++*i;
      }
      else if (ch=='?') {
         n = app_new(res, reg, 1);
         ++*i;
      }
      else if (ch=='{') {
         n = app_new(res, reg, 2);
         fill_set(i, expr, expr_len, res, n);
      }
      else if (ch=='[') {
         n = app_new(res, reg, 2);
         fill_set(i, expr, expr_len, res, n);
      }
      else {
         n = app_new(res, reg, 0);
         fill_str(i, expr, expr_len, res, n);
      }
      dollar(expr, expr_len, i, res, n);
   }
   return *res;
} /* end simple() */

static X2C_INT32 factor(X2C_CHAR [], X2C_CARD32, X2C_INT32 *, X2C_INT32 *,
                RegComp_Expr *);

static X2C_INT32 re(X2C_CHAR [], X2C_CARD32, X2C_INT32 *, X2C_INT32 *,
                RegComp_Expr *);


static X2C_INT32 factor(X2C_CHAR expr[], X2C_CARD32 expr_len, X2C_INT32 * i,
                X2C_INT32 * res, RegComp_Expr * reg)
{
   RegComp_Expr last = 0;
   *reg = 0;
   if (*res) return *res;
   if (*i>expr_len-1L || expr[*i]==0) return 1L;
   if (expr[*i]=='(') {
      ++*i;
      *reg = new0(8);
      if (*res) return *res;
      *res = re(expr, expr_len, i, res, &(*reg)->next);
      if (*res) return *res;
      if (expr[*i]==')') {
         ++*i;
         dollar(expr, expr_len, i, res, *reg);
      }
      else *res = 1L;
   }
   else if (expr[*i]=='^') {
      ++*i;
      *reg = new0(7);
      if (*res) return *res;
      *res = factor(expr, expr_len, i, res, &(*reg)->next);
      if (*res) return *res;
      if ((*reg)->next->nres>=0) {
         (*reg)->nres = (*reg)->next->nres;
         (*reg)->next->nres = -1;
      }
   }
   else {
      *res = simple(expr, expr_len, i, res, reg);
      if ((*res==0L && *i<expr_len) && (expr[*i]=='^' || expr[*i]=='(')) {
         last = *reg;
         while (last->next && X2C_IN((X2C_INT32)last->kind,32,0xFUL)) {
            last = last->next;
         }
         *res = factor(expr, expr_len, i, res, &last->next);
      }
   }
   return *res;
} /* end factor() */

static X2C_INT32 term(X2C_CHAR [], X2C_CARD32, X2C_INT32 *, X2C_INT32 *,
                RegComp_Expr *);


static X2C_INT32 term(X2C_CHAR expr[], X2C_CARD32 expr_len, X2C_INT32 * i,
                X2C_INT32 * res, RegComp_Expr * reg)
{
   RegComp_Expr t = 0;
   *reg = 0;
   if (*res) return *res;
   if (*i>expr_len-1L || expr[*i]==0) return 1L;
   *res = factor(expr, expr_len, i, res, reg);
   if ((*i<expr_len-1L && expr[*i]=='&') && *res==0L) {
      t = new0(5);
      ++*i;
      t->left = *reg;
      *reg = t;
      *res = term(expr, expr_len, i, res, &t->next);
   }
   return *res;
} /* end term() */


static X2C_INT32 re(X2C_CHAR expr[], X2C_CARD32 expr_len, X2C_INT32 * i,
                X2C_INT32 * res, RegComp_Expr * reg)
{
   RegComp_Expr t = 0;
   *reg = 0;
   if (*res) return *res;
   if (*i>expr_len-1L || expr[*i]==0) return 1L;
   *res = term(expr, expr_len, i, res, reg);
   if ((*i<expr_len-1L && expr[*i]=='|') && *res==0L) {
      t = new0(6);
      ++*i;
      t->left = *reg;
      *reg = t;
      *res = re(expr, expr_len, i, res, &t->next);
   }
   return *res;
} /* end re() */


static void pars_reg(const X2C_CHAR expr[], X2C_CARD32 expr_len,
                RegComp_Expr * reg, X2C_INT32 * i, X2C_INT32 * res)
{
   *reg = 0;
   *res = 0L;
   *res = re(expr, expr_len, i, res, reg);
} /* end pars_reg() */


extern void RegComp_Compile(X2C_CHAR expr[], X2C_CARD32 expr_len,
                RegComp_Expr * reg, X2C_INT32 * res)
{
   X2C_INT32 code;
   X2C_INT32 i;
   i = 0L;
   pars_reg(expr, expr_len, reg, &i, &code);
   if (code) {
      *res = -i;
      return;
   }
   if (i<expr_len && expr[i]) *res = -i;
   else {
      *res = i;
      X2C_NEW(&RegComp_RESULT_desc,(X2C_ADDRESS*) &(*reg)->res,
                sizeof(struct RegComp_RESULT),0);
      for (i = 0L; i<=9L; i++) {
         (*reg)->res->len[i] = 0L;
      } /* end for */
      memcpy((*reg)->res->pos,(*reg)->res->len,40u);
   }
} /* end Compile() */


extern X2C_BOOLEAN RegComp_Const(RegComp_Expr re0)
{
   while (re0->kind==8) re0 = re0->next;
   return re0->kind==0 && re0->next==0;
} /* end Const() */

static X2C_BOOLEAN match0(RegComp_Expr, const X2C_CHAR [], X2C_CARD32,
                X2C_INT32, X2C_INT32 *, struct RegComp_RESULT *, X2C_TD );


static X2C_BOOLEAN bra_seq_end(X2C_INT32 * stop, X2C_INT32 p,
                struct RegComp_RESULT * rs, X2C_TD rs_type, X2C_INT16 n,
                RegComp_Expr * reg)
{
   while (*reg && X2C_IN((X2C_INT32)(*reg)->kind,32,0x18UL)) {
      *reg = (*reg)->next;
   }
   if (*reg) return 0;
   if (n>=0) rs->len[n] = p-rs->pos[n];
   *stop = p;
   return 1;
} /* end bra_seq_end() */


static X2C_BOOLEAN match0(RegComp_Expr reg, const X2C_CHAR s[],
                X2C_CARD32 s_len, X2C_INT32 p, X2C_INT32 * stop,
                struct RegComp_RESULT * rs, X2C_TD rs_type)
{
   X2C_INT16 n;
   X2C_INT32 i;
   struct RegComp__0 * anonym = 0;
   X2C_INT32 tmp;
   *stop = p;
   if (reg==0) return p>s_len-1L || s[p]==0;
   n = reg->nres;
   if (p>s_len-1L || s[p]==0) {
      return reg==0 || X2C_IN((X2C_INT32)reg->kind,32,
                0x18UL) && reg->next==0;
   }
   if (reg->kind==1) {
      if (n>=0) {
         rs->pos[n] = p;
         rs->len[n] = 1L;
      }
      return match0(reg->next, s, s_len, p+1L, stop, rs, rs_type);
   }
   else if (reg->kind==4) {
      if (n>=0) rs->pos[n] = p;
      while (p<s_len && s[p]) {
         if (match0(reg->next, s, s_len, p, stop, rs, rs_type)) {
            if (n>=0) rs->len[n] = p-rs->pos[n];
            return 1;
         }
         ++p;
      }
      return bra_seq_end(stop, p, rs, rs_type, n, &reg);
   }
   else if (reg->kind==2) {
      i = (X2C_INT32)(X2C_INT16)(X2C_CARD8)s[p];
      if (!X2C_IN(i&31L,32,reg->leg[X2C_DIV(i,32L)])) return 0;
      if (n>=0) {
         rs->pos[n] = p;
         rs->len[n] = 1L;
      }
      return match0(reg->next, s, s_len, p+1L, stop, rs, rs_type);
   }
   else if (reg->kind==3) {
      if (n>=0) rs->pos[n] = p;
      while (p<s_len-1L && s[p]) {
         if (match0(reg->next, s, s_len, p, stop, rs, rs_type)) {
            if (n>=0) rs->len[n] = p-rs->pos[n];
            return 1;
         }
         i = (X2C_INT32)(X2C_INT16)(X2C_CARD8)s[p];
         if (!X2C_IN(i&31L,32,reg->leg[X2C_DIV(i,32L)])) return 0;
         ++p;
      }
      return bra_seq_end(stop, p, rs, rs_type, n, &reg);
   }
   else if (reg->kind==0) {
      if (n>=0) rs->pos[n] = p;
      tmp = reg->pat->Len0-2L;
      i = 0L;
      if (i<=tmp) for (;; i++) {
         if (s[p]!=(anonym = reg->pat,anonym->Adr[i])) return 0;
         ++p;
         if (i==tmp) break;
      } /* end for */
      if (n>=0) rs->len[n] = p-rs->pos[n];
      return match0(reg->next, s, s_len, p, stop, rs, rs_type);
   }
   else if (reg->kind==5) {
      return match0(reg->left, s, s_len, p, stop, rs,
                rs_type) && match0(reg->next, s, s_len, p, stop, rs,
                rs_type);
   }
   else if (reg->kind==6) {
      return match0(reg->left, s, s_len, p, stop, rs,
                rs_type) || match0(reg->next, s, s_len, p, stop, rs,
                rs_type);
   }
   else if (reg->kind==7) {
      if (n>=0) rs->pos[n] = p;
      if (match0(reg->next, s, s_len, p, stop, rs, rs_type)) return 0;
      else {
         while (p<s_len-1L && s[p]) ++p;
         *stop = p;
         if (n>=0) rs->len[n] = *stop-rs->pos[n];
         return 1;
      }
   }
   else if (reg->kind==8) {
      if (n>=0) rs->pos[n] = p;
      if (match0(reg->next, s, s_len, p, stop, rs, rs_type)) {
         if (n>=0) rs->len[n] = *stop-rs->pos[n];
         return 1;
      }
      return 0;
   }
   else X2C_ASSERT(79UL);
   return 0;
} /* end match0() */


extern X2C_BOOLEAN RegComp_Match(RegComp_Expr re0, X2C_CHAR s[],
                X2C_CARD32 s_len, X2C_INT32 pos)
{
   X2C_INT32 i;
   struct RegComp_RESULT * anonym = 0;
   for (i = 0L; i<=9L; i++) {
      re0->res->len[i] = 0L;
   } /* end for */
   memcpy(re0->res->pos,re0->res->len,40u);
   return anonym = re0->res,match0(re0, s, s_len, pos, &i, anonym,
                X2C_GET_TD(anonym));
} /* end Match() */


extern void RegComp_Substitute(RegComp_Expr re0, X2C_CHAR s[],
                X2C_CARD32 s_len, X2C_CHAR m[], X2C_CARD32 m_len,
                X2C_CHAR d[], X2C_CARD32 d_len)
{
   X2C_INT32 l;
   X2C_INT32 n;
   X2C_INT32 k;
   X2C_INT32 j;
   X2C_INT32 i;
   X2C_PCOPY((void **)&m,m_len);
   i = 0L;
   j = 0L;
   if (d_len==0L) goto label;
   while (i<m_len && m[i]) {
      if (j==d_len-1L) {
         d[j] = 0;
         goto label;
      }
      if ((m[i]=='\\' && i<m_len-1L) && m[i+1L]=='$') {
         d[j] = '$';
         i += 2L;
         ++j;
      }
      else if ((m[i]=='$' && i<m_len-1L) && X2C_IN((X2C_INT32)((X2C_INT16)
                (X2C_CARD8)m[i+1L]-48),32,0x3FFUL)) {
         n = (X2C_INT32)((X2C_INT16)(X2C_CARD8)m[i+1L]-48);
         k = re0->res->pos[n];
         l = re0->res->len[n];
         if (j+l>d_len-1L) l = (d_len-j)-1L;
         if (k+l>s_len) l = s_len-k;
         while (l>0L) {
            d[j] = s[k];
            ++k;
            ++j;
            --l;
         }
         i += 2L;
      }
      else {
         d[j] = m[i];
         ++i;
         ++j;
      }
   }
   if (j<d_len) d[j] = 0;
   label:;
   X2C_PFREE(m);
} /* end Substitute() */


extern X2C_INT32 RegComp_Len(RegComp_Expr re0, X2C_INT16 n)
{
   return re0->res->len[n];
} /* end Len() */


extern X2C_INT32 RegComp_Pos(RegComp_Expr re0, X2C_INT16 n)
{
   return re0->res->pos[n];
} /* end Pos() */


static void * RegComp_offs[] = {
   X2C_OFS_END
};
static X2C_PROC RegComp_cmds[] = { 0 };
static X2C_CHAR * RegComp_cnms[] = { 0 };
struct X2C_MD_STR RegComp_desc = {
  0, 0, "RegComp",RegComp_offs,RegComp_cmds,RegComp_cnms,
                &RegComp_RESULT_desc
};

extern void RegComp_BEGIN(void)
{
   static int RegComp_init = 0;
   if (RegComp_init) return;
   RegComp_init = 1;
   X2C_MODULE(&RegComp_desc);
}

