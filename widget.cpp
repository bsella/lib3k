#include "window.h"

Widget3k::Widget3k(unsigned int w, unsigned int h){
	width=w;
	height=h;
}

Widget3k::~Widget3k(){
}

void Widget3k::redraw(){
	valid= true;
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
