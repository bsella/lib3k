#include <unistd.h>
#include "window.h"

int main(){
	Window3k win(400, 300, "Hellow World", true);
	win.line(10,20,30,40);
	while(win.run)
		win.handle();
	return 0;
}
