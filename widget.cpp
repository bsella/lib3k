#include "window.h"

Widget3k::Widget3k(unsigned int w, unsigned int h){
	width=w;
	height=h;
}

Widget3k::~Widget3k(){
}

void Widget3k::resize(){
	redraw();
}

void Widget3k::on_mouse_enter(){}
void Widget3k::on_mouse_leave(){}
void Widget3k::on_mouse_move(){}
void Widget3k::on_mouse_press(int){}
void Widget3k::on_mouse_release(int){}
void Widget3k::on_mouse_wheel(int){}

void Widget3k::add_child(Widget3k* child, int x, int y){
	pos_x= x;
	pos_y= y;
	child->win= win;
	child->gc= gc;
	children.insert(child);
	for(auto c: child->children)
		child->add_child(c, c->pos_x, c->pos_y);
}

void Widget3k::remove_child(Widget3k* child){
	auto it= children.find(child);
	if(it!= children.end())
		children.erase(it);
}

void Widget3k::draw(){}

void Widget3k::recursive_redraw(){
	draw();
	valid= true;
	for(auto c: children){
		c->recursive_redraw();
	}
}
void Widget3k::redraw(){
	recursive_redraw();
	XFlush(display3k);
}

void Widget3k::validate(){
	if(!valid){
		draw();
		valid=true;
	}
	for(auto c: children){
		c->validate();
	}
}

void Widget3k::line(int x1, int y1, int x2, int y2){
	XSetForeground(display3k, gc, WhitePixel(display3k, screen3k));
	XDrawLine(display3k, win, gc, x1, y1, x2, y2);
	valid=false;
}
