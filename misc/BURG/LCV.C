/****************************************************************/
/*  <oburg.c> 1 ??????? 94   ??᫥???? ?????????:  3 䥢ࠫ? 94 */
/*  (?) ?.???㤨?, xTech Ltd., 1994    ????ᨡ????, ?.35-11-53  */
/****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#define BFSIZE 256
static FILE *infp = NULL;       /* ???? ?室???? ⥪???         */
static FILE *outfp = NULL;      /* ???? ??室???? ⥪???        */
static char inbuf[BFSIZE];             /* ????? ?室???? ⥪???        */
/****************************************************************/
void main(int argc, char *argv[])
{
int i, j;                       /* ?ᯮ????⥫???? ????稪?     */
char b[BFSIZE];                 /* ????? ??? ????䨪?樨 ????   */
char bb[BFSIZE];                /* ????? ??? ????䨪?樨 ????   */
char *a;                        /* 㪠?. ?? ??.??ப? ??ࠬ???? */
int c;                          /* ????ୠ? ?????? ??.⥪???    */
/****************************************************************/
/* ?????祭?? ??権 ? ???? 䠩??? ?? ????????? ??ப? MS-DOS    */
/****************************************************************/
	     /* 䠩? ?室???? ⥪???              */
	     for(a=argv[1],j=0;*a!=0 && *a!='.';++a) b[j++]=*a;
	     if(*a==0)
	       b[j++]='.',b[j++]='l',b[j++]='s',b[j++]='t',b[j]=0;
             else { for(;*a!=0;++a) b[j++]=*a; b[j]=0; }
             if ((infp = fopen(b, "r")) == NULL)
             {
		printf("%s: ?? ????뢠???? ??? ?⥭?? 䠩? `%s'\n",
                        argv[0],b);
                exit(1);
             }
	     b[j-1]='v'; b[j-2]='c';
	     if ((outfp = fopen(b, "w")) == NULL)
             {
	       printf("%s: ?? ????뢠???? ??? ?????? 䠩? `%s'\n",
                       argv[0], b);
               exit(1);
             }

    for(i=0; fgets(inbuf, sizeof inbuf, infp) != NULL; ++i)
    {
      if(inbuf[25]=='-') exit(1);
      if(i>4) fputs(inbuf+25, outfp);
    }
}

