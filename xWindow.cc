#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "xWindow.h"

using namespace std;

struct XWindowImpl {
    Display *d;
    Window w;
    int s;
    GC gc;
    unsigned long colours[10];
};

Xwindow::Xwindow(int width, int height): pImpl{new XWindowImpl} {

  pImpl->d = XOpenDisplay(NULL);
  if (pImpl->d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  pImpl->s = DefaultScreen(pImpl->d);
  pImpl->w = XCreateSimpleWindow(pImpl->d, RootWindow(pImpl->d, pImpl->s), 10, 10, width, height, 1,
                          BlackPixel(pImpl->d, pImpl->s), WhitePixel(pImpl->d, pImpl->s));
  XSelectInput(pImpl->d, pImpl->w, ExposureMask | KeyPressMask);
  XMapRaised(pImpl->d, pImpl->w);

  Pixmap pix = XCreatePixmap(pImpl->d,pImpl->w,width,
        height,DefaultDepth(pImpl->d,DefaultScreen(pImpl->d)));
  pImpl->gc = XCreateGC(pImpl->d, pix, 0,(XGCValues *)0);

  XFlush(pImpl->d);
  XFlush(pImpl->d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[10][10]={"white", "black", "red", "green", "blue", "cyan", "yellow", "magenta", "orange", "brown"};

  cmap=DefaultColormap(pImpl->d,DefaultScreen(pImpl->d));
  for(int i=0; i < 10; ++i) {
      XParseColor(pImpl->d,cmap,color_vals[i],&xcolour);
      XAllocColor(pImpl->d,cmap,&xcolour);
      pImpl->colours[i]=xcolour.pixel;
  }

  XSetForeground(pImpl->d,pImpl->gc,pImpl->colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(pImpl->d, pImpl->w, &hints);

  XSynchronize(pImpl->d,True);

  usleep(1000);

  // Make sure we don't race against the Window being shown
  XEvent ev;
  while(1) {
    XNextEvent(pImpl->d, &ev);
    if(ev.type == Expose) break;
  }
}

Xwindow::~Xwindow() {
  XFreeGC(pImpl->d, pImpl->gc);
  XCloseDisplay(pImpl->d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(pImpl->d, pImpl->gc, pImpl->colours[colour]);
  XFillRectangle(pImpl->d, pImpl->w, pImpl->gc, x, y, width, height);
  XSetForeground(pImpl->d, pImpl->gc, pImpl->colours[Black]);
}

void Xwindow::drawString(int x, int y, string msg) {
  XDrawString(pImpl->d, pImpl->w, DefaultGC(pImpl->d, pImpl->s), x, y, msg.c_str(), msg.length());
}
