#include "OrderingForwardIterator.h"

OrderingForwardIterator::OrderingForwardIterator(const DataWrapper* aCollection) noexcept :
	fCollection(aCollection),
	fIndex(0),
	fMapPosition(0)
{
	setMapPosition();
}

void OrderingForwardIterator::setMapPosition() // This will go thorugh the data finding the key that equals the fIndex. It then assigns fMapPosition the value of the index it is in the data.
{
	for (size_t i = 0; i < (*fCollection).size(); i++)
	{
		if ((*fCollection)[i].key() == fIndex)
		{
			fMapPosition = i;
			break;
		}
	}
}

const DataMap& OrderingForwardIterator::operator*() noexcept
{
	return (*fCollection)[fMapPosition];
}

OrderingForwardIterator& OrderingForwardIterator::operator++() noexcept //prefix - Increase fIndex by 1 and then find the new fMapPosition
{
	fIndex++;
	setMapPosition();
	return *this;
}

OrderingForwardIterator OrderingForwardIterator::operator++(int) noexcept //postfix - Increase fIndex by 1 and then find the new fMapPosition, but return the iterator before the increase.
{
	OrderingForwardIterator old = *this;
	++(*this);
	return old;
}

bool OrderingForwardIterator::operator==(const OrderingForwardIterator& aOther) const noexcept
{
	return fCollection == aOther.fCollection && fIndex == aOther.fIndex; // once again we have to compare the member variables and not the iterators themselves because it just causes an infinite recursive loop (aka stack overflow)
}

bool OrderingForwardIterator::operator!=(const OrderingForwardIterator& aOther) const noexcept
{
	return !(*this == aOther); // this just calls the aboe function
}

OrderingForwardIterator OrderingForwardIterator::begin() const noexcept
{
	OrderingForwardIterator Result = *this;
	Result.fIndex = 0;
	Result.setMapPosition(); //need to update the fMapPosition after setting the fIndex = 0;
	return Result;
}

OrderingForwardIterator OrderingForwardIterator::end() const noexcept
{
	OrderingForwardIterator Result = *this;
	Result.fIndex = (*fCollection).size(); // no need to update the fMapPosition when it's the end condition statement
	return Result;
}