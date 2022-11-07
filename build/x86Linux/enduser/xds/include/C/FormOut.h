/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#ifndef FormOut_H_
#define FormOut_H_
#ifndef X2C_H_
#include "X2C.h"
#endif

#define FormOut_default "0"

#define FormOut_text "2"

#define FormOut_cr "\015"

#define FormOut_lf "\012"

#define FormOut_crlf "1"

typedef void ( *FormOut_write_proc)(X2C_ADDRESS, X2C_CHAR [], X2C_CARD32,
                X2C_INT32);

extern void FormOut_format(X2C_ADDRESS, FormOut_write_proc, X2C_CHAR [],
                X2C_CARD32, X2C_CHAR, X2C_ADDRESS, X2C_CARD32);

extern void FormOut_LineSeparator(X2C_CHAR [], X2C_CARD32);

extern void FormOut_TextSeparator(X2C_CHAR [], X2C_CARD32);


extern void FormOut_BEGIN(void);


#endif /* FormOut_H_ */
