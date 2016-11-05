#include <stdio.h>
#include "cpu/cpu.h"
#include <stdlib.h>	// for malloc
#include <string.h>

/* TODO:
	Implement sp addressing
	Check byte operations
*/

int main()
{
	cpu_emulation(&vcpu);	

	return 0;
}