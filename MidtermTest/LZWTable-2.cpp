#include "LZWTable.h"
#include "cassert"

LZWTable::LZWTable(uint16_t aInitialCharacters) :
	fEntries(), //collection of (code, prefixstring, extension)
	fIndex(0), //next available slot index in the table
	fInitialCharacters(aInitialCharacters)
{
	
}

void LZWTable::initialize()
{
	if (fInitialCharacters > 128)
	{
		fInitialCharacters = 128;
	}
	for (size_t i = 0; i < fInitialCharacters; i++)
	{
		fEntries[i] = PrefixString(static_cast<char>(i));
		fEntries[i].setCode(static_cast<uint16_t>(i));
	}
	fIndex = fInitialCharacters;
}

const PrefixString& LZWTable::lookupStart(char aK) const noexcept
{
	assert( -1 < aK < fIndex);
	size_t i;
	for (i = 0; i < fIndex; i++)
	{
		if (fEntries[i].K() == aK)
		{
			break;
		}
	}
	return fEntries[i];
}

bool LZWTable::contains(PrefixString& aWK) const noexcept
{
	assert(aWK.w() != static_cast<uint16_t>(-1));
	size_t index = fIndex - 1;
	while (index >= aWK.w())
	{
		if (aWK == fEntries[index])
		{
			aWK = fEntries[index];
			return true;
		}
		index--;
	}
	return false;

}

void LZWTable::add(PrefixString& aWK) noexcept
{
	assert(aWK.w() != static_cast<uint16_t>(-1));
	aWK.setCode(fIndex);
	fEntries[fIndex++] = aWK;
}