#include "cpu.h"
#include <stdio.h>
#include <sys/mman.h>	// for mmap
#include <stdlib.h>	// for abort
#include <decode/decode.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>



uint8_t exec_array[] = 
{
	0b01000000, 0b00011100, 0b00001010, 0b00000000,
	0b10000000, 0b10001100, 0b00000001, 0b00000001, 
	0b01111111, 0b01111111, 0b10010001, 0b10000000,
	0b01111111, 0b01111111, 0b01111111, 0b01111111,
	0b01111111, 0b01111111, 0b01111111, 0b01111111, 
	0b00000011, 0b00000000, 0b01111111, 0b01111111
};
// 	0b00000100, 0b01100100, 0b01111111, 0b01111111,


int read_file(char* path, void* mem)
{
/*
	int fd = open(path, O_RDWR);

	if (fd == -1)
	{	
		printf("Can not open file \n");
		abort();
	}

	long long size = lseek(fd, 0, SEEK_END);

	printf("number of rom bytes: %lld\n", size);
*/

	int size = sizeof(exec_array);

	printf("array size: %d\n", size);

	memcpy(mem, exec_array, size);

	int i = 0;

	for (i = 0; i < size; i++)
	{
		printf("mem: 0x%x\n", ((uint8_t*)mem)[i]);

	}

/*
	char* buf = (uint8_t*)malloc(sizeof(char) * size);
	memset(buf, 0, size);

	int rd = read(fd, buf, size);

	if (rd == -1)
	{
		printf("Read error \n");
		abort();
	}

	memcpy(mem, buf, size);

	printf("mem: 0x%x\n", *((uint16_t*)mem));

	free(buf);
*/
	return 0;
}

void interrupt_handler(vcpu_t* vcpu)
{
	*(uint16_t*)((uint8_t*)vcpu->mem_entry + vcpu->regs[SP]) = (*(vcpu->psw)).reg_val; 
	vcpu->regs[SP] -= 2;
	*(uint16_t*)((uint8_t*)vcpu->mem_entry + vcpu->regs[SP]) = vcpu->regs[PC];	
	vcpu->regs[SP] -= 2;

	vcpu->regs[PC] = *(uint16_t*)((uint8_t*)vcpu->mem_entry + KB_INTERRUPT_VEC);
	(*(vcpu->psw)).reg_val = *(uint16_t*)((uint8_t*)vcpu->mem_entry + KB_INTERRUPT_VEC + 2);	
}

int vcpu_init(vcpu_t* vcpu, void* mem)
{
	printf("vcpu init\n");	
	vcpu->mem_entry = mem;
	vcpu->regs = (uint16_t*)((uint8_t*)mem + MEM_SPACE_SIZE);

	vcpu->regs[PC] = 0x0000;
//	vcpu->regs[SP];			// FIXME: Need to deal with it 

	vcpu->psw = (uint16_t*)((uint8_t*)mem + PS_ADDR);
	vcpu->br_points = (uint8_t*)((uint8_t*)mem + BR_POINT_ADDR);
	vcpu->kb_stat_reg = (uint16_t*)((uint8_t*)mem + KB_STAT_REG);
	vcpu->kb_data_reg = (uint16_t*)((uint8_t*)mem + KB_DATA_REG);

	PS_INIT(vcpu);

	vcpu->stop_flag = 0;
	vcpu->step_flag = 0;

	// FIXME: if to write LOAD_N() here 
	// SEGMENTATION FAULT WILL OCCUR						

	read_file("rom_file.txt", vcpu->mem_entry);

	return 0;
}

int emu_init(vcpu_t* vcpu)
{
	void* mem_entry = mmap(NULL, ADDR_SPACE_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0); 

	if (mem_entry == (void*)-1)
	{
		printf("Mem allocation failed (mmap)\n");
		abort();
	}

	vcpu_init(vcpu, mem_entry);

	return 0;
}

uint16_t fetch_instr(vcpu_t* vcpu)
{
	printf("Instruction fetch \n");
		
	uint16_t op = 0;

	if (GET_KB_STAT_REG(vcpu))
	{
		printf("Keyboard interrupt was caught\n");
		printf("Previous PC: 0x%llx\n", vcpu->regs[PC]);
		interrupt_handler(vcpu);	
		printf("PC switched to: 0x%llx\n", vcpu->regs[PC]);
	}
	else
	{
		printf("PC: 0x%llx\n", vcpu->regs[PC]);
	}

	memcpy(&op, (uint8_t*)(vcpu->mem_entry) + vcpu->regs[PC], sizeof(uint8_t) * 2);
	printf("op: 0x%x\n", op);

	vcpu->regs[PC] += 2;

	return op;
}

void vcpu_print(vcpu_t* vcpu)
{
	printf("REG 0: 0x%x\n", vcpu->regs[REG0]);
	printf("REG 1: 0x%x\n", vcpu->regs[REG1]);
	printf("REG 2: 0x%x\n", vcpu->regs[REG2]);
	printf("REG 3: 0x%x\n", vcpu->regs[REG3]);
	printf("REG 4: 0x%x\n", vcpu->regs[REG4]);
	printf("REG 5: 0x%x\n", vcpu->regs[REG5]);
	printf("REG 6: 0x%x\n", vcpu->regs[SP]);
	printf("REG 7: 0x%x\n", vcpu->regs[PC]);						
}

int is_break(vcpu_t* vcpu, uint16_t address)		 // FIXME: Need to check 
{
	int set = address / 8;
	int disp = address % 8;
	uint8_t mask = vcpu->br_points[set];
	
	mask &= (0x01 << (8 - disp));
	mask = (mask >> (8 - disp)); //

	if (mask)
	{	
		printf("Breakpoint was set at address: 0x%x\n", address);
	}

	return mask;
}

exec_status_t cpu_exec(vcpu_t* vcpu)
{
	instr_t op = fetch_instr(vcpu);

	instr_desc_t* instr;
	lookup_table(op, &instr);

	if (instr == NULL)				// FIXME: Need to deal with it properly
		return EXEC_UNDEFINED;
		

	exec_status_t st = instr->execute(vcpu, instr, op);

	return st;
}






