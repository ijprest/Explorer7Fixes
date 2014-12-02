set foo=explorer7fixes.dll
reg query hkcr\appid\%foo%
if errorlevel 1 (regsvr32 /s %foo%) else (regsvr32 /s /u %foo%)
taskkill /f /im explorer.exe
start explorer.exe
timeout 1
start %cd%
