#pragma once
#include "RAM.h"
#include "common.h"

class PhysicalRAM : public RAM
{
public:
	PhysicalRAM();
	~PhysicalRAM();
	void setValue(u32 location, u8 value);
	u8 getValue(u32 location);
	bool isInRange(u32 location);

	u8* bootROM;
	u8* graphicsRAM;
	u8* workingRAM;
	u8* OAM;
	u8* HighRAM;
	u8 FFFF_Interrupts;
};

