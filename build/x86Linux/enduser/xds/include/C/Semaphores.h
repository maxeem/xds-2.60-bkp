/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#ifndef Semaphores_H_
#define Semaphores_H_
#ifndef X2C_H_
#include "X2C.h"
#endif

typedef void *Semaphores_SEMAPHORE;

extern void Semaphores_Create(Semaphores_SEMAPHORE *, X2C_CARD32);

extern void Semaphores_Destroy(Semaphores_SEMAPHORE *);

extern void Semaphores_Claim(Semaphores_SEMAPHORE);

extern void Semaphores_Release(Semaphores_SEMAPHORE);

extern X2C_BOOLEAN Semaphores_CondClaim(Semaphores_SEMAPHORE);

extern X2C_BOOLEAN Semaphores_IsSemaphoreExceptio(void);


extern void Semaphores_BEGIN(void);


#endif /* Semaphores_H_ */
