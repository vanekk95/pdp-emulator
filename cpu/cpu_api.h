#ifndef CPU_API_H
#define CPU_API_H

#include "cpu.h"

#ifdef __cplusplus
	extern "C" {
#endif

	void throw_kb_interrupt(vcpu_t* vcpu, uint8_t data);
	void cpu_emulation(vcpu_t* vcpu);
	void stop_emulator(vcpu_t* vcpu);
	void set_step_flag(vcpu_t* vcpu);
	void set_breakpoint(vcpu_t* vcpu, uint16_t address);
	void remove_breakpoint(vcpu_t* vcpu, uint16_t address);
	uint16_t get_register(vcpu_t* vcpu, uint8_t num);
	
#ifdef __cplusplus
}
#endif




#endif // CPU_API_H