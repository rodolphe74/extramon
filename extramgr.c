#include "extramgr.h"

void declare_window(int x0, int y0, int x1, int y1)
{
	asm {
	LDB #GR_RESETW
	JSR GR_EXTRA
	LDX :x0
	STX XL
	LDX :y0
	STX YB
	LDX :x1
	STX XR
	LDX :y1
	STX YT
	}
}

void pset(int x, int y)
{
	asm {
	LDX :x
	LDY :y
	LDB #PSETXY
	JSR GR_EXTRA
	}
}

void line(int x0, int y0, int x1, int y1)
{
	asm {
	LDX :x0
	LDY :y0
	STX XXXX
	STY YYYY
	LDX :x1
	LDY :y1
	LDB #LINE
	JSR GR_EXTRA
	}
}
