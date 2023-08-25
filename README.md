# wxWidgets-3.2.2.1-Webview-Edge
CodeBlocks wxWidgets-3.2.2.1-Webview-Edge
wxWidgets-3.2.2.1\include\wx\msw\setup.h
change to 1
// Use the Edge (Chromium) wxWebView backend (Requires WebView2 SDK)
//
// Default is 0 because WebView2 is not always available, set it to 1 if you do have it.
//
// Recommended setting: 1 when building for Windows with WebView2 SDK
#define wxUSE_WEBVIEW_EDGE 1
Compile wxWidgtes with mingw32-make SHELL=CMD.exe -j4 -f makefile.gcc BUILD=release SHARED=0 MONOLITHIC=1 UNICODE=1
put WebView2Loader.dll in project folder
Create wxWidgets projects in codebloks and file in code....
