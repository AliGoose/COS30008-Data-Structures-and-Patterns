#include "CharacterCounter.h"

CharacterCounter::CharacterCounter() noexcept : 
	fTotalNumberOfCharacters(0),
	fCharacterCounts()
{
	for (size_t i = 0; i <256; i++)
	{
		fCharacterCounts[i].setCharacter(static_cast<unsigned char>(i));
	}
}

void CharacterCounter::count(unsigned char aCharacter) noexcept
{
	fCharacterCounts[aCharacter].increment();
	fTotalNumberOfCharacters++;

	//size_t i = 0;
	//for (; i < 256; i++)
	//{
	//	if (fCharacterCounts[i].character() == aCharacter)
	//	{
	//		fCharacterCounts[i].increment();
	//		fTotalNumberOfCharacters++;
	//		break;
	//	}
	//}
}

const CharacterMap& CharacterCounter::operator[](unsigned char aCharacter) const noexcept
{
	return fCharacterCounts[aCharacter];
}