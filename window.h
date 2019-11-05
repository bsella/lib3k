#pragma once
#include "widget.h"

class Window3k : public Widget3k{
public:
	Window3k(unsigned int w, unsigned int h, const char*, bool mouse=false, bool keyboard=false);
	virtual ~Window3k();
	
	bool run= true;
	
	void handle();
	void redraw();

protected:
	virtual void close();
};
