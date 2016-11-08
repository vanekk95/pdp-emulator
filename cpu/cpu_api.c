#include "cpu_api.h"

#include <stdio.h>
#include <sys/mman.h>	// for mmap
#include <stdlib.h>	// for abort
#include <decode/decode.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


void throw_kb_interrupt(vcpu_t* vcpu, uint8_t data)
{
	SET_KB_DATA_REG(vcpu, data);	

	if (GET_KB_STAT_REG(vcpu))
	{
		printf("Keyboard interrupt is not proc yet\n Need to implement buffer\n");	// FIXME: Need to implement buffer
		abort();
	}

	SET_KB_STAT_REG(vcpu);
}


void cpu_emulation(vcpu_t* vcpu)
{
//	vcpu_t* vcpu = (vcpu_t*)malloc(sizeof(vcpu_t));

	emu_init(vcpu);	
	vcpu_print(vcpu);	
	
	exec_status_t exec_st = EXEC_SUCCESS;
	
	while (1)
	{
		if (is_break(vcpu, vcpu->regs[PC]))
			SET_STOP_FLAG(vcpu);

		if (!vcpu->stop_flag || vcpu->step_flag)
		{
			if (vcpu->stop_flag)			
				RESET_STEP_FLAG(vcpu);	

			exec_st = cpu_exec(vcpu);			
			vcpu_print(vcpu);
			
			if (exec_st == EXEC_UNDEFINED)
				break;	
		}
	}
}

void stop_emulator(vcpu_t* vcpu)
{
	vcpu->stop_flag = 1;
}

void set_step_flag(vcpu_t* vcpu)
{
	vcpu->step_flag = 1;
}

void set_breakpoint(vcpu_t* vcpu, uint16_t address)		// FIXME: Need to check
{
	int set = address / 8;
	int disp = address % 8;
	vcpu->br_points[set] |= (0x01 << (8 - disp)); 
}

void remove_breakpoint(vcpu_t* vcpu, uint16_t address)
{
	int set = address / 8;
	int disp = address % 8;
	vcpu->br_points[set] &= (0xff ^ (0x1 << (8 - disp)));	
}

uint16_t get_register(vcpu_t* vcpu, uint8_t num)
{
	return GET_CPU_REG(vcpu, num);
}