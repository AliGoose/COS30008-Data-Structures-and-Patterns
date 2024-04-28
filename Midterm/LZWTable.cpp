#include "LZWTable.h"
#include <cassert>

LZWTable::LZWTable(uint16_t aInitialCharacters) :
	fEntries(), //collection of (code, prefixstring, extension)
	fIndex(0), //next available slot index in the table
	fInitialCharacters(aInitialCharacters)
{
	if (fInitialCharacters != 128)
	{
		fInitialCharacters = 128;
	}
}

void LZWTable::initialize()
{
	fIndex = 0;
	while (fIndex < fInitialCharacters)
	{
		fEntries[fIndex] = PrefixString(static_cast<char>(fIndex));
		fEntries[fIndex].setCode(static_cast<uint16_t>(fIndex));
		fIndex++;
	}
}

const PrefixString& LZWTable::lookupStart(char aK) const noexcept
{
	assert(aK < fInitialCharacters);

	return fEntries[static_cast<uint16_t>(aK)];
}

bool LZWTable::contains(PrefixString& aWK) const noexcept
{
	assert(aWK.w() != static_cast<uint16_t>(-1));

	for (uint16_t i = fIndex - 1; i > aWK.w(); i--)
	{
		if (fEntries[i] == aWK)
		{
			aWK = fEntries[i];
			return true;
		}
	}
	return false;
}

void LZWTable::add(PrefixString& aWK) noexcept
{
	assert(aWK.w() != static_cast<uint16_t>(-1));
	aWK.setCode(fIndex);
	fEntries[fIndex++] = aWK;
}