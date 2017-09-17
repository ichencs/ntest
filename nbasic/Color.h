#pragma once
#include "basic.h"

namespace n
{
	using namespace vl;
	typedef vuint Rgb;

	const Rgb  RGB_MASK = 0x00ffffff;     // masks RGB values

	inline int nRed(Rgb rgb)
	{
		return ((rgb >> 16) & 0xff);
	}

	inline int nGreen(Rgb rgb)                // get green part of RGB
	{
		return ((rgb >> 8) & 0xff);
	}

	inline int nBlue(Rgb rgb)                // get blue part of RGB
	{
		return (rgb & 0xff);
	}
	inline Rgb nRgb(int r, int g, int b)	// set RGB value
	{
		return (0xffu << 24) | ((r & 0xffu) << 16) | ((g & 0xffu) << 8) | (b & 0xffu);
	}



	class Color
	{
	public:
		Color();
		~Color();
	};

}

