
// COS30008, tutorial 4, 2023

#pragma once

#include <istream>
#include <ostream>

template<typename Key, typename Value>
class Map
{
private:
    Key fKey;
    Value fValue;
    
public:
    Map( const Key& aKey = Key{}, const Value& aValue = Value{}) noexcept: //Default values are empty arrays for implicit conversion constructor
        fKey(aKey),
        fValue(aValue)
    {}

    const Key& key() const noexcept { return fKey; } //return the private member variable
    const Value& value() const noexcept { return fValue; }
    
    template<typename U>
    operator U() const noexcept
    {
        return static_cast<U>(fValue);//static casting the fValue to a U.
    }
    
    friend std::istream& operator>>(std::istream& aIStream, Map& aMap)
    {
        return aIStream >> aMap.fKey >> aMap.fValue;
    }

    friend std::ostream& operator<<(std::ostream& aOStream, const Map& aMap)
    {
        return aOStream << "{" << aMap.fKey << ", " << aMap.fValue << "}";
    }
};
