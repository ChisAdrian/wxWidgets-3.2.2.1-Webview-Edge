# wxWidgets-3.2.2.1-Webview-Edge
CodeBlocks wxWidgets-3.2.2.1-Webview-Edge

Compiler MingwDistrox64_GCC 9.2.0_Boost 1.71.0

In wxWidgets-3.2.2.1\include\wx\msw\setup.h
change to 1
#define wxUSE_WEBVIEW_EDGE 1

Compile wxWidgtes with mingw32-make SHELL=CMD.exe -j4 -f makefile.gcc BUILD=release SHARED=0 MONOLITHIC=1 UNICODE=1

put WebView2Loader.dll in project folder

Create wxWidgets projects in codebloks and file in code....
