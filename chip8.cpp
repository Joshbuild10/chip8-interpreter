#include <cstdint>
#include <string>
#include <fstream>
#include <chrono>
#include "chip8.hpp"
#include "tables.hpp"

chip8::chip8()
{
	PC = START_ADDRESS;
	scale = interval = I = nnn = opCode = n = kk = SP = sound = delay = running = 0;
	x = y = nullptr;
	init_table();
}

void chip8::load_rom(const std::string& rom_dir)
{
	std::ifstream file(rom_dir, std::ios::binary | std::ios::ate);

	if (file.is_open())
	{
		const std::streampos size = file.tellg();
		auto buffer = new char[static_cast<int>(size)];
		file.seekg(0, std::ios::beg);
		file.read(buffer, size);
		file.close();
		memcpy(mem + START_ADDRESS, buffer, sizeof(char) * static_cast<char>(size));
		delete[] buffer;
	}
}

void chip8::init(const std::string& rom_dir, const float in_speed, const float in_scale)
{
	load_rom(rom_dir);
	this->scale = in_scale;
	this->interval = in_speed;
}

void chip8::run()
{
	auto lastTime = std::chrono::high_resolution_clock::now();
	float time_elapsed = 0;
	while (!running)
	{
		//quit = platform.ProcessInput(chip8.keypad);

		auto current_time = std::chrono::high_resolution_clock::now();
		time_elapsed = std::chrono::duration<float, std::chrono::milliseconds::period>(
			current_time - lastTime).count();

		if (time_elapsed >= interval) //run fetch decode execute cycle
		{
			lastTime = current_time;
			opCode = mem[PC++] << 8 | mem[PC++]; //fetches OPcode and increments PC by 2
			(this->*table[(opCode & 0xF000) >> 12])();
		}
	}
}
