#include "rider.h"
#include <numeric>

string Rider::getName() const
{
	return mName;
}

string Rider::getCountry() const
{
	return mCountry;
}

string Rider::getTeam() const
{
	return mTeam;
}

int Rider::getTime(int stage) const
{
	if ((int)stage < 0 || (size_t)stage > mTimes.size()) {
		return 0;
		//error....
	}
	else if (stage == 0) {
		return accumulate(mTimes.begin(), mTimes.end(), 0);
	}
	else {
		return mTimes.at(stage - 1);
	}
	return 0;
}

const vector<int>& Rider::getTimes() const
{
	return mTimes;
}
