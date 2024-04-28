
// COS30008, Final Exam, 2023

#pragma once

#include <memory>
#include <cassert>
#include <algorithm>

template<typename T>
class TernaryTree
{
public:
    
    using Node = std::unique_ptr<TernaryTree>;

public:

    TernaryTree(const T& aKey = T{}) noexcept :
        fKey(aKey)
    {}

    TernaryTree(T&& aKey) noexcept :
        fKey(std::move(aKey))
    {}

    template<typename... Args>
    static Node makeNode(Args&&... args)
    {
        return std::make_unique<TernaryTree>(std::forward<Args>(args)...);
    }

    const T& operator*() const noexcept
    {
        return fKey;
    }

    TernaryTree& operator[](size_t aIndex) const
    {
        assert(aIndex <= 2);

        return *fNodes[aIndex];
    }

    void add(size_t aIndex, Node& aNode)
    {
        assert(aIndex <= 2);
        assert(this != nullptr);
        assert(fNodes[aIndex] == nullptr);
        fNodes[aIndex] = std::move(aNode);
    }

    Node remove(size_t aIndex)
    {
        assert(aIndex <= 2);
        assert(this != nullptr);
        return std::move(fNodes[aIndex]);
    }

    bool leaf() const noexcept
    {
        for (size_t i = 0; i < 3; i++)
        {
            if (fNodes[i] != nullptr)
            {
                return false;
            }
        }
        return true;
    }

    size_t height() const noexcept
    {
        assert(this != nullptr);
        if (leaf())
        {
            return 0;
        }

        size_t leftHeight = fNodes[0] == nullptr ? 0 : fNodes[0]->height();
        size_t middleHeight = fNodes[1] == nullptr ? 0 : fNodes[1]->height();
        size_t rightHeight = fNodes[2] == nullptr ? 0 : fNodes[2]->height();

        return std::max({ leftHeight, middleHeight, rightHeight }) + 1;
    }

private:

    T fKey;
    Node fNodes[3];
};

