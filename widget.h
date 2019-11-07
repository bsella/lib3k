#pragma once
#include <X11/Xlib.h>
#include <unordered_set>

extern Display* display3k;
extern int screen3k;

class Widget3k{
	int pos_x, pos_y;
	void recursive_redraw();
public:
	inline int w(){return width;}
	inline int h(){return height;}
	
	Widget3k(unsigned int w, unsigned int h);
	virtual ~Widget3k();
	
	bool valid=false;
	void draw();
	void redraw();
	void validate();
	virtual void resize();
	
	void add_child(Widget3k*, int, int);
	void remove_child(Widget3k*);

	void line(int, int, int, int);

protected:
	Window win;
	GC gc;
	std::unordered_set<Widget3k*> children;
	int width,height;

	virtual void on_mouse_enter();
	virtual void on_mouse_leave();
	virtual void on_mouse_move();

	virtual void on_mouse_wheel(int);

	virtual void on_mouse_press(int);
	virtual void on_mouse_release(int);
};
