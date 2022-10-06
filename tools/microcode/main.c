#include <cpu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	uint32_t microcode[MAX_INSTR * MAX_MICROCODE_STEP] = { 0 };

	microcode[INSTR_NOP << 3 | MICROCODE_STEP_0] = FINISH;

	microcode[INSTR_MOV << 3 | MICROCODE_STEP_0] = PUT_IR1_DB | SAVE_DB_IR0;
	microcode[INSTR_MOV << 3 | MICROCODE_STEP_1] = FINISH;

	microcode[INSTR_LOD << 3 | MICROCODE_STEP_0] = PUT_IIMM_DB | SAVE_DB_IR0;
	microcode[INSTR_LOD << 3 | MICROCODE_STEP_1] = FINISH;

	microcode[INSTR_OUT << 3 | MICROCODE_STEP_0] = PUT_A_ADDR | PUT_IR0_DB | IO_OUT;
	microcode[INSTR_OUT << 3 | MICROCODE_STEP_1] = FINISH;

	microcode[INSTR_INP << 3 | MICROCODE_STEP_0] = PUT_A_ADDR | SAVE_DB_IR0 | IO_IN;
	microcode[INSTR_INP << 3 | MICROCODE_STEP_1] = FINISH;

	microcode[INSTR_JNZA << 3 | MICROCODE_STEP_0] = PUT_A_ADDR | COND_INVERT | SAVE_PCB_IF_Z;
	microcode[INSTR_JNZA << 3 | MICROCODE_STEP_1] = PC_FLUSH_COND;
	microcode[INSTR_JNZA << 3 | MICROCODE_STEP_2] = FINISH;

	microcode[INSTR_ADD << 3 | MICROCODE_STEP_0] = PUT_IR0_DB | SAVE_DB_ALUA;
	microcode[INSTR_ADD << 3 | MICROCODE_STEP_1] = PUT_IR1_DB | SAVE_DB_ALUB;
	microcode[INSTR_ADD << 3 | MICROCODE_STEP_2] = ALU_ADD;
	microcode[INSTR_ADD << 3 | MICROCODE_STEP_3] = PUT_ALUOUT_DB | SAVE_DB_IR0;
	microcode[INSTR_ADD << 3 | MICROCODE_STEP_4] = FINISH;

	microcode[INSTR_ADDI << 3 | MICROCODE_STEP_0] = PUT_IR0_DB | SAVE_DB_ALUA;
	microcode[INSTR_ADDI << 3 | MICROCODE_STEP_1] = PUT_IIMM_DB | SAVE_DB_ALUB;
	microcode[INSTR_ADDI << 3 | MICROCODE_STEP_2] = ALU_ADD;
	microcode[INSTR_ADDI << 3 | MICROCODE_STEP_3] = PUT_ALUOUT_DB | SAVE_DB_IR0;
	microcode[INSTR_ADDI << 3 | MICROCODE_STEP_4] = FINISH;

	microcode[INSTR_SUB << 3 | MICROCODE_STEP_0] = PUT_IR0_DB | SAVE_DB_ALUA;
	microcode[INSTR_SUB << 3 | MICROCODE_STEP_1] = PUT_IR1_DB | SAVE_DB_ALUB;
	microcode[INSTR_SUB << 3 | MICROCODE_STEP_2] = ALU_SUB;
	microcode[INSTR_SUB << 3 | MICROCODE_STEP_3] = PUT_ALUOUT_DB | SAVE_DB_IR0;
	microcode[INSTR_SUB << 3 | MICROCODE_STEP_4] = FINISH;

	microcode[INSTR_SUBI << 3 | MICROCODE_STEP_0] = PUT_IR0_DB | SAVE_DB_ALUA;
	microcode[INSTR_SUBI << 3 | MICROCODE_STEP_1] = PUT_IIMM_DB | SAVE_DB_ALUB;
	microcode[INSTR_SUBI << 3 | MICROCODE_STEP_2] = ALU_SUB;
	microcode[INSTR_SUBI << 3 | MICROCODE_STEP_3] = PUT_ALUOUT_DB | SAVE_DB_IR0;
	microcode[INSTR_SUBI << 3 | MICROCODE_STEP_4] = FINISH;

	microcode[INSTR_NAD << 3 | MICROCODE_STEP_0] = PUT_IR0_DB | SAVE_DB_ALUA;
	microcode[INSTR_NAD << 3 | MICROCODE_STEP_1] = PUT_IR1_DB | SAVE_DB_ALUB;
	microcode[INSTR_NAD << 3 | MICROCODE_STEP_2] = ALU_NAND;
	microcode[INSTR_NAD << 3 | MICROCODE_STEP_3] = PUT_ALUOUT_DB | SAVE_DB_IR0;
	microcode[INSTR_NAD << 3 | MICROCODE_STEP_4] = FINISH;

	microcode[INSTR_NADI << 3 | MICROCODE_STEP_0] = PUT_IR0_DB | SAVE_DB_ALUA;
	microcode[INSTR_NADI << 3 | MICROCODE_STEP_1] = PUT_IIMM_DB | SAVE_DB_ALUB;
	microcode[INSTR_NADI << 3 | MICROCODE_STEP_2] = ALU_SUB;
	microcode[INSTR_NADI << 3 | MICROCODE_STEP_3] = PUT_ALUOUT_DB | SAVE_DB_IR0;
	microcode[INSTR_NADI << 3 | MICROCODE_STEP_4] = FINISH;

	microcode[INSTR_NOR << 3 | MICROCODE_STEP_0] = PUT_IR0_DB | SAVE_DB_ALUA;
	microcode[INSTR_NOR << 3 | MICROCODE_STEP_1] = PUT_IR1_DB | SAVE_DB_ALUB;
	microcode[INSTR_NOR << 3 | MICROCODE_STEP_2] = ALU_NOR;
	microcode[INSTR_NOR << 3 | MICROCODE_STEP_3] = PUT_ALUOUT_DB | SAVE_DB_IR0;
	microcode[INSTR_NOR << 3 | MICROCODE_STEP_4] = FINISH;

	microcode[INSTR_NORI << 3 | MICROCODE_STEP_0] = PUT_IR0_DB | SAVE_DB_ALUA;
	microcode[INSTR_NORI << 3 | MICROCODE_STEP_1] = PUT_IIMM_DB | SAVE_DB_ALUB;
	microcode[INSTR_NORI << 3 | MICROCODE_STEP_2] = ALU_NOR;
	microcode[INSTR_NORI << 3 | MICROCODE_STEP_3] = PUT_ALUOUT_DB | SAVE_DB_IR0;
	microcode[INSTR_NORI << 3 | MICROCODE_STEP_4] = FINISH;

	microcode[INSTR_CMP << 3 | MICROCODE_STEP_0] = PUT_IR0_DB | SAVE_DB_ALUA;
	microcode[INSTR_CMP << 3 | MICROCODE_STEP_1] = PUT_IR1_DB | SAVE_DB_ALUB;
	microcode[INSTR_CMP << 3 | MICROCODE_STEP_2] = ALU_CMP;
	microcode[INSTR_CMP << 3 | MICROCODE_STEP_3] = FINISH;

	microcode[INSTR_CMPI << 3 | MICROCODE_STEP_0] = PUT_IR0_DB | SAVE_DB_ALUA;
	microcode[INSTR_CMPI << 3 | MICROCODE_STEP_1] = PUT_IIMM_DB | SAVE_DB_ALUB;
	microcode[INSTR_CMPI << 3 | MICROCODE_STEP_2] = ALU_CMP;
	microcode[INSTR_CMPI << 3 | MICROCODE_STEP_3] = FINISH;

	microcode[INSTR_JMPA << 3 | MICROCODE_STEP_0] = PUT_A_ADDR | SAVE_PCB;
	microcode[INSTR_JMPA << 3 | MICROCODE_STEP_1] = PC_FLUSH;
	microcode[INSTR_JMPA << 3 | MICROCODE_STEP_3] = FINISH;

	microcode[INSTR_JZRA << 3 | MICROCODE_STEP_0] = PUT_A_ADDR | SAVE_PCB_IF_Z;
	microcode[INSTR_JZRA << 3 | MICROCODE_STEP_1] = PC_FLUSH_COND;
	microcode[INSTR_JZRA << 3 | MICROCODE_STEP_2] = FINISH;

	microcode[INSTR_LDRA << 3 | MICROCODE_STEP_0] = PUT_A_ADDR | SAVE_DB_IR0 | PUT_MEM_DB;
	microcode[INSTR_LDRA << 3 | MICROCODE_STEP_1] = FINISH;

	microcode[INSTR_WTRA << 3 | MICROCODE_STEP_0] = PUT_A_ADDR | SAVE_DB_MEM | PUT_IR0_DB;
	microcode[INSTR_WTRA << 3 | MICROCODE_STEP_1] = FINISH;

	microcode[INSTR_JEQA << 3 | MICROCODE_STEP_0] = PUT_A_ADDR | SAVE_PCB_IF_EQ;
	microcode[INSTR_JEQA << 3 | MICROCODE_STEP_1] = PC_FLUSH_COND;
	microcode[INSTR_JEQA << 3 | MICROCODE_STEP_2] = FINISH;

	microcode[INSTR_JNQA << 3 | MICROCODE_STEP_0] = PUT_A_ADDR | COND_INVERT | SAVE_PCB_IF_EQ;
	microcode[INSTR_JNQA << 3 | MICROCODE_STEP_1] = PC_FLUSH_COND;
	microcode[INSTR_JNQA << 3 | MICROCODE_STEP_2] = FINISH;

	microcode[INSTR_JNZB << 3 | MICROCODE_STEP_0] = PUT_B_ADDR | COND_INVERT | SAVE_PCB_IF_Z;
	microcode[INSTR_JNZB << 3 | MICROCODE_STEP_1] = PC_FLUSH_COND;
	microcode[INSTR_JNZB << 3 | MICROCODE_STEP_2] = FINISH;

	microcode[INSTR_JMPB << 3 | MICROCODE_STEP_0] = PUT_B_ADDR | SAVE_PCB;
	microcode[INSTR_JMPB << 3 | MICROCODE_STEP_1] = PC_FLUSH;
	microcode[INSTR_JMPB << 3 | MICROCODE_STEP_3] = FINISH;

	microcode[INSTR_JZRB << 3 | MICROCODE_STEP_0] = PUT_B_ADDR | SAVE_PCB_IF_Z;
	microcode[INSTR_JZRB << 3 | MICROCODE_STEP_1] = PC_FLUSH_COND;
	microcode[INSTR_JZRB << 3 | MICROCODE_STEP_2] = FINISH;

	microcode[INSTR_JEQB << 3 | MICROCODE_STEP_0] = PUT_B_ADDR | SAVE_PCB_IF_EQ;
	microcode[INSTR_JEQB << 3 | MICROCODE_STEP_1] = PC_FLUSH_COND;
	microcode[INSTR_JEQB << 3 | MICROCODE_STEP_2] = FINISH;

	microcode[INSTR_JNQB << 3 | MICROCODE_STEP_0] = PUT_B_ADDR | COND_INVERT | SAVE_PCB_IF_EQ;
	microcode[INSTR_JNQB << 3 | MICROCODE_STEP_1] = PC_FLUSH_COND;
	microcode[INSTR_JNQB << 3 | MICROCODE_STEP_2] = FINISH;

	microcode[INSTR_LDRB << 3 | MICROCODE_STEP_0] = PUT_B_ADDR | SAVE_DB_IR0 | PUT_MEM_DB;
	microcode[INSTR_LDRB << 3 | MICROCODE_STEP_1] = FINISH;

	microcode[INSTR_WTRB << 3 | MICROCODE_STEP_0] = PUT_B_ADDR | SAVE_DB_MEM | PUT_IR0_DB;
	microcode[INSTR_WTRB << 3 | MICROCODE_STEP_1] = FINISH;

	microcode[INSTR_JMPI << 3 | MICROCODE_STEP_0] = PUT_IADR_ADDR | SAVE_PCB;
	microcode[INSTR_JMPI << 3 | MICROCODE_STEP_1] = PC_FLUSH;
	microcode[INSTR_JMPI << 3 | MICROCODE_STEP_3] = FINISH;

	microcode[INSTR_JEQI << 3 | MICROCODE_STEP_0] = PUT_IADR_ADDR | SAVE_PCB_IF_EQ;
	microcode[INSTR_JEQI << 3 | MICROCODE_STEP_1] = PC_FLUSH_COND;
	microcode[INSTR_JEQI << 3 | MICROCODE_STEP_2] = FINISH;

	microcode[INSTR_JNQI << 3 | MICROCODE_STEP_0] = PUT_IADR_ADDR | COND_INVERT | SAVE_PCB_IF_EQ;
	microcode[INSTR_JNQI << 3 | MICROCODE_STEP_1] = PC_FLUSH_COND;
	microcode[INSTR_JNQI << 3 | MICROCODE_STEP_2] = FINISH;

	microcode[INSTR_JEQI << 3 | MICROCODE_STEP_0] = PUT_IADR_ADDR | SAVE_PCB_IF_EQ;
	microcode[INSTR_JEQI << 3 | MICROCODE_STEP_1] = PC_FLUSH_COND;
	microcode[INSTR_JEQI << 3 | MICROCODE_STEP_2] = FINISH;

	microcode[INSTR_JNZI << 3 | MICROCODE_STEP_0] = PUT_IADR_ADDR | COND_INVERT | SAVE_PCB_IF_Z;
	microcode[INSTR_JNZI << 3 | MICROCODE_STEP_1] = PC_FLUSH_COND;
	microcode[INSTR_JNZI << 3 | MICROCODE_STEP_2] = FINISH;


	FILE* f = fopen("microcode.bin", "wb");
	fwrite(microcode, sizeof(microcode), 1, f);
	fclose(f);
}