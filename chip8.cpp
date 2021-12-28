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
	init_table();
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
		auto current_time = std::chrono::high_resolution_clock::now();
		time_elapsed = std::chrono::duration<float, std::chrono::milliseconds::period>(
			current_time - lastTime).count();

		if (time_elapsed >= interval) // Run the fetch decode execute cycle
		{
			lastTime = current_time;
			opCode = mem[PC++] << 8; // Get first half of opCode
			n = 0xF; nnn = 0xFFF; // Reset n and nnn masks
			n &= nnn &= opCode |= kk = mem[PC++];
			x = &reg[(opCode & 0x0F00) >> 8];
			y = &reg[kk >> 4];
			(this->*table[(opCode & 0xF000) >> 12])();
			delay -= delay ? 1 : 0; // Decrement sound / delay timers if on
			sound -= sound ? 1 : 0;
		}
	}
}
