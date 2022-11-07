/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)Processes.c Nov  7 22:55:49 2022" */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef Processes_H_
#include "Processes.h"
#endif
#define Processes_C_
#ifndef EXCEPTIONS_H_
#include "EXCEPTIONS.h"
#endif
#ifndef Storage_H_
#include "Storage.h"
#endif
#ifndef XPrs_H_
#include "XPrs.h"
#endif
#ifndef COROUTINES_H_
#include "COROUTINES.h"
#endif
#ifndef xmRTS_H_
#include "xmRTS.h"
#endif

static EXCEPTIONS_ExceptionSource source;

static XPrs_Process events[32];

static X2C_CARD32 hcnt;

static XPrs_Process corpse;


static void GoNext(void)
{
   COROUTINES_COROUTINE c;
   while (XPrs_current==0) {
      COROUTINES_LISTEN(0);
      COROUTINES_LISTEN(1);
   }
   COROUTINES_TRANSFER(&c, XPrs_current->body);
   if (corpse==0) return;
   if (corpse->wsp) Storage_DEALLOCATE(&corpse->wsp, corpse->wsp_size);
   corpse->magic = 0UL;
   Storage_DEALLOCATE((X2C_ADDRESS*) &corpse,
                sizeof(struct XPrs_ProcessDesc));
} /* end GoNext() */


static void Tie(XPrs_Process p)
{
   XPrs_Process l;
   XPrs_Process max0;
   XPrs_Process min0;
   p->state = XPrs_st_ready;
   p->info = 0;
   if (XPrs_current==0) {
      XPrs_current = p;
      p->fwd = p;
      p->bck = p;
   }
   else {
      XPrs_current->state = XPrs_st_ready;
      XPrs_current->body = COROUTINES_CURRENT();
      if (p->urgency==XPrs_current->urgency) l = XPrs_current;
      else {
         max0 = XPrs_current;
         min0 = max0;
         while (min0->bck!=max0 && min0->bck->urgency<=min0->urgency) {
            min0 = min0->bck;
         }
         max0 = min0->bck;
         if (p->urgency>=max0->urgency || p->urgency<=min0->urgency) {
            l = min0;
         }
         else {
            l = min0;
            while (l->urgency<p->urgency) l = l->fwd;
         }
      }
      p->fwd = l;
      p->bck = l->bck;
      p->fwd->bck = p;
      p->bck->fwd = p;
      if (XPrs_current->urgency<p->urgency) XPrs_current = p;
   }
} /* end Tie() */


static void UnTie(void)
{
   XPrs_Process p;
   p = XPrs_current;
   XPrs_current = p->fwd;
   if (p==XPrs_current) XPrs_current = 0;
   else {
      p->fwd->bck = p->bck;
      p->bck->fwd = p->fwd;
   }
   p->fwd = 0;
   p->bck = 0;
   p->body = COROUTINES_CURRENT();
   p->state = XPrs_st_passive;
} /* end UnTie() */

static void execBody(void);


static void execBody(void)
{
   XPrs_Process p;
   p = XPrs_current;
   p->execBody();
   Processes_StopMe();
} /* end execBody() */


static void cre(Processes_ProcessId * procId, X2C_PROC procBody,
                X2C_INT32 procUrg, X2C_ADDRESS procParams, X2C_CARD32 size,
                X2C_ADDRESS * wsp, XPrs_Process p)
{
   struct X2C_XHandler_STR anonym;
   if (X2C_XTRY(&anonym)) {
      if (p==0 || *wsp==0) {
         EXCEPTIONS_RAISE(source, 1UL, "No memory for process stack", 28ul);
      }
      COROUTINES_NEWCOROUTINE(execBody, *wsp, size, &p->body, 0);
      p->magic = 24555UL;
      p->bck = 0;
      p->fwd = 0;
      p->param = procParams;
      p->info = 0;
      p->urgency = procUrg;
      p->wsp = *wsp;
      p->wsp_size = size;
      p->state = XPrs_st_passive;
      p->execBody = procBody;
      *procId = (Processes_ProcessId)p;
      X2C_XOFF();
   }
   else {
      if (p) {
         Storage_DEALLOCATE((X2C_ADDRESS*) &p,
                sizeof(struct XPrs_ProcessDesc));
      }
      if (*wsp) Storage_DEALLOCATE(wsp, size);
      *procId = 0;
      X2C_XON();
   }
   X2C_XREMOVE();
} /* end cre() */


extern void Processes_Create(X2C_PROC procBody, X2C_CARD32 extraSpace,
                X2C_INT32 procUrg, X2C_ADDRESS procParams,
                Processes_ProcessId * procId)
{
   XPrs_Process p;
   X2C_ADDRESS wsp;
   X2C_CARD32 size;
   p = 0;
   wsp = 0;
   *procId = 0;
   size = extraSpace+1024UL+sizeof(struct X2C_Coroutine_STR);
   Storage_ALLOCATE((X2C_ADDRESS*) &p, sizeof(struct XPrs_ProcessDesc));
   Storage_ALLOCATE(&wsp, size);
   cre(procId, procBody, procUrg, procParams, size, &wsp, p);
} /* end Create() */


extern void Processes_Start(X2C_PROC procBody, X2C_CARD32 extraSpace,
                X2C_INT32 procUrg, X2C_ADDRESS procParams,
                Processes_ProcessId * procId)
{
   Processes_Create(procBody, extraSpace, procUrg, procParams, procId);
   Processes_Activate(*procId);
} /* end Start() */


extern void Processes_StopMe(void)
{
   XPrs_Process p;
   COROUTINES_LISTEN(1);
   p = XPrs_current;
   UnTie();
   if (XPrs_current==0) {
      Tie(p);
      COROUTINES_LISTEN(0);
      X2C_HALT(0UL);
   }
   corpse = p;
   GoNext();
} /* end StopMe() */


extern void Processes_SuspendMe(void)
{
   XPrs_Process p;
   X2C_PROTECTION anonym;
   X2C_PROTECT(&anonym,1);
   p = XPrs_current;
   UnTie();
   if (XPrs_current==0 && hcnt==0UL) {
      Tie(p);
      EXCEPTIONS_RAISE(source, 0UL, "Processes.SuspendMe: Passive program",
                37ul);
   }
   GoNext();
   X2C_PROTECT(&anonym,anonym);
} /* end SuspendMe() */


extern void Processes_Activate(Processes_ProcessId p)
{
   X2C_PROTECTION anonym;
   X2C_PROTECT(&anonym,1);
   if ((XPrs_Process)p==0 || ((XPrs_Process)p)->magic!=24555UL) {
      EXCEPTIONS_RAISE(source, 1UL, "Processes.Activate: Invalid argument",
                37ul);
   }
   if (((XPrs_Process)p)->state!=XPrs_st_passive && ((XPrs_Process)p)->state)
                 goto label;
   Tie((XPrs_Process)p);
   GoNext();
   label:;
   X2C_PROTECT(&anonym,anonym);
} /* end Activate() */


extern void Processes_SuspendMeAndActivate(Processes_ProcessId p)
{
   X2C_PROTECTION anonym;
   X2C_PROTECT(&anonym,1);
   if ((XPrs_Process)p==0 || ((XPrs_Process)p)->magic!=24555UL) {
      EXCEPTIONS_RAISE(source, 1UL, "Processes.SuspendMeAndActivate: Invalid \
argument", 49ul);
   }
   if ((((XPrs_Process)p)->state!=XPrs_st_passive && ((XPrs_Process)p)
                ->state) && (XPrs_Process)p!=XPrs_current) goto label;
   UnTie();
   Tie((XPrs_Process)p);
   GoNext();
   label:;
   X2C_PROTECT(&anonym,anonym);
} /* end SuspendMeAndActivate() */


extern void Processes_Switch(Processes_ProcessId p, X2C_ADDRESS * info)
{
   X2C_PROTECTION anonym;
   X2C_PROTECT(&anonym,1);
   if (((XPrs_Process)p==0 || ((XPrs_Process)p)->magic!=24555UL)
                || ((XPrs_Process)p)->state==XPrs_st_ready) {
      EXCEPTIONS_RAISE(source, 1UL, "Processes.Switch: Invalid argument",
                35ul);
   }
   if (XPrs_current->urgency<=((XPrs_Process)p)->urgency) UnTie();
   Tie((XPrs_Process)p);
   ((XPrs_Process)p)->info = *info;
   GoNext();
   *info = XPrs_current->info;
   X2C_PROTECT(&anonym,anonym);
} /* end Switch() */


extern void Processes_Wait(void)
{
   XPrs_Process p;
   X2C_PROTECTION anonym;
   X2C_PROTECT(&anonym,1);
   p = XPrs_current;
   UnTie();
   p->state = XPrs_st_waiting;
   GoNext();
   X2C_PROTECT(&anonym,anonym);
} /* end Wait() */


extern void Processes_Attach(X2C_CARD32 e)
{
   X2C_PROTECTION anonym;
   X2C_PROTECT(&anonym,1);
   if (e<=31UL) {
      if (events[e]==0) ++hcnt;
      events[e] = XPrs_current;
   }
   X2C_PROTECT(&anonym,anonym);
} /* end Attach() */


extern void Processes_Detach(X2C_CARD32 e)
{
   X2C_PROTECTION anonym;
   X2C_PROTECT(&anonym,1);
   if (e<=31UL) {
      if (events[e]) --hcnt;
      events[e] = 0;
   }
   X2C_PROTECT(&anonym,anonym);
} /* end Detach() */


extern X2C_BOOLEAN Processes_IsAttached(X2C_CARD32 e)
{
   return e<=31UL && events[e];
} /* end IsAttached() */


extern Processes_ProcessId Processes_Handler(X2C_CARD32 e)
{
   if (e>31UL) return 0;
   return (Processes_ProcessId)events[e];
} /* end Handler() */


extern Processes_ProcessId Processes_Me(void)
{
   return (Processes_ProcessId)XPrs_current;
} /* end Me() */


extern X2C_ADDRESS Processes_MyParam(void)
{
   return XPrs_current->param;
} /* end MyParam() */


extern X2C_INT32 Processes_UrgencyOf(Processes_ProcessId procId)
{
   return ((XPrs_Process)procId)->urgency;
} /* end UrgencyOf() */


static void init(void)
{
   X2C_INT32 i;
   hcnt = 0UL;
   corpse = 0;
   for (i = 0L; i<=31L; i++) {
      events[i] = 0;
   } /* end for */
   Storage_ALLOCATE((X2C_ADDRESS*) &XPrs_current,
                sizeof(struct XPrs_ProcessDesc));
   if (XPrs_current==0) {
      EXCEPTIONS_RAISE(source, 1UL, "No memory for initialization of \"Proces\
ses\"", 44ul);
   }
   XPrs_current->magic = 24555UL;
   XPrs_current->fwd = XPrs_current;
   XPrs_current->bck = XPrs_current;
   XPrs_current->param = 0;
   XPrs_current->info = 0;
   XPrs_current->body = COROUTINES_CURRENT();
   XPrs_current->urgency = 0L;
   XPrs_current->wsp = 0;
   XPrs_current->wsp_size = 0UL;
   XPrs_current->state = XPrs_st_ready;
} /* end init() */


extern X2C_CARD8 Processes_ProcessesException(void)
{
   return (X2C_CARD8)EXCEPTIONS_CurrentNumber(source);
} /* end ProcessesException() */


extern X2C_BOOLEAN Processes_IsProcessesException(void)
{
   return EXCEPTIONS_IsCurrentSource(source);
} /* end IsProcessesException() */


extern void Processes_BEGIN(void)
{
   static int Processes_init = 0;
   if (Processes_init) return;
   Processes_init = 1;
   COROUTINES_BEGIN();
   XPrs_BEGIN();
   Storage_BEGIN();
   EXCEPTIONS_BEGIN();
   EXCEPTIONS_AllocateSource(&source);
   init();
}

