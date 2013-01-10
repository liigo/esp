echo off
echo: Do not make mistakes, do not delete the source code files! :)
echo: 清理无用文件，瘦身

@del /s /q .\debug
@del /s /q .\release
@del    /q .\*.ncb
@del    /q .\*.opt
@del    /q .\*.suo
@del    /q .\*.plg

@del /s /q .\esp-apache\debug
@del /s /q .\esp-apache\release
@del    /q .\esp-apache\*.plg

@del /s /q .\esp-core\debug
@del /s /q .\esp-core\release
@del    /q .\esp-core\*.plg

@del /s /q .\esp-e\debug
@del /s /q .\esp-e\release
@del    /q .\esp-e\*.plg

@del /s /q .\esp-iis\debug
@del /s /q .\esp-iis\release
@del    /q .\esp-iis\*.plg

@del /s /q .\esp-lighttpd\debug
@del /s /q .\esp-lighttpd\release
@del    /q .\esp-lighttpd\*.plg

@del /s /q .\esp-nginx\debug
@del /s /q .\esp-nginx\release
@del    /q .\esp-nginx\*.plg

@del    /q .\lib\esp-core.lib
@del    /q .\lib\esp-core-debug.lib

@del /s /q .\test\debug
@del /s /q .\test\release
@del    /q .\test\*.plg

@del /s /q .\other\html-parser\test\debug
@del /s /q .\other\html-parser\test\release
@del    /q .\other\html-parser\test\*.plg
@del    /q .\other\html-parser\test\*.ncb
@del    /q .\other\html-parser\test\*.opt
@del    /q .\other\html-parser\test\*.suo
