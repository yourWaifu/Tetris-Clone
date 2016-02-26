#include "SpeedTimingData.h"


int SpeedTimingData::getIndexFromLevel(int level, unsigned int *data, const size_t numOfLevels, const size_t numOfTypesPlusLevel)
{
	if (level < 0) return 0;
	unsigned int Ulevel = level;	//fixes compiler warning C4018
	unsigned int i = 0;
	while (i < numOfLevels) {
		if (*data <= Ulevel && Ulevel < *(data + numOfTypesPlusLevel))
			return i;
		data += numOfTypesPlusLevel;
		i++;
	}
	return i - 1;	//this is only for the last level
}

Uint32 roundDoubleIntoUInt(double value)
{
	int tenthsValue = ((Uint64)(value * 10) % 10);
	if (tenthsValue < 5) return (Uint32)value;
	else if (5 < tenthsValue) return (Uint32)value + 1;
	else {
		if ((Uint64)value % 2 == 0)
			return (Uint32)value;
		else
			return (Uint32)value + 1;
	}
}

Uint32 InternalGravity::getRawDataFromLevel(int level) {
	return (*data)[getIndexFromLevel(level, **data, numOfLevels, numOfTypesPlusLevel)][1];
}
double InternalGravity::getConvertedDataFromLevel(Uint64 frequency, int level) {
	return (1.0 / ((double)getRawDataFromLevel(level) / (double)NUM_OF_GSLICES_IN_ONE_G)) * ((double)frequency / 60.0);
}

Uint32 InternalGravity::getRoundedAndConvertedDataFromLevel(Uint64 frequency, int level)
{
	return roundDoubleIntoUInt(getConvertedDataFromLevel(frequency, level));
}

int Delays::getRawDataFromLevel(int level, Type type) {
	return (*data)[getIndexFromLevel(level, **data, numOfLevels, numOfTypesPlusLevel)][type];
};
double Delays::getConvertedDataFromLevel(Uint64 frequency, int level, Type type) {
	return (double)getRawDataFromLevel(level, type) * ((double)frequency / 60.0);
}

Uint32 Delays::getRoundedAndConvertedDataFromLevel(Uint64 frequency, int level, Type type)
{
	return roundDoubleIntoUInt(getConvertedDataFromLevel(frequency, level, type));
}
