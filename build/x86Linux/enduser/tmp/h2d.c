/* "@(#)h2d.c Nov  7 22:56:04 2022" */
/* Generated by XDS Oberon-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef h2d_H_
#include "h2d.h"
#endif
#define h2d_C_
#ifndef Printf_H_
#include "Printf.h"
#endif
#ifndef ProgEnv_H_
#include "ProgEnv.h"
#endif
#ifndef H2DCfg_H_
#include "H2DCfg.h"
#endif
#ifndef LongStrs_H_
#include "LongStrs.h"
#endif
#ifndef H2DMsg_H_
#include "H2DMsg.h"
#endif
#ifndef adt_H_
#include "adt.h"
#endif
#ifndef H2DFile_H_
#include "H2DFile.h"
#endif
#ifndef H2DObjs_H_
#include "H2DObjs.h"
#endif
#ifndef H2DParse_H_
#include "H2DParse.h"
#endif
#ifndef H2DGen_H_
#include "H2DGen.h"
#endif

extern struct X2C_MD_STR h2d_desc;
struct h2d_OptionDesc;
extern struct X2C_TD_STR h2d_OptionDesc_desc;

typedef struct h2d_OptionDesc * Option0;


struct h2d_OptionDesc {
   X2C_INT32 _dummy_;
   LongStrs_String name;
   LongStrs_String value;
};
static X2C_PROC h2d_OptionDesc_proc[] = {
   (X2C_PROC)adt_Compare0,
   (X2C_PROC)adt_SetName
};
static void * h2d_OptionDesc_offs[] = {
   X2C_OFS(struct h2d_OptionDesc,name),
   X2C_OFS(struct h2d_OptionDesc,value),
   X2C_OFS_END
};
struct X2C_TD_STR h2d_OptionDesc_desc = {
   sizeof(struct h2d_OptionDesc), "OptionDesc",
   &h2d_desc, 0, 2, 2,
   { &adt_ElementDesc_desc, &adt_NamedElementDesc_desc, &h2d_OptionDesc_desc,
                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
   h2d_OptionDesc_proc, h2d_OptionDesc_offs, 0, 0, 0, &h2d_OptionDesc_desc,
                0x93678150lu
};

static LongStrs_String configuration;

static LongStrs_String header;

static LongStrs_String definition;

static adt_Element e;

static adt_NamedElement ne;

static H2DObjs_Header h;

static X2C_INT32 arg_num;

static adt_List project_list;

static X2C_BOOLEAN cstdlib;

static X2C_BOOLEAN show_stat;

#define h2d_opt_undef 0

#define h2d_opt_on 1

#define h2d_prj_opt_p 2

#define h2d_prj_opt_prj 3

static LongStrs_String prj_name;

static adt_List filenames;

static X2C_INT32 prj_opt;

static X2C_INT32 o_opt;

static adt_List options;


static void get_option(X2C_CHAR option[], X2C_CARD32 option_len,
                X2C_CHAR name[], X2C_CARD32 name_len, X2C_CHAR value[],
                X2C_CARD32 value_len)
{
   X2C_INT32 j;
   X2C_INT32 i;
   X2C_SEQ tmp[3];
   X2C_PCOPY((void **)&option,option_len);
   i = 1L;
   j = 0L;
   while (((X2C_CARD8)option[i]>='A' && (X2C_CARD8)
                option[i]<='Z' || (X2C_CARD8)option[i]>='a' && (X2C_CARD8)
                option[i]<='z') || (X2C_CARD8)option[i]>='0' && (X2C_CARD8)
                option[i]<='9') {
      name[j] = X2C_CAP(option[i]);
      ++i;
      ++j;
   }
   name[j] = 0x0U ;
   while (option[i]==' ') ++i;
   if (option[i]=='=') {
      ++i;
      while (option[i]==' ') ++i;
      j = 0L;
      if (option[i]=='\"') {
         ++i;
         while (option[i] && option[i]!='\"') {
            value[j] = option[i];
            ++i;
            ++j;
         }
         if (option[i]==0x0U ) {
            H2DMsg_Error0(71L, (tmp[0].adr = name, tmp[1].val = 0,
                tmp[2].val = name_len-1, (X2C_LOC *)tmp),
                3ul*sizeof(X2C_SEQ));
            goto label;
         }
         value[j] = 0x0U ;
      }
      else {
         while (option[i] && option[i]!=' ') {
            value[j] = option[i];
            ++i;
            ++j;
         }
         value[j] = 0x0U ;
      }
   }
   else if (option[i]=='-') X2C_COPY("Off",4ul,value,value_len);
   else if (option[i]=='+') X2C_COPY("On",3ul,value,value_len);
   else {
      H2DMsg_Error0(71L, (tmp[0].adr = name, tmp[1].val = 0,
                tmp[2].val = name_len-1, (X2C_LOC *)tmp),
                3ul*sizeof(X2C_SEQ));
   }
   label:;
   X2C_PFREE(option);
} /* end get_option() */


static void ParseCommandLine(void)
{
   X2C_INT32 i;
   LongStrs_String arg = 0;
   adt_NamedElement ne0 = 0;
   X2C_CHAR value[100];
   X2C_CHAR name[100];
   Option0 option = 0;
   X2C_SEQ tmp[3];
   adt_NewList(&options);
   arg_num = (X2C_INT32)ProgEnv_ArgNumber();
   i = 0L;
   arg = 0;
   prj_name = 0;
   adt_NewList(&filenames);
   prj_opt = 0L;
   o_opt = 0L;
   while (i<arg_num) {
      LongStrs_Allocate(&arg, (X2C_INT32)(ProgEnv_ArgLength((X2C_CARD32)i)+1UL));
      ProgEnv_GetArg((X2C_CARD32)i, arg->Adr, arg->Len0);
      ++i;
      if (arg->Adr[0UL]=='=') {
         if (arg->Adr[2UL]==0x0U ) {
            if (X2C_CAP(arg->Adr[1UL])=='P') {
               if (prj_opt==0L) {
                  prj_opt = 2L;
                  if (i<arg_num) {
                     LongStrs_Allocate(&prj_name,
                (X2C_INT32)(ProgEnv_ArgLength((X2C_CARD32)i)+1UL));
                     ProgEnv_GetArg((X2C_CARD32)i, prj_name->Adr,
                prj_name->Len0);
                     ++i;
                  }
                  else {
                     H2DMsg_Error0(63L, (tmp[0].adr = "", tmp[1].val = 0,
                tmp[2].val = 1u-1, (X2C_LOC *)tmp), 3ul*sizeof(X2C_SEQ));
                  }
               }
               else {
                  H2DMsg_Error0(72L, (tmp[0].adr = "=p", tmp[1].val = 0,
                tmp[2].val = 3u-1, (X2C_LOC *)tmp), 3ul*sizeof(X2C_SEQ));
                  return;
               }
            }
            else if (X2C_CAP(arg->Adr[1UL])=='O') {
               if (o_opt==0L) o_opt = 1L;
               else {
                  H2DMsg_Error0(72L, (tmp[0].adr = "=o", tmp[1].val = 0,
                tmp[2].val = 3u-1, (X2C_LOC *)tmp), 3ul*sizeof(X2C_SEQ));
                  return;
               }
            }
            else {
               H2DMsg_Error0(73L, (tmp[0].adr = arg->Adr, tmp[1].val = 0,
                tmp[2].val = arg->Len0*1u-1, (X2C_LOC *)tmp),
                3ul*sizeof(X2C_SEQ));
               return;
            }
         }
         else {
            H2DMsg_Error0(73L, (tmp[0].adr = arg->Adr, tmp[1].val = 0,
                tmp[2].val = arg->Len0*1u-1, (X2C_LOC *)tmp),
                3ul*sizeof(X2C_SEQ));
            return;
         }
      }
      else if (arg->Adr[0UL]=='-') {
         get_option(arg->Adr, arg->Len0, name, 100ul, value, 100ul);
         if (H2DMsg_WasError) return;
         if (X2C_STRCMP(name,100u,"PRJ",4u)==0) {
            if (prj_opt==0L) {
               prj_opt = 3L;
               LongStrs_Assign(value, 100ul, &prj_name);
            }
            else {
               H2DMsg_Error0(72L, (tmp[0].adr = "-prj", tmp[1].val = 0,
                tmp[2].val = 5u-1, (X2C_LOC *)tmp), 3ul*sizeof(X2C_SEQ));
               return;
            }
         }
         else {
            X2C_NEW(&h2d_OptionDesc_desc,(X2C_ADDRESS*) &option,
                sizeof(struct h2d_OptionDesc),0);
            X2C_CALL(adt_SetName_,X2C_GET_TD(option),
                1)((adt_NamedElement)option, name, 100ul);
            LongStrs_Assign(value, 100ul, &option->value);
            X2C_CALL(adt_Insert_0,X2C_GET_TD(options),14)(options,
                (adt_Element)option);
         }
      }
      else {
         adt_NewNamedElement(&ne0, arg->Adr, arg->Len0);
         X2C_CALL(adt_Insert_0,X2C_GET_TD(filenames),14)(filenames,
                (adt_Element)ne0);
      }
   }
} /* end ParseCommandLine() */


static X2C_BOOLEAN get_name(LongStrs_String * name)
{
   adt_Element e0 = 0;
   LongStrs_String anonym0 = 0;
   if (project_list==0 || prj_opt==3L) {
      X2C_CALL(adt_FindNext_0,X2C_GET_TD(filenames),8)(filenames, &e0);
      if (e0) {
         *name = ((adt_NamedElement)e0)->name;
         cstdlib = H2DCfg_CStdLib;
         return 1;
      }
      else return 0;
   }
   else {
      X2C_CALL(adt_FindNext_0,X2C_GET_TD(project_list),8)(project_list, &e0);
      if (e0) {
         anonym0 = ((adt_NamedElement)e0)->name;
         LongStrs_Assign(anonym0->Adr, anonym0->Len0, name);
         cstdlib = ((H2DObjs_Module)e0)->cstdlib;
      }
      return e0!=0;
   }
   return 0;
} /* end get_name() */


static void SetOptions(void)
{
   adt_Element e0 = 0;
   X2C_INT32 err;
   LongStrs_String anonym0 = 0;
   LongStrs_String anonym1 = 0;
   LongStrs_String anonym2 = 0;
   LongStrs_String anonym3 = 0;
   LongStrs_String anonym4 = 0;
   LongStrs_String anonym5 = 0;
   X2C_SEQ tmp[3];
   if (!X2C_CALL(adt_IsEmpty_1,X2C_GET_TD(options),4)(options)) {
      X2C_CALL(adt_FindFirst_0,X2C_GET_TD(options),6)(options, &e0);
      while (e0) {
         if ((anonym0 = ((Option0)e0)->name,X2C_STRCMP(anonym0->Adr,
                anonym0->Len0,"CTYPE",6u)) && (anonym1 = ((Option0)e0)->name,
                X2C_STRCMP(anonym1->Adr,anonym1->Len0,"M2TYPE",7u))) {
            err = (anonym2 = ((Option0)e0)->name,
                (anonym3 = ((Option0)e0)->value,H2DCfg_GetInfo(anonym2->Adr,
                anonym2->Len0, anonym3->Adr, anonym3->Len0, 1)));
            if (err>=0L) {
               anonym4 = ((Option0)e0)->name;
               H2DMsg_Error0(err, (tmp[0].adr = anonym4->Adr, tmp[1].val = 0,
                 tmp[2].val = anonym4->Len0*1u-1, (X2C_LOC *)tmp),
                3ul*sizeof(X2C_SEQ));
               return;
            }
         }
         else {
            anonym5 = ((Option0)e0)->name;
            H2DMsg_Error0(71L, (tmp[0].adr = anonym5->Adr, tmp[1].val = 0,
                tmp[2].val = anonym5->Len0*1u-1, (X2C_LOC *)tmp),
                3ul*sizeof(X2C_SEQ));
            return;
         }
         X2C_CALL(adt_FindNext_0,X2C_GET_TD(options),8)(options, &e0);
      }
   }
} /* end SetOptions() */

static LongStrs_String anonym;


static void * h2d_offs[] = {
   &definition,
   &header,
   &configuration,
   &e,
   &ne,
   &h,
   &project_list,
   &prj_name,
   &filenames,
   &options,
   &anonym,
   X2C_OFS_END
};
static X2C_PROC h2d_cmds[] = { 0 };
static X2C_CHAR * h2d_cnms[] = { 0 };
struct X2C_MD_STR h2d_desc = {
  0, 0, "h2d",h2d_offs,h2d_cmds,h2d_cnms,&h2d_OptionDesc_desc
};

X2C_STACK_LIMIT(8000000l)
extern int main(int argc, char **argv)
{
   X2C_BEGIN(&argc,argv,1,8000000l,16000000l);
   LongStrs_BEGIN();
   adt_BEGIN();
   H2DGen_BEGIN();
   H2DParse_BEGIN();
   H2DFile_BEGIN();
   H2DObjs_BEGIN();
   H2DMsg_BEGIN();
   H2DCfg_BEGIN();
   ProgEnv_BEGIN();
   Printf_BEGIN();
   X2C_MODULE(&h2d_desc);
   ParseCommandLine();
   if (!H2DMsg_WasError) {
      if (arg_num==0L) H2DMsg_Help();
      H2DFile_CreateName("", 1ul, H2DFile_ProgramName->Adr,
                H2DFile_ProgramName->Len0, "cfg", 4ul, &configuration);
      H2DParse_ParseConfig(configuration->Adr, configuration->Len0);
      if (prj_opt) {
         project_list = H2DParse_ParseProject(prj_name->Adr, prj_name->Len0);
         X2C_CALL(adt_Reset_,X2C_GET_TD(project_list),9)(project_list);
         if (prj_opt!=2L) project_list = 0;
      }
      SetOptions();
      if (!H2DMsg_WasError) {
         show_stat = 0;
         X2C_CALL(adt_Reset_,X2C_GET_TD(filenames),9)(filenames);
         while (get_name(&header)) {
            show_stat = 1;
            H2DMsg_WasError = 0;
            definition = 0;
            H2DGen_GetOutputFileName(header->Adr, header->Len0, &definition);
            X2C_NEW(&adt_NamedElementDesc_desc,(X2C_ADDRESS*) &ne,
                sizeof(struct adt_NamedElementDesc),0);
            X2C_CALL(adt_SetName_,X2C_GET_TD(ne),1)(ne, header->Adr,
                header->Len0);
            X2C_CALL(adt_Find_0,X2C_GET_TD(H2DObjs_Headers),
                11)(H2DObjs_Headers, (adt_Element)ne, &e);
            if (!H2DMsg_WasError && ((!H2DFile_Exist(definition->Adr,
                definition->Len0) || H2DCfg_Retranslate) && e==0)) {
               if (H2DCfg_HeadersMerging) adt_NewList(&H2DObjs_Headers);
               H2DObjs_CurrentHeader = H2DObjs_SuperHeader;
               H2DParse_Parse(header->Adr, header->Len0, cstdlib);
               X2C_CALL(adt_FindLast_0,X2C_GET_TD(H2DObjs_Headers),
                5)(H2DObjs_Headers, &e);
               while (e) {
                  h = (H2DObjs_Header)e;
                  anonym = h->name;
                  H2DGen_GetOutputFileName(anonym->Adr, anonym->Len0,
                &definition);
                  if (!h->generated && (!H2DFile_Exist(definition->Adr,
                definition->Len0) || H2DCfg_Retranslate)) {
                     X2C_CALL(H2DMsg_ShowHeader_,X2C_GET_TD(h->stat),
                5)(h->stat);
                     if (h->parsed) {
                        H2DMsg_WasError = 0;
                        H2DGen_Generate(h);
                     }
                     h->generated = 1;
                     X2C_CALL(H2DMsg_ShowFooter_,X2C_GET_TD(h->stat),
                4)(h->stat);
                  }
                  X2C_CALL(adt_FindPrev_0,X2C_GET_TD(H2DObjs_Headers),
                7)(H2DObjs_Headers, &e);
               }
            }
         }
         if (show_stat) {
            X2C_CALL(H2DMsg_ShowHeader_,
                X2C_GET_TD(H2DObjs_SuperHeader->stat),
                5)(H2DObjs_SuperHeader->stat);
            X2C_CALL(H2DMsg_ShowFooter_,
                X2C_GET_TD(H2DObjs_SuperHeader->stat),
                4)(H2DObjs_SuperHeader->stat);
            H2DMsg_GlobalStatistics();
         }
         if (o_opt==1L) H2DCfg_PrintOptions();
      }
   }
   X2C_EXIT();
   return 0;
}

X2C_MAIN_DEFINITION
