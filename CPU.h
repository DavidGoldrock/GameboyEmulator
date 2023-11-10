#pragma once
#include <stdint.h>
#include "common.h"

class CPU
{
public:
	union AF {
		struct {
			u8 FLAGS;
			u8 A;
		};
		u16 AF;
	};
	union BC {
		struct {
			u8 C;
			u8 B;
		};
		u16 BC;
	};
	union DE {
		struct {
			u8 E;
			u8 D;
		};
		u16 DE;
	};
	union HL {
		struct {
			u8 L;
			u8 H;
		};
		u16 HL;
	};
	AF AF;
	BC BC;
	DE DE;
	HL HL;
	u16 SP;
	u16 PC;
	bool isPrefixed;


	CPU();

	void setZFlag(bool Z);
	void setSFlag(bool S);
	void setHFlag(bool H);
	void setCFlag(bool C);
};

