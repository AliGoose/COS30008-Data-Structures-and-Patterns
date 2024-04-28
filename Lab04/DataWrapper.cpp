#include "DataWrapper.h"
#include <iostream>
#include <fstream>
#include <cassert>

DataWrapper::DataWrapper(): //constructor used to initalise values
	fSize(0), //currently we have 0 maps
	fData(nullptr) //we can use nullptr to point to a null address
{}

DataWrapper::~DataWrapper() //'~' is used to denote a deconstructor
{
	delete[] fData;
}

bool DataWrapper::load(const std::string& aFileName)
{
	bool Result = false;
	std::ifstream lInput(aFileName, std::ifstream::in);
	if (lInput) //if stream was able to read file, continue
	{
		if (lInput >> fSize) //if statement that reads the first line and assigns it to fSize. So in this case fSize = 1050
		{
			fData = new DataMap[fSize]; //create new DataMap array with the size of 1050

			for (size_t i = 0; i < fSize; i++) //for each iteration, add the key value pair to the DataMap
			{
				lInput >> fData[i];
			}

			Result = true;
		}
		lInput.close();
	}
	return Result;
}

size_t DataWrapper::size() const noexcept
{
	return fSize; //the souce files has access to the private member variables of the header file
}

const DataMap& DataWrapper::operator[](size_t aIndex) const
{
	assert(aIndex < fSize);

	return fData[aIndex];
}