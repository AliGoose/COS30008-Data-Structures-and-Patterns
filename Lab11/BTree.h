
// COS30008, Tutorial 11, 2023

#pragma once

#include <memory>
#include <cassert>
#include <iostream>

template<typename T>
class BTree
{
public:
	using Node = std::unique_ptr<BTree>;

	BTree( const T& aKey = T{} ) noexcept : 
		fKey(aKey)
	{}

	BTree(T&& aKey) noexcept :
		fKey(std::move(aKey))
	{}
    
	~BTree()
	{
		std::cout << "Delete " << fKey << std::endl;
	}
	
	template<typename... Args>
	static Node makeNode(Args&&... args)
	{
		return std::make_unique<BTree>(std::forward<Args>(args)...);
	}

	// copy semantics
	BTree(const BTree& aOther) :
		fKey(aOther.fKey)
	{
		if (aOther.fLeft)
		{
			fLeft = std::move(makeNode(*aOther.fLeft));
		}
		if (aOther.fRight)
		{
			fRight = std::move(makeNode(*aOther.fRight));
		}
	}

	BTree& operator=(const BTree& aOther)
	{
		if (this != aOther)
		{
			this->~BTree();
			new (this) BTree(aOther);
		}
		return *this;
	}

	// move semantics
	BTree(BTree&& aOther) noexcept :
		BTree()
	{
		swap(aOther);
	}

	BTree& operator=(BTree&& aOther) noexcept
	{
		if (this != aOther)
		{
			swap(aOther);
		}
		return *this;
	}

	void swap(BTree& aOther) noexcept
	{
		std::swap(fKey, aOther.fKey);
		std::swap(fLeft, aOther.fLeft);
		std::swap(fRight, aOther.fRight);
	}

	const T& operator*() const noexcept
	{
		return fKey;
	}

	bool hasLeft() const noexcept //These 'has' methods are redundent. The asserts could simply be replaced with assert(fLeft) or assert(fRight)
	{
		return fLeft ? true : false;
	}

	BTree& left() const
	{
		assert(fLeft);
		
		return *fLeft;
	}

	bool hasRight() const noexcept
	{
		return fRight ? true : false;
	}

	BTree& right() const
	{
		assert(fRight);

		return *fRight;
	}

	void attachLeft(Node& aNode)
	{
		assert(!fLeft);

		fLeft = std::move(aNode);
	}

	void attachRight(Node& aNode)
	{
		assert(!fRight);

		fRight = std::move(aNode);
	}

	Node detachLeft()
	{
		assert(fLeft);

		return std::move(fLeft);
	}

	Node detachRight()
	{
		assert(fRight);

		return std::move(fRight);
	}
    
	bool leaf() const noexcept
	{
		return !fLeft && !fRight; 
	}

	size_t height() const noexcept
	{
		size_t result = 0;

		if (!leaf())
		{
			result = std::max(fLeft ? fLeft->height() + 1 : 0, fRight ? fRight->height() + 1 : 0);
		}
		return result;

		//if (leaf())
		//{
		//	return 0;
		//}

		//size_t leftHeight = fLeft ? fLeft->height() : 0;
		//size_t rightHeight = fRight ? fRight->height() : 0;

		//return 1 + std::max(leftHeight, rightHeight);
	}

	const T& findMax() const noexcept
	{
		if (hasRight())
		{
			return right().findMax();
		}
		return **this; //**this is better than fKey because the derefence operator * controls the access to that variable

		//if (!hasRight())
		//{
		//	return fKey;
		//}
		//return fRight->findMax();
	}

	const T& findMin() const noexcept
	{
		if (hasLeft())
		{
			return left().findMin();
		}
		return **this;

		//if (!hasLeft())
		//{
		//	return fKey;
		//}
		//return fLeft->findMin();
	}

private:
	T fKey;
	Node fLeft;
	Node fRight;
};
