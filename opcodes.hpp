#include "chip8.hpp"
void chip8::op_null() {}
void chip8::op_00E0()
{
	
}
void chip8::op_00EE() // Return from subroutine
{
	PC = stack[--SP];
}
// Sets PC to address nnn
void chip8::op_1nnn() { PC = opCode & 0x0FFF; }
// Call subroutine at nnn
void chip8::op_2nnn()
{
	stack[SP++] = PC;
	PC = opCode & 0x0FFF;
}
// Skip next instruction if Vx = kk.
void chip8::op_3xkk()
{
	PC += (reg[(opCode & 0x0F00) >> 8] == (opCode & 0x00FF)) ? 2 : 0;
}
// Skip next instruction if Vx != kk.
void chip8::op_4xkk()
{
	PC += (reg[(opCode & 0x0F00) >> 8] != (opCode & 0x00FF)) ? 2 : 0;
}
// Skip next instruction if Vx = Vy.
void chip8::op_5xy0()
{
	PC += (reg[(opCode & 0x0F00) >> 8] == (reg[(opCode & 0x00F0) >> 4])) ? 2 : 0;
}
// Set Vx = kk
void chip8::op_6xkk()
{
	reg[(opCode & 0x0F00) >> 8] = opCode & 0x00FF;
}
// Set Vx = Vx + kk
void chip8::op_7xkk()
{
	reg[(opCode & 0x0F00) >> 8] += opCode & 0x00FF;
}
// Set Vx = Vy
void chip8::op_8xy0()
{
	reg[(opCode & 0x0F00) >> 8] = reg[(opCode & 0x00F0) >> 4];
}
// Set Vx = Vx OR Vy
void chip8::op_8xy1()
{
	reg[(opCode & 0x0F00) >> 8] |= reg[(opCode & 0x00F0) >> 4];
}
//
void chip8::op_8xy2()
{

}
void chip8::op_8xy3()
{

}
void chip8::op_8xy4()
{

}
void chip8::op_8xy5()
{

}
void chip8::op_8xy6()
{

}
void chip8::op_8xy7()
{

}
void chip8::op_8xyE()
{

}
void chip8::op_9xy0()
{

}
void chip8::op_Annn()
{

}
void chip8::op_Bnnn()
{

}
void chip8::op_Cxkk()
{

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
void chip8::op_Fx07()
{

}
void chip8::op_Fx0A()
{

}
void chip8::op_Fx15()
{

}
void chip8::op_Fx18()
{

}
void chip8::op_Fx1E()
{

}
void chip8::op_Fx29()
{

}
void chip8::op_Fx33()
{

}
void chip8::op_Fx55()
{

}
void chip8::op_Fx65()
{

}