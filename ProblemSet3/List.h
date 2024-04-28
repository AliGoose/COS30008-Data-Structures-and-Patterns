
// COS30008, Problem Set 3, 2023

#pragma once

#include "DoublyLinkedList.h"
#include "DoublyLinkedListIterator.h"

#include <cassert>

template<typename T>
class List
{
private:
    using Node = typename DoublyLinkedList<T>::Node;

    Node fHead;		// first element
    Node fTail;		// last element
    size_t fSize;	// number of elements

public:

    using Iterator = DoublyLinkedListIterator<T>;

    List() noexcept :							// default constructor
        //fHead(nullptr),
        //fTail(nullptr),
        fSize(0)
    {}

    // copy semantics
    List(const List& aOther) :					// copy constructor
        List()
    {
        for (auto& item : aOther)
        {
            push_back(item);
        }
    }

    List& operator=(const List& aOther)		// copy assignment
    {
        if (this != &aOther)
        {
            this->~List();
            new (this) List(aOther);
        }
        return *this;
    }

    // move semantics
    List(List&& aOther) noexcept :				// move constructor
        List()
    {
        swap(aOther);
    }

    List& operator=(List&& aOther) noexcept	// move assignment
    {
        if (this != &aOther)
        {
            swap(aOther);
        }
        return *this;
    }

    void swap(List& aOther) noexcept			// swap elements
    {
        std::swap(fHead, aOther.fHead);
        std::swap(fTail, aOther.fTail);
        std::swap(fSize, aOther.fSize);
    }

    // basic operations
    size_t size() const noexcept				// list size
    {
        return fSize;
    }

    template<typename U>
    void push_front(U&& aData)				// add element at front
    {
        //Node lNode = DoublyLinkedList<T>::makeNode(aData);
        //if (fSize == 0)
        //{
        //    fHead = lNode;
        //    fTail = lNode;
        //}
        //else
        //{
        //    Node lOldHead = fHead;
        //    fHead = lNode;
        //    lOldHead->fPrevious = fHead;
        //    fHead->fNext = lOldHead;
        //}
        //fSize++;

        Node lNode = DoublyLinkedList<T>::makeNode(std::forward<U>(aData));

        if (!fHead)                               // first element
        {
            fTail = lNode;                          // set tail to first element
        }
        else
        {
            lNode->fNext = fHead;                   // new node becomes head
            fHead->fPrevious = lNode;               // new node previous of head
        }

        fHead = lNode;                              // new head
        fSize++;                                    // increment size
    }

    template<typename U>
    void push_back(U&& aData)				// add element at back
    {
        //Node lNode = DoublyLinkedList<T>::makeNode(aData);
        //if (fSize == 0)
        //{
        //    fHead = lNode;
        //    fTail = lNode;
        //}
        //else
        //{
        //    Node lOldTail = fTail;
        //    fTail = lNode;
        //    lOldTail->fNext = fTail;
        //    fTail->fPrevious = lOldTail;
        //}
        //fSize++;

        Node lNode = DoublyLinkedList<T>::makeNode(std::forward<U>(aData));

        if (!fTail)                               // first element
        {
            fHead = lNode;                          // set head to first element
        }
        else
        {
            lNode->fPrevious = fTail;               // new node becomes tail
            fTail->fNext = lNode;                   // new node next of tail
        }

        fTail = lNode;                              // new tail
        fSize++;                                    // increment size
    }

    void remove(const T& aElement) noexcept	// remove element
    {
        Node lNode = fHead;                         // start at first

        while (lNode)                             // Are there still nodes available?
        {
            if (lNode->fData == aElement)         // Have we found the node?
            {
                break;                              // stop the search
            }

            lNode = lNode->fNext;                   // move to next node
        }

        if (lNode)                                // We have found a first matching node.
        {
            if (fHead == lNode)                   // remove head
            {
                fHead = lNode->fNext;               // make lNode's next head
            }

            if (fTail == lNode)                   // remove tail
            {
                fTail = lNode->fPrevious.lock();    // make lNode's previuos tail, requires std::shared_ptr
            }

            lNode->isolate();                       // isolate node, automatically freed
            fSize--;                                // decrement count
        }
    }

    const T& operator[](size_t aIndex) const	// list indexer
    {
        assert(aIndex < fSize);

        Node lNode = fHead;

        while (aIndex--)
        {
            lNode = lNode->fNext;
        }

        return lNode->fData;
    }

    // iterator interface
    Iterator begin() const noexcept
    {
        //return Iterator(fHead, fTail).begin();
        return Iterator(fHead, fTail);
    }

    Iterator end() const noexcept
    {
        //return Iterator(fHead, fTail).end();
        return begin().end();
    }

    Iterator rbegin() const noexcept
    {
        //return Iterator(fHead, fTail).rbegin();
        return begin().rbegin();
    }

    Iterator rend() const noexcept
    {
        //return Iterator(fHead, fTail).rend();
        return begin().rend();
    }
};
