#include "window.h"

Widget3k::Widget3k(int x, int y, unsigned int w, unsigned int h){
	pos_x= x;
	pos_y= y;
	width=w;
	height=h;
}
Widget3k::Widget3k(unsigned int w, unsigned int h){
	width=w;
	height=h;
}

Widget3k::~Widget3k(){
}

void Widget3k::resize(){
	redraw();
}

void Widget3k::on_mouse_enter(int,int){}
void Widget3k::on_mouse_leave(){}
void Widget3k::on_mouse_move(int,int){}
void Widget3k::on_mouse_press(int,int,int){}
void Widget3k::on_mouse_release(int,int,int){}
void Widget3k::on_mouse_wheel(int,int,int){}

void Widget3k::recursive_mouse_move(int x, int y){
	on_mouse_move(x-pos_x, y-pos_y);
	for(auto child: children)
		if(child->inside(x, y)){
			if(child->cursor_inside)
				child->recursive_mouse_move(x, y);
			else
				child->recursive_mouse_enter(x, y);
		}else if(child->cursor_inside)
			child->recursive_mouse_leave();
}
void Widget3k::recursive_mouse_enter(int x, int y){
	on_mouse_enter(x-pos_x, y-pos_y);
	cursor_inside= true;
	for(auto child: children)
		if(child->inside(x,y))
			child->recursive_mouse_enter(x, y);
}
void Widget3k::recursive_mouse_leave(){
	on_mouse_leave();
	cursor_inside= false;
	for(auto child: children)
		if(child->cursor_inside)
			child->recursive_mouse_leave();
}
void Widget3k::recursive_mouse_press(int x, int y, int button){
	on_mouse_press(x-pos_x, y-pos_y, button);
	pressed_mask|= 1 << button;
	for(auto child: children)
		if(child->inside(x,y))
			child->recursive_mouse_press(x, y, button);
}
void Widget3k::recursive_mouse_release(int x, int y, int button){
	on_mouse_release(x-pos_x, y-pos_y, button);
	pressed_mask&= ~(1 << button);
	for(auto child: children)
		if(child->pressed_mask & 1 << button)
			child->recursive_mouse_release(x, y, button);
}
void Widget3k::recursive_mouse_wheel(int x, int y, int value){
	on_mouse_wheel(x-pos_x, y-pos_y, value);
	for(auto child: children)
		if(child->inside(x,y))
			child->recursive_mouse_wheel(x, y, value);
}

void Widget3k::add_child(Widget3k* child, int x, int y){
	child->pos_x= pos_x + x;
	child->pos_y= pos_y + y;
	add_child(child);
}
void Widget3k::add_child(Widget3k* child){
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

void Widget3k::redraw(){
	draw();
	for(auto c: children)
		c->redraw();
}
bool Widget3k::inside(int x, int y)const{
	return y>pos_y && y<pos_y+height && x<pos_x+width && x>pos_x;
}

void Widget3k::color(unsigned c)const{
	XSetForeground(display3k, gc, c);
}
void Widget3k::clear()const{
	XFillRectangle(display3k, win, gc, pos_x, pos_y, width, height);
}
void Widget3k::point(int x, int y)const{
	XDrawPoint(display3k, win, gc, x, y);
}
void Widget3k::line(int x1, int y1, int x2, int y2)const{
	XDrawLine(display3k, win, gc, pos_x+x1, pos_y+y1, pos_x+x2, pos_y+y2);
}
void Widget3k::rect(int x, int y, unsigned int w, unsigned int h)const{
	XDrawRectangle(display3k, win, gc, pos_x+x, pos_y+y, w, h);
}
void Widget3k::rectf(int x, int y, unsigned int w, unsigned int h)const{
	XFillRectangle(display3k, win, gc, pos_x+x, pos_y+y, w, h);
}
void Widget3k::arc(int x, int y, unsigned int w, unsigned int h, int angle1, int angle2)const{
	XDrawArc(display3k, win, gc, pos_x+x, pos_y+y, w, h, angle1*64, angle2*64);
}
void Widget3k::arcf(int x, int y, unsigned int w, unsigned int h, int angle1, int angle2)const{
	XFillArc(display3k, win, gc, pos_x+x, pos_y+y, w, h, angle1*64, angle2*64);
}
#include <cstring>
void Widget3k::text(int x, int y, const char* text)const{
	XDrawString(display3k, win, gc, pos_x+x, pos_y+y, text, strlen(text));
}
