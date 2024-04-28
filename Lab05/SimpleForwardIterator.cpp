#include "SimpleForwardIterator.h"
#include <iostream>

SimpleForwardIterator::SimpleForwardIterator(const DataWrapper* aCollection) noexcept :
	fCollection(aCollection),
	fIndex(0)
{};

const DataMap& SimpleForwardIterator::operator*() noexcept
{
	return (*fCollection)[fIndex]; //we have to "()" the *fcollection because this allows the (*fCollection) to just become a DataWrapper
}

SimpleForwardIterator& SimpleForwardIterator::operator++() noexcept //prefix
{
	fIndex++;
	return *this;
}

SimpleForwardIterator SimpleForwardIterator::operator++(int) noexcept //postfix
{
	SimpleForwardIterator old = *this;
	++(*this); //This just calls the above function. So we increase the interator, but return the index of the iterator before the increase.
	return old;
}

bool SimpleForwardIterator::operator==(const SimpleForwardIterator& aOther) const noexcept
{
	return fCollection == aOther.fCollection && fIndex == aOther.fIndex; //we have to verify via the member variables because if we just compare "==" the SimpleForwardIterators, it just ends up calling itself causing a infinte recursive loop (aka stack overflow).
}

bool SimpleForwardIterator::operator!=(const SimpleForwardIterator& aOther) const noexcept
{
	return !(*this == aOther); //This just calls the above function
}

SimpleForwardIterator SimpleForwardIterator::begin() const noexcept // This is returning an iterator with the same fCollection as *this but it's index starts at the first position
{
	SimpleForwardIterator Result = *this;
	Result.fIndex = 0;
	return Result;
}

SimpleForwardIterator SimpleForwardIterator::end() const noexcept // This is returning an iterator with the same fCollection as *this but it's index starts at the (last position + 1)
{
	SimpleForwardIterator Result = *this;
	Result.fIndex = (*fCollection).size();
	return Result;
}