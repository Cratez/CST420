#ifndef RIDER_H
#define RIDE_H
#include <string>
#include <vector>

using namespace std;

class Rider
{
public:
	//const bool IsStub;
	Rider::Rider(const string& name, const string& country, const string& team, const vector<int>& times) :
		mName(name),
		mCountry(country),
		mTeam(team),
		mTimes(times)
	{}

	string getName() const;
	string getCountry() const;
	string getTeam() const;
	int getTime(int stage) const;
	const vector<int>& getTimes() const;

private:
	const string mName, mCountry, mTeam;
	const vector<int> mTimes;
};

#endif