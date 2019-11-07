#include "window.h"

Display* display3k;
int screen3k;

static unsigned int windows_count=0;

static XEvent event;
static Atom wmDelete;

#include <iostream>
Window3k::Window3k(unsigned int w, unsigned int h, const char*, bool mouse, bool keyboard): Widget3k(w,h){
	if(!windows_count){
		display3k= XOpenDisplay(0);
		screen3k= DefaultScreen(display3k);
		wmDelete= XInternAtom(display3k, "WM_DELETE_WINDOW", false);
	}
	windows_count++;
	unsigned long black= BlackPixel(display3k, screen3k);
	win= XCreateSimpleWindow(display3k, DefaultRootWindow(display3k), 0,0, w,h, 0, black, black);
	//XSetStandardProperties(display3k,win, title, "Test", None,nullptr,0,nullptr);
	long masks= StructureNotifyMask;
	if(mouse)
		masks|= ButtonPressMask
			| ButtonReleaseMask
			| ButtonMotionMask
			| EnterWindowMask
			| LeaveWindowMask
			| PointerMotionMask;
	if(keyboard)
		masks|= KeyPressMask
			| KeyReleaseMask;
	XSelectInput(display3k, win, masks);
 	XMapWindow(display3k, win);

	gc=XCreateGC(display3k, win, 0,0);
	XSetForeground(display3k, gc, black);

	XSetWMProtocols(display3k, win, &wmDelete, 1);

	for(;;){
		XNextEvent(display3k, &event);
		if(event.type==MapNotify) break;
	}
	validate();
	XFlush(display3k);
}

Window3k::~Window3k(){
	XFreeGC(display3k, gc);
	XDestroyWindow(display3k, win);
	windows_count--;
	if(!windows_count)
		XCloseDisplay(display3k);
}

void Window3k::handle(){
	XNextEvent(display3k, &event);
	switch(event.type){
		case ClientMessage:
			if(static_cast<Atom>(event.xclient.data.l[0])==wmDelete)
				close();
			break;
		case ConfigureNotify:
			if(event.xconfigure.width!=width || event.xconfigure.height!=height){
				width=event.xconfigure.width;
				height=event.xconfigure.height;
				resize();
			}
			break;
		case EnterNotify:
			on_mouse_enter();
			break;
		case LeaveNotify:
			on_mouse_leave();
			break;
		case MotionNotify:
			on_mouse_move();
			break;
		case ButtonPress:
			if(event.xbutton.button < Button4)
				on_mouse_press(event.xbutton.button);
			else
				on_mouse_wheel(event.xbutton.button-4);
			break;
		case ButtonRelease:
			if(event.xbutton.button < Button4)
				on_mouse_release(event.xbutton.button);
			break;
		default:
			std::cout << event.type << std::endl;
			break;
	}
	if(!valid){
		validate();
		XFlush(display3k);
	}
}

void Window3k::close(){
	run= false;
}
