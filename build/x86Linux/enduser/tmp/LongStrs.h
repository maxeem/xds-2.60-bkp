/* Generated by XDS Oberon-2 to ANSI C v4.20 translator */

#ifndef LongStrs_H_
#define LongStrs_H_
#ifndef X2C_H_
#include "X2C.h"
#endif

#define LongStrs_SPACE 0x20U 

#define LongStrs_TAB 0x9U 

#define LongStrs_none (-1)

typedef X2C_INT32 LongStrs_INT;


struct LongStrs__0 {
   X2C_CHAR * Adr;
   X2C_INDEX Len0;
};

typedef struct LongStrs__0 * LongStrs_String;

extern void LongStrs_Deallocate(LongStrs_String *);

extern void LongStrs_Allocate(LongStrs_String *, X2C_INT32);

extern X2C_INT32 LongStrs_Length(X2C_CHAR [], X2C_CARD32);

extern X2C_INT32 LongStrs_Length1(LongStrs_String);

extern void LongStrs_Assign(X2C_CHAR [], X2C_CARD32, LongStrs_String *);

extern void LongStrs_Extract(X2C_CHAR [], X2C_CARD32, X2C_INT32, X2C_INT32,
                LongStrs_String *);

extern void LongStrs_Insert(X2C_CHAR [], X2C_CARD32, X2C_INT32,
                LongStrs_String *);

extern void LongStrs_Delete(X2C_CHAR [], X2C_CARD32, X2C_INT32, X2C_INT32);

extern void LongStrs_Append(X2C_CHAR [], X2C_CARD32, LongStrs_String *);

extern void LongStrs_Concat(X2C_CHAR [], X2C_CARD32, X2C_CHAR [], X2C_CARD32,
                 LongStrs_String *);

extern void LongStrs_AppendChar(X2C_CHAR, LongStrs_String *);

extern void LongStrs_CutSpace(X2C_CHAR [], X2C_CARD32);

extern void LongStrs_Capitalize(X2C_CHAR [], X2C_CARD32);

extern X2C_INT32 LongStrs_FindPos(X2C_CHAR [], X2C_CARD32, X2C_CHAR);

extern X2C_INT32 LongStrs_BackFindPos(X2C_CHAR [], X2C_CARD32, X2C_CHAR);

extern void LongStrs_Fill(LongStrs_String *, X2C_CHAR, X2C_INT32);

extern void LongStrs_IntToStr(X2C_INT32, LongStrs_String *);

extern void LongStrs_RealToStr(X2C_LONGREAL, LongStrs_String *);


extern void LongStrs_BEGIN(void);


#endif /* LongStrs_H_ */
