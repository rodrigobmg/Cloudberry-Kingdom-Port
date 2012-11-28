#ifndef _BINARY_READER_H_
#define _BINARY_READER_H_

#include <Math/Vectors.h>
#include <string>

class BinaryReader
{

public:

	int ReadInt32()
	{
		// FIXME: Implement this.
		return 0xdeadbeef;
	}

	std::wstring ReadString()
	{
		return std::wstring();
	}

	Vector2 ReadVector2()
	{
		return Vector2();
	}

	bool ReadBoolean()
	{
		return false;
	}

	float ReadSingle()
	{
		return 0;
	}

	unsigned char ReadByte()
	{
		return 0;
	}

	unsigned char PeekChar()
	{
		return 0;
	}
};

#endif