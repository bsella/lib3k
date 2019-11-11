#pragma once
#include <X11/Xlib.h>
#include <unordered_set>

extern Display* display3k;
extern int screen3k;

class Widget3k{
	bool cursor_inside= false;
	unsigned int pressed_mask=0;
public:
	inline int w(){return width;}
	inline int h(){return height;}
	
	Widget3k(int x, int y, unsigned int w, unsigned int h);
	Widget3k(unsigned int w, unsigned int h);
	virtual ~Widget3k();
	
	virtual void draw();
	void redraw();
	virtual void resize();
	
	void add_child(Widget3k*);
	void add_child(Widget3k*, int, int);
	void remove_child(Widget3k*);

	void color(unsigned)const;
	void clear()const;
	void point(int, int)const;
	void line(int, int, int, int)const;
	void rect(int, int, unsigned, unsigned)const;
	void rectf(int, int, unsigned, unsigned)const;
	void arc(int, int, unsigned, unsigned, int, int)const;
	void arcf(int, int, unsigned, unsigned, int, int)const;
	void text(int, int, const char*)const;

protected:
	Window win;
	GC gc;
	std::unordered_set<Widget3k*> children;
	int pos_x, pos_y;
	int width,height;

	virtual bool inside(int, int)const;

	virtual void on_mouse_enter(int,int);
	virtual void on_mouse_leave();
	virtual void on_mouse_move(int,int);
	virtual void on_mouse_wheel(int,int,int);
	virtual void on_mouse_press(int,int,int);
	virtual void on_mouse_release(int,int,int);

	void recursive_mouse_enter(int,int);
	void recursive_mouse_leave();
	void recursive_mouse_move(int,int);
	void recursive_mouse_wheel(int,int,int);
	void recursive_mouse_press(int,int,int);
	void recursive_mouse_release(int,int,int);
};
