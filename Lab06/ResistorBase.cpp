#include "ResistorBase.h";

ResistorBase::ResistorBase(double aBaseValue) noexcept :
	fBaseValue(aBaseValue)
{
	//setBaseValue(aBaseValue);
};

void ResistorBase::setBaseValue(double aBaseValue) noexcept
{
	fBaseValue = aBaseValue;
}

double ResistorBase::getBaseValue() const noexcept
{
	return fBaseValue;
}

double ResistorBase::getPotentialAt(double aCurrent, double aFrequency) const noexcept
{
	return aCurrent * getReactance(aFrequency);
}

double ResistorBase::getCurrentAt(double aVoltage, double aFrequency) const noexcept
{
	return aVoltage / getReactance(aFrequency);
}

std::istream& operator>>(std::istream& aIStream, ResistorBase& aObject)
{
	double lRawValue;
	std::string lRawUnit;

	aIStream >> lRawValue >> lRawUnit;

	aObject.convertUnitValueToBaseValue(lRawValue, lRawUnit);

	return aIStream;
}

std::ostream& operator<<(std::ostream& aOStream, const ResistorBase& aObject)
{
	double lRawValue;
	std::string lRawUnit;

	aObject.convertBaseValueToUnitValue(lRawValue, lRawUnit);

	aOStream << lRawValue << lRawUnit;

	return aOStream;
}
