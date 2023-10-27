#pragma once
#include "RAMLocations.h"
#include "common.h"
#include <stdint.h>
class RAM
{
public:

	RAM();
	virtual bool isInRange(u32 location) = 0;
	virtual u8 getValue(u32 location) = 0;
	virtual void setValue(u32 location, unsigned char value) = 0;

private:

};

