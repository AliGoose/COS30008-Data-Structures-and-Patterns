
// COS30008, Final Exam, 2023

#include "DSPStringIterator.h"

DSPStringIterator::DSPStringIterator( const DSPString& aCollection ) :
	fCollection( std::make_shared<DSPString>( aCollection ) ),
	fIndex( 0 )
{}

char DSPStringIterator::operator*() const noexcept
{
	// 4A
	return (*fCollection)[fIndex];
}

DSPStringIterator& DSPStringIterator::operator++() noexcept
{
	// 4B
	fIndex++;
	return *this;
}

DSPStringIterator DSPStringIterator::operator++( int ) noexcept
{
	DSPStringIterator old = *this;

	++(*this);

	return old;
}

DSPStringIterator& DSPStringIterator::operator--() noexcept
{
	// 4C
	--fIndex;
	return *this;
}

DSPStringIterator DSPStringIterator::operator--( int ) noexcept
{
	DSPStringIterator old = *this;

	--(*this);

	return old;
}

bool DSPStringIterator::operator==( const DSPStringIterator& aOther ) const noexcept
{
	// 4D
	return fIndex == aOther.fIndex && fCollection == aOther.fCollection;
}

bool DSPStringIterator::operator!=( const DSPStringIterator& aOther ) const noexcept
{
	return !(*this == aOther);
}

DSPStringIterator  DSPStringIterator::begin() const noexcept
{
	// 4E
	DSPStringIterator lCopy = *this;
	lCopy.fIndex = 0;
	return lCopy;
}

DSPStringIterator DSPStringIterator::end() const noexcept
{
	// 4F
	DSPStringIterator lCopy = *this;
	lCopy.fIndex = lCopy.fCollection->size();
	return lCopy;
}

DSPStringIterator DSPStringIterator::rbegin() const noexcept
{
	// 4G
	return --(end());
}

DSPStringIterator DSPStringIterator::rend() const noexcept
{
	// 4H
	DSPStringIterator lCopy = *this;
	lCopy.fIndex = -1;
	return lCopy;
}
