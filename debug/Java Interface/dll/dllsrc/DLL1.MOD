
IMPLEMENTATION MODULE dll1;
FROM  WholeStr IMPORT CardToStr;
FROM  Printf   IMPORT sprintf;

VAR count: CARDINAL;
    n    : CARDINAL;
-- ???????? ⥪?饥 ?६? ? ??ᯮ??
PROCEDURE ["StdCall"] RegisterWindow(VAR p:PASSPORT);
BEGIN
   p.time := count;
   INC(count);
END RegisterWindow;

-- ?뤠?? ???砩?? ??????஥ ???????⢮ ID  - ?? 0 ?? 10 ????
PROCEDURE ["StdCall"] IterId(p-: PASSPORT; VAR id: CARDINAL): CARDINAL;
BEGIN
  IF n <= 100 THEN
 --   id := p.time + n;
      id := n;
    RETURN 1;
  ELSE
    RETURN 0;
  END;
END IterId;


-- ?? ID ?뤠?? ??????? - 楫?? ??᫮
PROCEDURE ["StdCall"] IterData1 (p-: PASSPORT; id: CARDINAL; VAR str: STRING);
BEGIN
  CardToStr( id, str);
END IterData1;


-- ?? ID ?뤠?? ??????? - 楫?? ??᫮ ? 16 ?/?
PROCEDURE ["StdCall"] IterData2 (p-: PASSPORT; id: CARDINAL; VAR str: STRING);
BEGIN
   sprintf(str, "%o",id);
END IterData2;

BEGIN
 count := 0;
 n     := 10;
END dll1.