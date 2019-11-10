#include <unistd.h>
#include "window.h"

#include <iostream>
class TestWidget : public Widget3k{
	void draw()override{
		line(0,0,width,0);
		line(0,0,0,height);
		line(width,height,width,0);
		line(width,height,0,height);
	}
	void on_mouse_enter(int, int){
		std::cout << "enter" << std::endl;
	}
	void on_mouse_move(int x, int y){
		line(0,0, x, y);
	}
	void on_mouse_leave(){
		std::cout << "leave" << std::endl;
	}
	void on_mouse_press(int,int,int){
		std::cout << "press" << std::endl;
	}
	void on_mouse_release(int,int,int){
		std::cout << "release" << std::endl;
	}
public:
	TestWidget(int w, int h):Widget3k(w,h){}
};

int main(){
	Window3k win(400, 300, "Hellow World", true);
	TestWidget test(200,150);
	win.add_child(&test, 20, 30);
	win.redraw();

	while(win.run) win.handle();
	return 0;
}
