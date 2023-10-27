#pragma once
#include "RAM.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "common.h"
class CartridgeRAM : public RAM
{
public:
	CartridgeRAM();
	~CartridgeRAM();

	void setValue(u32 location, u8 value);
	u8 getValue(u32 location);
	bool isInRange(u32 location);
	
	const char* gameFileName;

	
private:
	std::ifstream gameFile;
	u8* ExternalRAM;
	u8 ROMBank;
	u8 RAMBank;
	bool RAMActivated;
	bool IsRAMMode;
};


