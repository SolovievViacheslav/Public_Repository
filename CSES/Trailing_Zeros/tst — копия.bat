

@echo off
set PATH=%PATH%;"C:\Program Files\Beyond Compare 4"
set n=%1%
echo START %TIME:~6,2%
a.exe  < "test_input (%n%).txt" >"user_out (%n%).txt"
echo END %TIME:~6,2%

rem bcomp.exe "user_out (%n%).txt" "test_output (%n%).txt"
cmp.exe "user_out (%n%).txt" "test_output (%n%).txt" 
if errorlevel 1 (
	bcomp.exe "user_out (%n%).txt" "test_output (%n%).txt"
)
