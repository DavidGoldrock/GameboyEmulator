#pragma once
#include <stdint.h>
#include "common.h"

class RAMLocations {
public:
	static const u32 bootROMStart = 0x0000;
	static const u32 cartridgeRAMStart = 0x0100;
	static const u32 additionalBankStart = 0x4000;
	static const u32 graphicsRAMStart = 0x8000;
	static const u32 extraRAMStart = 0xa000;
	static const u32 workingRAMStart = 0xc000;
	static const u32 workingRAM2Start = 0xe000;
	static const u32 OAMStart = 0xfe00;
	static const u32 OIStart = 0xff00;
	static const u32 HighRAMStart = 0xff80;
	static const u32 Interupts = 0xffff;

	static const u32 BankSize = 0x4000;
};
