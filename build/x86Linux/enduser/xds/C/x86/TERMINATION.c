/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)TERMINATION.c Nov  7 22:55:32 2022" */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef TERMINATION_H_
#include "TERMINATION.h"
#endif
#define TERMINATION_C_
#include "X2C.h"
#ifndef xmRTS_H_
#include "xmRTS.h"
#endif
#ifndef xrtsOS_H_
#include "xrtsOS.h"
#endif

static X2C_BOOLEAN is_terminating;

static X2C_BOOLEAN has_halted;


extern X2C_BOOLEAN TERMINATION_IsTerminating(void)
{
   return is_terminating;
} /* end IsTerminating() */


extern X2C_BOOLEAN TERMINATION_HasHalted(void)
{
   return has_halted;
} /* end HasHalted() */

#define TERMINATION_ABORT_EXIT_CODE 9

extern void X2C_HALT(X2C_INT32);


extern void X2C_HALT(X2C_INT32 x)
{
   has_halted = 1;
   X2C_doexit(x);
} /* end X2C_HALT() */


extern void X2C_ABORT(void)
{
   X2C_HALT(9L);
} /* end X2C_ABORT() */

struct FinalRec;

typedef struct FinalRec * Final;


struct FinalRec {
   X2C_PROC proc;
   Final next;
};

static Final finals;


static void do_final(X2C_PROC p)
{
   struct X2C_XHandler_STR anonym;
   if (X2C_XTRY(&anonym)) {
      p();
      X2C_XOFF();
   }
   else {
   }
   X2C_XREMOVE();
} /* end do_final() */

static void atexit_procedure(void);


static void atexit_procedure(void)
{
   X2C_PROC p;
   Final f;
   is_terminating = 1;
   while (finals) {
      f = finals;
      finals = f->next;
      p = f->proc;
      do_final(p);
   }
   X2C_show_profile();
} /* end atexit_procedure() */

extern void X2C_FINALEXE(X2C_PROC);


extern void X2C_FINALEXE(X2C_PROC proc)
{
   Final f;
   f = (Final)X2C_AllocMem(sizeof(struct FinalRec));
   if (f==0) X2C_TRAP((X2C_INT32)X2C_noMemoryException);
   f->proc = proc;
   f->next = finals;
   finals = f;
} /* end X2C_FINALEXE() */


extern void X2C_FINALDLL(X2C_ADDRESS * finalHead, X2C_PROC proc)
{
   Final f;
   f = (Final)X2C_AllocMem(sizeof(struct FinalRec));
   if (f==0) X2C_TRAP((X2C_INT32)X2C_noMemoryException);
   f->proc = proc;
   f->next = (Final)*finalHead;
   *finalHead = (X2C_ADDRESS)f;
} /* end X2C_FINALDLL() */


extern void X2C_FINALLY(X2C_PROC proc)
{
   X2C_FINALEXE(proc);
} /* end X2C_FINALLY() */


extern void X2C_EXIT(void)
{
   X2C_doexit(0L);
} /* end X2C_EXIT() */


static void do_finald(X2C_PROC p)
{
   struct X2C_XHandler_STR anonym;
   if (X2C_XTRY(&anonym)) {
      p();
      X2C_XOFF();
   }
   else {
   }
   X2C_XREMOVE();
} /* end do_finald() */


extern void X2C_EXITDLL(X2C_ADDRESS * finalHead)
{
   X2C_PROC p;
   Final f;
   while (*finalHead) {
      f = (Final)*finalHead;
      *finalHead = (X2C_ADDRESS)f->next;
      p = f->proc;
      do_finald(p);
   }
} /* end X2C_EXITDLL() */


extern void X2C_ini_termination(void)
{
   is_terminating = 0;
   has_halted = 0;
   X2C_iniexit();
   X2C_atexit(atexit_procedure);
} /* end X2C_ini_termination() */


extern void TERMINATION_BEGIN(void)
{
   static int TERMINATION_init = 0;
   if (TERMINATION_init) return;
   TERMINATION_init = 1;
}

