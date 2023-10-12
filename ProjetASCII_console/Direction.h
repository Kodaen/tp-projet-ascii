#pragma once
// This uses decimal values
//enum DIRECTION
//{
//	TOP = 1024,
//	TOP_RIGHT = 5120,
//	RIGHT = 4096,
//	BOTTOM_RIGHT = 36864,
//	BOTTOM = 40960,
//	BOTTOM_LEFT = 34816,
//	LEFT = 2048,
//	TOP_LEFT = 3072,
//};

// This uses hex values
enum DIRECTION
{
	TOP = 0x0400,
	LEFT = 0x0800,
	TOP_LEFT = 0x0C00,
	RIGHT = 0x1000,
	TOP_RIGHT = 0x1400,
	BOTTOM = 0x8000,
	BOTTOM_LEFT = 0x8800,
	BOTTOM_RIGHT = 0x9000,	
};