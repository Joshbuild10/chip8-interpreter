#include "chip8.hpp"
#include <cstdlib>
#include <ctime>
void chip8::op_null() {}
void chip8::op_00E0()
{
	
}
void chip8::op_00EE() // Return from subroutine
{
	PC = stack[--SP];
}
// Sets PC to address nnn
void chip8::op_1nnn() { PC = nnn; }
// Call subroutine at nnn
void chip8::op_2nnn()
{
	stack[SP++] = PC;
	PC = nnn;
}
// Skip next instruction if Vx = kk.
void chip8::op_3xkk()
{
	PC += (*x == kk) ? 2 : 0;
}
// Skip next instruction if Vx != kk.
void chip8::op_4xkk()
{
	PC += (*x != kk) ? 2 : 0;
}
// Skip next instruction if Vx = Vy.
void chip8::op_5xy0()
{
	PC += (*x == *y) ? 2 : 0;
}
// Set Vx = kk
void chip8::op_6xkk()
{
	*x = kk;
}
// Set Vx = Vx + kk
void chip8::op_7xkk()
{
	*x += kk;
}
// Set Vx = Vy
void chip8::op_8xy0()
{
	*x = *y;
}
// Set Vx = Vx OR Vy
void chip8::op_8xy1()
{
	*x |= *y;
}
// Set Vx = Vx AND Vy
void chip8::op_8xy2()
{
	*x &= *y;
}
// Vx = Vx XOR Vy
void chip8::op_8xy3()
{
	*x ^= *y;
}
// Set Vx = Vx + Vy, set VF = carry
void chip8::op_8xy4()
{
	reg[0xF] = *x + *y > 255 ? 1 : 0;
	*x = (*x + *y) & 0xFF;
}
// Set Vx = Vx - Vy, set VF = NOT borrow
void chip8::op_8xy5()
{
	reg[0xF] = *x > *y ? 1 : 0;
	*x -= *y;
}
// Set Vx = Vx SHR 1
void chip8::op_8xy6()
{
	reg[0xF] = *x % 2;
	*x >>= 1;
}
// Set Vx = Vy - Vx, set VF = NOT borrow
void chip8::op_8xy7()
{
	reg[0xF] = *y > *x ? 1 : 0;
	*x = *y - *x;
}
// Set Vx = Vx SHL 1
void chip8::op_8xyE()
{
	reg[0xF] = *x >= 0x80 ? 1 : 0;
	*x <<= 1;
}
// Skip next instruction if Vx != Vy
void chip8::op_9xy0()
{
	PC += *x != *y ? 2 : 0;
}
// The value of register I is set to nnn.
void chip8::op_Annn()
{
	I = nnn;
}
// Jump to location nnn + V0
void chip8::op_Bnnn()
{
	PC = nnn + reg[0x0];
}
// Set Vx = random byte AND kk
void chip8::op_Cxkk()
{
	srand(time(0));
	*x = (rand() % 256) & kk;
}
void chip8::op_Dxyn()
{

}
void chip8::op_Ex9E()
{

}
void chip8::op_ExA1()
{

}
// Set Vx = delay timer value
void chip8::op_Fx07()
{
	*x = delay;
}
void chip8::op_Fx0A()
{

}
// Set delay timer = Vx
void chip8::op_Fx15()
{
	delay = *x;
}
// Set sound timer = Vx
void chip8::op_Fx18()
{
	sound = *x;
}
// Set I = I + Vx
void chip8::op_Fx1E()
{
	I += *x;
}
void chip8::op_Fx29()
{

}
// Store BCD representation of Vx in memory locations I, I+1, and I+2
void chip8::op_Fx33()
{
	int value = *x;
	mem[I + 2] = value % 10; // 1's place
	value /= 10;
	mem[I + 1] = value % 10; // 10's place
	value /= 10;
	mem[I] = value % 10; // 100's place
}
// Store registers V0 through Vx in memory starting at location I
void chip8::op_Fx55()
{
	memcpy(&mem[I], reg, sizeof(uint8_t) * (x - reg + 1));
}
// Read registers V0 through Vx from memory starting at location I
void chip8::op_Fx65()
{
	memcpy(reg, &mem[I], sizeof(uint8_t) * (x - reg + 1));
}