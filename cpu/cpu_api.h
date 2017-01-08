#ifndef CPU_API_H
#define CPU_API_H

#include "cpu.h"

#ifdef __cplusplus
	extern "C" {
#endif

	int emulator_initialized;
	int emulator_halted;

	void throw_kb_interrupt(vcpu_t* vcpu, uint8_t data);
	int cpu_emulation(vcpu_t** vcpu, char* path);
	void halt_emulator(vcpu_t* vcpu);	
	void stop_emulator(vcpu_t* vcpu);
	void step_emulator(vcpu_t* vcpu);
	void run_emulator(vcpu_t* vcpu);
	void reset_emulator(vcpu_t* vcpu);
	void set_breakpoint(vcpu_t* vcpu, uint16_t address);
	void remove_breakpoint(vcpu_t* vcpu, uint16_t address);
	uint16_t get_register(vcpu_t* vcpu, uint8_t num);
	uint8_t get_nflag(vcpu_t* vcpu);
	uint8_t get_cflag(vcpu_t* vcpu);
	uint8_t get_vflag(vcpu_t* vcpu);
	uint8_t get_zflag(vcpu_t* vcpu);

#ifdef __cplusplus
}
#endif




#endif // CPU_API_H