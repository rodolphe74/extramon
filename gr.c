#include <cmoc.h>
#include "extramgr.h"



int main()
{
	declare_window(0, 0, 319, 199);
	
	for (int i = 0; i < 200; i++) {
		pset(i, i);
	}
	
	return 0;
}
