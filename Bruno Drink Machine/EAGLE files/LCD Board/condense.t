setscreen ("text")

const MAX_LINE := 90

var InLine, OutLine : string := ""
var InFile, OutFile : int

open :InFile, "mill.txt", get
open :OutFile, "mill cond.txt", put
loop
    exit when eof(InFile)
    get :InFile, InLine:*
%    InLine := InLine(1..*-1) % remove CR (or LF)

    if length(InLine) + length(OutLine)+1 <= MAX_LINE-2 then %fit comma CR/LF?
	OutLine := OutLine + ";" + InLine
    else
	put :OutFile, OutLine + "\n"
	OutLine := InLine
    end if
end loop
if eof(InFile) and OutLine not="" then
    put :OutFile, OutLine + "\n"
end if

close :InFile
close :OutFile
