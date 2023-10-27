#pragma once
#include "PhysicalRAM.h"
#include "CartridgeRAM.h"
#include "RAM.h"
#include "CPU.h"
#include "common.h"
class GameBoy
{
public:
	GameBoy();
	~GameBoy();
	PhysicalRAM* physicalRAM;
	CartridgeRAM* cartridgeRAM;
	CPU* cpu;

	void setValue(u32 location, u8 value);
	u8 getValue(u32 location);
private:
	u8 fetch(u32 location);
	void execute(u8 code);
};

