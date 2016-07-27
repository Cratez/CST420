#include "rider.h"




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
	if (stage < 0 || stage > mTimes.size) {
		//error....
	}
	else if (stage == 0) {
		//accumulate the sum of the vector
	}
	else {
		return mTimes.at(stage);
	}
}

const vector<int>& Rider::getTimes() const
{
	return mTimes;
}
