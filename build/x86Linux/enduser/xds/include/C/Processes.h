/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#ifndef Processes_H_
#define Processes_H_
#ifndef X2C_H_
#include "X2C.h"
#endif

typedef void *Processes_ProcessId;

typedef X2C_ADDRESS Processes_Parameter;

typedef X2C_PROC Processes_Body;

typedef X2C_INT32 Processes_Urgency;

typedef X2C_CARD32 Processes_Sources;

enum Processes_ProcessesExceptions {Processes_passiveProgram,
                Processes_processError};


extern void Processes_Create(X2C_PROC, X2C_CARD32, X2C_INT32, X2C_ADDRESS,
                Processes_ProcessId *);

extern void Processes_Start(X2C_PROC, X2C_CARD32, X2C_INT32, X2C_ADDRESS,
                Processes_ProcessId *);

extern void Processes_StopMe(void);

extern void Processes_SuspendMe(void);

extern void Processes_Activate(Processes_ProcessId);

extern void Processes_SuspendMeAndActivate(Processes_ProcessId);

extern void Processes_Switch(Processes_ProcessId, X2C_ADDRESS *);

extern void Processes_Wait(void);

extern void Processes_Attach(X2C_CARD32);

extern void Processes_Detach(X2C_CARD32);

extern X2C_BOOLEAN Processes_IsAttached(X2C_CARD32);

extern Processes_ProcessId Processes_Handler(X2C_CARD32);

extern Processes_ProcessId Processes_Me(void);

extern X2C_ADDRESS Processes_MyParam(void);

extern X2C_INT32 Processes_UrgencyOf(Processes_ProcessId);

extern X2C_CARD8 Processes_ProcessesException(void);

extern X2C_BOOLEAN Processes_IsProcessesException(void);


extern void Processes_BEGIN(void);


#endif /* Processes_H_ */
