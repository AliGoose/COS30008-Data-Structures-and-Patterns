#include "LZWCompressor.h"

LZWCompressor::LZWCompressor(const std::string& aInput) :
	fTable(128), // the LZW table
	fW(), // the current prefix string 
	fInput(aInput), // the input data (string)
	fIndex(0), // the iterator index into the input data
	fK(), // the current input character K
	fCurrentCode() // the code of the current prefix string (code(w))
{
	start();
}

bool LZWCompressor::readK() noexcept
{
	if (fInput[fIndex + 1] == '\0')
	{
		fK = -1;
		return false;
	}
	fK = fInput[++fIndex];
	return true;
}

void LZWCompressor::start()
{
	fIndex = 0;
	fTable.initialize();
	fK = fInput[fIndex];
	fW = fTable.lookupStart(fK);
	fCurrentCode = nextCode();
}

uint16_t LZWCompressor::nextCode()
{     
	if (fK == -1)
	{
		return -1;
	}
	while (readK())
	{
		PrefixString wK = fW + fK;
		if (fTable.contains(wK))
		{
			fW = wK;
		}
		else
		{
			uint16_t oldfW = fW.getCode();
			fTable.add(wK);
			fW = fTable.lookupStart(fK);
			return oldfW;
		}
	}
	return fW.getCode();
}

const uint16_t& LZWCompressor::operator*() const noexcept
{
	return fCurrentCode;
}

LZWCompressor& LZWCompressor::operator++() noexcept
{
	fCurrentCode = nextCode();
	return *this;
}

LZWCompressor LZWCompressor::operator++(int) noexcept
{
	LZWCompressor old = *this;
	++(*this);
	return old;
}

bool LZWCompressor::operator==(const LZWCompressor& aOther) const noexcept
{
	return (fInput == aOther.fInput) && (fIndex == aOther.fIndex) && (fK == aOther.fK) && (fCurrentCode == aOther.fCurrentCode);
}

bool LZWCompressor::operator!=(const LZWCompressor& aOther) const noexcept
{
	return !(*this == aOther);
}

LZWCompressor LZWCompressor::begin() const noexcept
{
	LZWCompressor Result = *this;
	Result.start();
	return Result;
}

LZWCompressor LZWCompressor::end() const noexcept
{
	LZWCompressor Result = *this;
	Result.fIndex = Result.fInput.length()-1;
	Result.fCurrentCode = -1;
	Result.fK = -1;
	return Result;
}