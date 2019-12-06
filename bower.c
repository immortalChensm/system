//
// Created by 1655664358@qq.com on 2019/12/5.
//

#define WEBVIEW_IMPLEMENTATION
#include "webview.h"

#ifdef WIN32
int WINAPI WinMain(HINSTANCE hInt, HINSTANCE hPrevInst, LPSTR lpCmdLine,
int nCmdShow) {
#else
int main() {
#endif
/* Open wikipedia in a 800x600 resizable window */
webview("Minimal webview example",
"http://www.999999.live", 800, 600, 1);
return 0;
}
