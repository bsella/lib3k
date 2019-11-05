#include <unistd.h>
#include "window.h"

int main(){
	Window3k win(400, 300, "Hellow World", true);
	while(win.run)
		win.handle();
	return 0;
}
