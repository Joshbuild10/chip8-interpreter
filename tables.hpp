#ifndef TABLES_HPP
#define TABLES_HPP
#include "opcodes.hpp"
void chip8::init_table()
{
	table[0x0] = &chip8::table0;
	table[0x1] = &chip8::op_1nnn;
	table[0x2] = &chip8::op_2nnn;
	table[0x3] = &chip8::op_3xkk;
	table[0x4] = &chip8::op_4xkk;
	table[0x5] = &chip8::op_5xy0;
	table[0x6] = &chip8::op_6xkk;
	table[0x7] = &chip8::op_7xkk;
	table[0x8] = &chip8::table8;
	table[0x9] = &chip8::op_9xy0;
	table[0xA] = &chip8::op_Annn;
	table[0xB] = &chip8::op_Bnnn;
	table[0xC] = &chip8::op_Cxkk;
	table[0xD] = &chip8::op_Dxyn;
	table[0xE] = &chip8::tableE;
	table[0xF] = &chip8::tableF;

	table_0[0x0] = &chip8::op_00E0;
	table_0[0xE] = &chip8::op_00EE;

	table_8[0x0] = &chip8::op_8xy0;
	table_8[0x1] = &chip8::op_8xy1;
	table_8[0x2] = &chip8::op_8xy2;
	table_8[0x3] = &chip8::op_8xy3;
	table_8[0x4] = &chip8::op_8xy4;
	table_8[0x5] = &chip8::op_8xy5;
	table_8[0x6] = &chip8::op_8xy6;
	table_8[0x7] = &chip8::op_8xy7;
	table_8[0xE] = &chip8::op_8xyE;

	table_E[0x9] = &chip8::op_Ex9E;
	table_E[0xA] = &chip8::op_ExA1;

	table_F[0x0] = &chip8::tableFx0;
	table_F[0x1] = &chip8::tableFx1;
	table_F[0x2] = &chip8::op_Fx29;
	table_F[0x3] = &chip8::op_Fx33;
	table_F[0x5] = &chip8::op_Fx55;
	table_F[0x6] = &chip8::op_Fx65;

	table_Fx0[0x7] = &chip8::op_Fx07;
	table_Fx0[0xA] = &chip8::op_Fx0A;

	table_Fx1[0x5] = &chip8::op_Fx15;
	table_Fx1[0x8] = &chip8::op_Fx18;
	table_Fx1[0xE] = &chip8::op_Fx1E;
}

void chip8::table0() { (this->*table_0[n])(); }
void chip8::table8() { (this->*table_8[n])(); }
void chip8::tableE() { (this->*table_E[(opCode & 0x00F0) >> 4])(); }
void chip8::tableF() { (this->*table_F[(opCode & 0x00F0) >> 4])(); }
void chip8::tableFx0() { (this->*table_Fx0[n])(); }
void chip8::tableFx1() { (this->*table_Fx1[n])(); }
#endif