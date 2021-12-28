#ifndef CHIP8_HPP
#define CHIP8_HPP
#include <cstdint>
#include <string>
#include <fstream>
#include <chrono>
constexpr uint16_t START_ADDRESS = 0x200;
constexpr uint16_t MEM_SIZE = 4096;
constexpr uint8_t REG_NUM = 16;
constexpr uint8_t STACK_NUM = 16;

class chip8
{
public:
	chip8();
	void load_rom(const std::string& rom_dir);
	void init(const std::string& rom_dir, const float in_speed, const float in_scale);
	void run();
private:
	bool running;
	uint8_t mem[MEM_SIZE]{ 0 }, reg[REG_NUM]{ 0 }, SP, sound, delay, *x, *y, n, kk;
	uint16_t PC, I, opCode, stack[STACK_NUM]{ 0 }, nnn;
	float scale, interval;
	void op_null();
	void op_00E0();
	void op_00EE();
	void op_1nnn();
	void op_2nnn();
	void op_3xkk();
	void op_4xkk();
	void op_5xy0();
	void op_6xkk();
	void op_7xkk();
	void op_8xy0();
	void op_8xy1();
	void op_8xy2();
	void op_8xy3();
	void op_8xy4();
	void op_8xy5();
	void op_8xy6();
	void op_8xy7();
	void op_8xyE();
	void op_9xy0();
	void op_Annn();
	void op_Bnnn();
	void op_Cxkk();
	void op_Dxyn();
	void op_Ex9E();
	void op_ExA1();
	void op_Fx07();
	void op_Fx0A();
	void op_Fx15();
	void op_Fx18();
	void op_Fx1E();
	void op_Fx29();
	void op_Fx33();
	void op_Fx55();
	void op_Fx65();

	void table0(), table8(), tableE(), tableF(), tableFx0(), tableFx1();
	typedef void(chip8::*func_ref)();
	func_ref table[0xF + 1]{ &chip8::op_null },
		table_0[0xE + 1]{ &chip8::op_null },
		table_8[0xE + 1]{ &chip8::op_null },
		table_E[0xA + 1]{ &chip8::op_null },
		table_F[0x6 + 1]{ &chip8::op_null },
		table_Fx0[0xA + 1]{ &chip8::op_null },
		table_Fx1[0xE + 1]{ &chip8::op_null };
	void init_table();
};
#endif