#include "LZWCompressor.h"

LZWCompressor::LZWCompressor(const std::string& aInput) :
	//fTable(128), // the LZW table
	//fW(), // the current prefix string 
	fInput(aInput), // the input data (string)
	fIndex(0), // the iterator index into the input data
	fK(-1), // the current input character K
	fCurrentCode(static_cast<uint16_t>(-1)) // the code of the current prefix string (code(w))
{
	start();
}

bool LZWCompressor::readK() noexcept
{
	if (fIndex < fInput.size())
	{
		fK = fInput[fIndex++];
		return true;
	}
	fK = -1;
	return false;
}

void LZWCompressor::start()
{
	fTable.initialize();
	if (readK())
	{
		fW = fTable.lookupStart(fK);
	}
	fCurrentCode = nextCode();
}

uint16_t LZWCompressor::nextCode()
{     
	if (fK == -1)
	{
		return static_cast<uint16_t>(-1);
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
			fW = fTable.lookupStart(wK.K());
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
	Result.fIndex = 0;
	Result.start();
	return Result;
}

LZWCompressor LZWCompressor::end() const noexcept
{
	LZWCompressor Result = *this;
	Result.fIndex = fInput.size();
	Result.fK = -1;
	Result.fCurrentCode = static_cast<uint16_t>(-1);
	return Result;
}