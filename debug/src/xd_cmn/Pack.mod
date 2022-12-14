<* Storage + *>

IMPLEMENTATION MODULE Pack;
(* 彔猸氅 珷ょí *)

IMPORT brk := CtrlC;

IMPORT xStr;
IMPORT red := RedFile;
IMPORT fil := File;
IMPORT opt := Options;
IMPORT pro := Protocol;
IMPORT msg := MsgNo;
IMPORT err := Errors;
IMPORT txt := Texts;

IMPORT krn := KrnTypes;

IMPORT exp := Expr;

IMPORT typ := PckTypes;
IMPORT bas := PckBase;
IMPORT ope := PckOpers;
IMPORT lst := Lists;

IMPORT key := Keys;

<* IF DEST_K26 THEN *>

IMPORT PckModel;

<* END *>


VAR
  Line: xStr.txt_ptr;

(*北北北北北北北 憽 猱? ? ㄥ ム獱 北北北北北北北北北北北北北北北北北*)
PROCEDURE Label_Collect_And_Check;
VAR
  name1     ,
  name2     : xStr.txt_ptr;
  name3     ,
  name4     : xStr.String;
  i         : CARDINAL;
  FileExt   : BOOLEAN;
  PosStr    : CARDINAL;
  Param     : xStr.String;

BEGIN
  IF typ.Pakets[typ.CurrPaket].Reference THEN RETURN; END;
  (* 嵁? 岖イ? 徕喈 *)
  typ.Pakets[typ.CurrPaket].LastLine := txt.LastLine(typ.Pakets[typ.CurrPaket].Paket);
  IF typ.Pakets[typ.CurrPaket].LastLine = 0 THEN RETURN; END;
  DEC(typ.Pakets[typ.CurrPaket].LastLine);
  (* 崰绋瓲ガ ? 啖 *)
  typ.Pakets[typ.CurrPaket].LineNum := 1;
  LOOP
    (* 忇 ⅴ犰 癄?? *)
    IF typ.Pakets[typ.CurrPaket].LineNum-1 > typ.Pakets[typ.CurrPaket].LastLine THEN EXIT END;
    txt.GetLine(typ.Pakets[typ.CurrPaket].Paket,typ.Pakets[typ.CurrPaket].LineNum-1, Line);
    PosStr := 0;
    IF NOT bas.SkipBlanks(Line^, PosStr) AND (PosStr = 0) THEN
      ASSERT(bas.GetParam(Line^, PosStr, Param));
      IF (Param[0] = '#') THEN
        IF (Param = '#IMPORT') OR (Param = '#垖弾悞') THEN
          IF bas.GetParam(Line^, PosStr, Param) THEN
            IF exp.CheckFileName(Param, FileExt) THEN
              xStr.Uppercase(Param);
              IF NOT FileExt THEN fil.ChangeExtension(Param, krn.imp_file_ext); END;
              txt.GetName(typ.Pakets[typ.CurrPaket].Paket, name1);
              bas.FileName(name1^, name3);
              pro.WriteMsgNo(msg.Include, TRUE, pro.to_file, name3,
                             typ.Pakets[typ.CurrPaket].LineNum, PosStr+1, Param);
              IF red.Read(Param, name4) = red.Ok THEN
                xStr.Uppercase(name4);
                i := 0;
                LOOP
                  IF i = typ.QuantityPaket THEN
                    txt.Open(typ.Pakets[typ.QuantityPaket].Paket, name4);
                    EXIT;
                  END;
                  txt.GetName(typ.Pakets[i].Paket,name1);
                  IF name1^ = name4 THEN
                    typ.Pakets[typ.QuantityPaket].Paket := typ.Pakets[i].Paket;
                    typ.Pakets[typ.QuantityPaket].Reference := TRUE;
                    EXIT;
                  END;
                  INC(i);
                END;
                IF typ.QuantityPaket < typ.MaxPakets THEN
                  IF typ.Pakets[typ.QuantityPaket].Paket <> txt.nil THEN
                    txt.GetName (typ.Pakets[typ.QuantityPaket].Paket, name1);
                    xStr.Uppercase (name1^);
                    i := typ.CurrPaket;
                    LOOP
                      txt.GetName (typ.Pakets[i].Paket,name2);
                      IF name1^ = name2^ THEN
                        bas.FileName(name1^, name3);
                        err.FatalError;
                        err.Error(msg.Paket_cross_reference, name3);
                      END;
                      IF typ.Pakets[i].RetPaket = MAX(CARDINAL) THEN EXIT; END;
                      i := typ.Pakets[i].RetPaket;
                    END;
                    typ.Pakets[typ.QuantityPaket].RetPaket := typ.CurrPaket;
                    INC(typ.QuantityPaket);
                  END;
                ELSE
                  err.Warning (msg.Too_many_pakets, typ.MaxPakets);
                END;
              ELSE
                err.Error(msg.Include_not_executing, Param);
              END;
            ELSE
              err.Error(msg.Incorrect_paket_name, Param);
            END;
          ELSE
            err.Error(msg.Paket_missed);
          END;
        ELSE
          err.Error(msg.DirectiveUndefined, Param);
        END;
      ELSE
        IF NOT ope.IsOperator(Param) THEN
          IF exp.CheckName(Param, TRUE) THEN
            lst.PutLabel(Param, typ.CurrPaket, typ.Pakets[typ.CurrPaket].LineNum-1);
            IF lst.Duplicate THEN err.Error(msg.Dublicate_label, Param); END;
          ELSE
            err.Error(msg.Incorrect_label);
          END;
        ELSE
          err.Error(msg.Label_equal_operator, Param);
        END;
      END;
    END;
    INC(typ.Pakets[typ.CurrPaket].LineNum);
  END;
  typ.Pakets[typ.CurrPaket].LineNum := 0;
END Label_Collect_And_Check;



(*北北北北? 傠? ム犫 癄鉅 珷お? 北北北北北北北北北北北北北北北?*)
PROCEDURE PrintStatement;
VAR
  name1: xStr.String;
  name2: xStr.txt_ptr;
BEGIN
  IF bas.CheckMode(typ.Pak) THEN
    IF typ.LastPaket <> typ.CurrPaket THEN
      txt.GetName(typ.Pakets[typ.CurrPaket].Paket, name2);
      bas.FileName(name2^, name1);
      pro.WriteMsgNo(msg.Executing_part,pro.to_screen,pro.to_file,name1);
    END;
    pro.WriteMsgNo(msg.On_line, pro.to_screen, pro.to_file, typ.Pakets[typ.CurrPaket].LineNum, Line^);
  END;
  typ.LastPaket := typ.CurrPaket;
END PrintStatement;


(* 堘キē 癄鉅 珷お? *)
PROCEDURE Debugger;
VAR
  name1  : xStr.txt_ptr;    (* 埇? 癄鉅                        *)
  name2  : xStr.String;     (* 埇? 癄鉅                        *)
  RC     : CARDINAL;       (* 姰? Б酄鉅 ㈦М ム犫?     *)
  warning: BOOLEAN;        (* 忇ě瓲? 瓲绋? 璀ㄥ 癄酄忄 *)


  (* 忇ム獱 啷瀹  ā *)
  PROCEDURE JumpByError(): BOOLEAN;
  VAR
    paket ,               (* 嵁? 癄鉅                  *)
    line  : CARDINAL;     (* 戔喈獱 ? 癄猊               *)
  BEGIN
    IF lst.GetJumpByError(RC, paket,line) THEN
      pro.WriteMsgNo(msg.JumpByError, pro.to_screen, pro.to_file, RC);
      typ.CurrPaket := paket;
      typ.Pakets[typ.CurrPaket].LineNum := line;
      RETURN TRUE;
    ELSE
      RETURN FALSE;
    END;
  END JumpByError;


BEGIN
  LOOP
    WITH typ.Pakets[typ.CurrPaket] DO
      IF LineNum > LastLine THEN; (* 呩  ⅴ犰 癄?. 庘珷お? キ? *)
        IF RetPaket # typ.CurrPaket THEN
          txt.GetName(Paket,name1);
          bas.FileName(name1^, name2);
          err.Error(msg.Not_found_RETURN, name2);
        END;
        EXIT;
      ELSE
        (* 忇ㄢ犫? ムイ? 徕喈 *)
        txt.GetLine(Paket,LineNum,Line);
        (* 懁ⅷ忪犸 瓲 岖イ. 徕喈 *)
        INC(LineNum);
        PrintStatement;
        IF ope.Execute(Line^, RC, warning) THEN
          IF RC # 0 THEN
            IF NOT JumpByError() THEN err.Error(RC); END;
          ELSIF warning THEN
            err.Warning(msg.Expected_end_param);
          END;
        ELSE
          err.Error(msg.ExpectedOperatorName);
        END;
      END;
    END;
    IF opt.Stop_Pack THEN EXIT; END;
  END;
END Debugger;


(* 戔犩? 癄猸? 珷ょí?                 *)
(* 埇? 癄鉅 ぎ ‰忪 ? Options.tst_name *)
PROCEDURE Start;
VAR
  fname: xStr.txt_ptr;
  tst_name: xStr.String;
  i: CARDINAL;
BEGIN
  (* ? 瓲徕楱?  酄‘鉅ガ ? 癄猊 *)
  opt.in_dialog := FALSE;

  (* 庘脞? 猊? 癄鉅 *)
  txt.Open(typ.Pakets[typ.CurrPaket].Paket, opt.tst_name);
  IF typ.Pakets[typ.CurrPaket].Paket <> txt.nil THEN (* 庘脞 *)
    txt.GetName(typ.Pakets[typ.CurrPaket].Paket, fname);
    xStr.Uppercase(fname^);
    bas.FileName(fname^, tst_name);
    pro.WriteMsgNo(msg.Paket, TRUE, pro.to_file, tst_name);
    INC(typ.QuantityPaket);

    (* 姤? ì噔ㄠ悭忉?, ? ì噔ㄠ泐楗． 癄鉅 *)
    (* 呩 MAX(CARDINAL) -  癄?            *)
    typ.Pakets[typ.CurrPaket].RetPaket := MAX(CARDINAL);
    LOOP
        (* 忇ムㄢ? ? 岙遴牠ㄢ? 猹?, ? 礅 ì噔ㄠ泐忉? 癄怆 *)
      Label_Collect_And_Check;
      INC(typ.CurrPaket);
      IF typ.CurrPaket = typ.QuantityPaket THEN EXIT; END;
    END;
    FOR i := 0 TO typ.QuantityPaket-1 DO
      typ.Pakets[i].RetPaket := MAX(LONGCARD);
      typ.Pakets[i].RetLineNum := txt.LastLine(typ.Pakets[i].Paket);
      IF typ.Pakets[i].RetLineNum > 0 THEN
        DEC(typ.Pakets[i].RetLineNum);
      END;
    END;
    (* 庒 (．) 癄? *)
    typ.Pakets[0].RetPaket := 0;
  END;
  IF typ.QuantityPaket > 0 THEN
    typ.CurrPaket := 0;
    (* 庒 妯: ⅴ噔ì犸, 獱  瓲ぎメ?... *)
    Debugger;
  END;
END Start;


VAR
  oldCtrlBreakHandler: brk.BreakHandler;

PROCEDURE ["C"] StopProcessingBatch (): BOOLEAN;
BEGIN
  opt.Stop_Pack := NOT opt.in_dialog;
  err.WasError := opt.Stop_Pack;
  RETURN oldCtrlBreakHandler();
END StopProcessingBatch;


BEGIN
  oldCtrlBreakHandler := brk.SetBreakHandler (StopProcessingBatch);
END Pack.

