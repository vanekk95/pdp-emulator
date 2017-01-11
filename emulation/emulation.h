#ifndef EMULATION_H
#define EMULATION_H

#include "decode/decode.h"
#include "cpu/cpu.h"

/* double operand */

emu_stat_t mov_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t movb_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);

emu_stat_t add_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t sub_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);


/* single operand */

emu_stat_t clr_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t com_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t inc_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t dec_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t neg_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t tst_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t asr_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t asl_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t ror_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t rol_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t swab_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);


/* branches */

emu_stat_t br_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t bne_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t beq_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t bpl_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t bmi_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t bvc_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t bvs_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t bcc_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t bcs_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t bge_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t blt_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t bgt_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t ble_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t bhi_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t blos_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t bhis_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t blo_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t jmp_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);


/* subroutine and instr_mode_terrupts */

emu_stat_t rti_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t jsr_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
emu_stat_t rts_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);

/* miscellaneous */

emu_stat_t halt_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);

#endif //EMULATION_H