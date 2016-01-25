#include "SpeedTimingData.h"

double SpeedTimingData::getDataInUnitOfTimeFromLevel(Uint64 frequency, int level)
{
	return 0;
}

int SpeedTimingData::getIndexFromLevel(int level, unsigned int *data, const size_t numOfLevels, const size_t numOfTypesPlusLevel)
{
	if (level < 0) return 0;
	int i = 0;
	while (i < numOfLevels) {
		if (*data <= level) {
			unsigned int *temp = data + numOfTypesPlusLevel;
			if (level < *temp) return i;
		}
		data += numOfTypesPlusLevel;
		i++;
	}
	return i - 1;	//this is only for the last level
}

Uint64 SpeedTimingData::getRoundedDataInUnitOfTimeFromLevel(Uint64 frequency, int level)
{
	return roundDoubleIntoUInt(getDataInUnitOfTimeFromLevel(frequency, level));
}

Uint64 roundDoubleIntoUInt(double value)
{
	int tenthsValue = ((Uint64)(value * 10) % 10);
	if (tenthsValue < 5) return (Uint64)value;
	else if (5 < tenthsValue) return (Uint64)value + 1;
	else {
		if ((Uint64)value % 2 == 0)
			return (Uint64)value;
		else
			return (Uint64)value + 1;
	}
}

int InternalGravity::getDataFromLevel(int level)
{
	return (*data)[getIndexFromLevel(level, **data, numOfLevels, numOfTypesPlusLevel)][1];
}

double InternalGravity::getDataInUnitOfTimeFromLevel(Uint64 frequency, int level)
{
	return (1.0 / ((double)getDataFromLevel(level) / (double)NUM_OF_GSLICES_IN_ONE_G)) * ((double)frequency / 60.0);
}

int Delays::getDataFromLevel(int level, Type type)
{
	return (*data)[getIndexFromLevel(level, **data, numOfLevels, numOfTypesPlusLevel)][type];
}

double Delays::getDataInUnitOfTimeFromLevel(Uint64 frequency, int level, Type type)
{
	return (double)getDataFromLevel(level, type) * ((double)frequency / 60.0);
}

int Delays::getRoundedDataInUnitOfTimeFromLevel(Uint64 frequency, int level, Type type)
{
	return (int)roundDoubleIntoUInt(getDataInUnitOfTimeFromLevel(frequency, level, type));
}
