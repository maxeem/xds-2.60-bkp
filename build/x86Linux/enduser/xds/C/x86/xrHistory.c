/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)xrHistory.c Nov 19  1:11:33 2022" */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef xrHistory_H_
#include "xrHistory.h"
#endif
#define xrHistory_C_
#ifndef xmRTS_H_
#include "xmRTS.h"
#endif
#include "X2C.h"
#ifndef xruSTABS_H_
#include "xruSTABS.h"
#endif
#ifndef xrnStkScan_H_
#include "xrnStkScan.h"
#endif
#include "xPOSIX.h"


extern void X2C_scanStackHistory(X2C_ADDRESS from, X2C_ADDRESS to,
                X2C_BOOLEAN exact)
{
   X2C_STACK_SCAN_PROC(from, to, exact);
} /* end X2C_scanStackHistory() */

extern void X2C_SET_CODE_EXTENT(X2C_INT32, X2C_INT32);

static X2C_BOOLEAN HISTORY_WAS_INIT;

#define maps_name "/proc/self/maps"


extern void X2C_INIT_HISTORY(void)
{
   FILE * maps;
   X2C_INT32 cend;
   X2C_INT32 cbeg;
   if (HISTORY_WAS_INIT) return;
   HISTORY_WAS_INIT = 1;
   maps = (FILE *)fopen("/proc/self/maps", "rb");
   if (maps==0) {
      cbeg = 1L;
      cend = 0L;
   }
   else {
      if (2!=fscanf(maps, "%lx-%lx", (X2C_ADDRESS) &cbeg,
                (X2C_ADDRESS) &cend)) {
         cbeg = 1L;
         cend = 0L;
      }
      fclose(maps);
   }
   X2C_SET_CODE_EXTENT(cbeg, cend);
} /* end X2C_INIT_HISTORY() */

typedef X2C_CHAR NAME[64];


static void GetInfo(X2C_CARD32 ip, NAME fn, NAME pn, X2C_CARD32 * ln,
                X2C_CARD32 * off)
{
   X2C_CARD32 last_block_value;
   X2C_CARD32 i;
   struct xruSTABS_STAB st;
   NAME cur_pn;
   NAME cur_fn;
   NAME name;
   X2C_CARD32 stabstr_off;
   X2C_CARD32 prev_stabstr_off;
   X2C_CARD32 d_off;
   X2C_CARD32 cur_off;
   X2C_CARD32 cur_ln;
   X2C_BOOLEAN Error;
   X2C_CARD32 tmp;
   cur_fn[0] = 0;
   cur_pn[0] = 0;
   d_off = 0UL;
   cur_ln = 0UL;
   cur_off = 0UL;
   stabstr_off = 0UL;
   prev_stabstr_off = 0UL;
   last_block_value = 0UL;
   Error = 0;
   tmp = xruSTABS_GetStabsNumber()-1UL;
   i = 0UL;
   if (i<=tmp) for (;; i++) {
      *off = cur_off;
      *ln = cur_ln;
      memcpy(pn,cur_pn,64u);
      memcpy(fn,cur_fn,64u);
      xruSTABS_GetStab(prev_stabstr_off, &Error, i, &st, name, 64ul);
      if (Error) {
         *ln = 0UL;
         pn[0] = 0;
         fn[0] = 0;
         *off = 0UL;
         return;
      }
      if ((X2C_CARD32)st.n_type==0UL) {
         prev_stabstr_off = stabstr_off;
         stabstr_off += st.n_value;
      }
      else if ((X2C_CARD32)st.n_type==100UL) {
         memcpy(cur_fn,name,64u);
         d_off = 0UL;
         cur_ln = 0UL;
         last_block_value = st.n_value;
      }
      else if ((X2C_CARD32)st.n_type==36UL) {
         memcpy(cur_pn,name,64u);
         d_off = 0UL;
         cur_ln = (X2C_CARD32)st.n_desc;
         last_block_value = st.n_value;
      }
      else if ((X2C_CARD32)st.n_type==68UL) {
         cur_ln = (X2C_CARD32)st.n_desc;
         d_off = st.n_value;
      }
      cur_off = d_off+last_block_value;
      if (cur_off>ip) return;
      if (i==tmp) break;
   } /* end for */
} /* end GetInfo() */


extern void X2C_show_history(void)
{
   X2C_INT32 len;
   X2C_INT32 i;
   X2C_CARD32 offset;
   X2C_CARD32 lineno;
   NAME procname;
   NAME filename;
   X2C_BOOLEAN err;
   X2C_Coroutine Current;
   X2C_INT32 tmp;
   Current = X2C_GetCurrent();
   len = (X2C_INT32)Current->his_cnt;
   if (len>256L) len = 256L;
   xruSTABS_OpenMyExe(&err);
   if ((!HISTORY_WAS_INIT || err) || len<=0L) {
      printf("#RTS: No history available.\n");
      return;
   }
   printf("             Source file              LineNo   CodeOffset     Proc\
edure name\n");
   tmp = len-1L;
   i = 0L;
   if (i<=tmp) for (;; i++) {
      GetInfo(Current->his[i], filename, procname, &lineno, &offset);
      printf("%-37s  %5d    %.8x   %-20s\n", filename, lineno,
                Current->his[i], procname);
      if (i==tmp) break;
   } /* end for */
   if ((X2C_INT32)Current->his_cnt>256L) {
      printf("#RTS: History stack was truncated: not enough room.\n");
   }
   xruSTABS_CloseMyExe();
} /* end X2C_show_history() */


extern void X2C_show_profile(void)
{
} /* end X2C_show_profile() */


extern void X2C_HIS_SAVE(X2C_INT16 * sv)
{
} /* end X2C_HIS_SAVE() */


extern void X2C_HIS_RESTORE(X2C_INT16 sv)
{
} /* end X2C_HIS_RESTORE() */


extern void X2C_Profiler_clock(void)
{
} /* end X2C_Profiler_clock() */


extern void X2C_PROC_INP_F(X2C_CHAR file[], X2C_INT32 line)
{
} /* end X2C_PROC_INP_F() */


extern void X2C_PROC_PRF_F(X2C_CHAR file[], X2C_INT32 line)
{
} /* end X2C_PROC_PRF_F() */


extern void X2C_PROC_OUT_F(void)
{
} /* end X2C_PROC_OUT_F() */


extern void xrHistory_BEGIN(void)
{
   static int xrHistory_init = 0;
   if (xrHistory_init) return;
   xrHistory_init = 1;
   if (sizeof(NAME)!=64) X2C_ASSERT(0);
   xruSTABS_BEGIN();
}

