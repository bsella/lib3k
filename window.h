#pragma once
#include <X11/Xlib.h>

extern Display* display3k;
extern int screen3k;

class Window3k{
	Window win;
	GC gc;
	int width,height;
public:
	inline int w(){return width;}
	inline int h(){return height;}
	bool run= true;
	
	Window3k(unsigned int w, unsigned int h, const char*, bool mouse=false, bool keyboard=false);
	virtual ~Window3k();
	
	void handle();

	virtual bool close();
	virtual void resize();

	virtual void on_mouse_enter();
	virtual void on_mouse_leave();
	virtual void on_mouse_move();

	virtual void on_mouse_press(int);
	virtual void on_mouse_release(int);
};
