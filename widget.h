#pragma once
#include <X11/Xlib.h>

extern Display* display3k;
extern int screen3k;

class Widget3k{
public:
	inline int w(){return width;}
	inline int h(){return height;}
	
	Widget3k(unsigned int w, unsigned int h);
	virtual ~Widget3k();
	
	bool valid=false;
	void redraw();
	virtual void resize();

protected:
	Window win;
	GC gc;
	int width,height;

	virtual void on_mouse_enter();
	virtual void on_mouse_leave();
	virtual void on_mouse_move();

	virtual void on_mouse_wheel(int);

	virtual void on_mouse_press(int);
	virtual void on_mouse_release(int);
};
