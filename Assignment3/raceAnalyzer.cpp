#include "raceAnalyzer.h"
#include "istream_getline_iterator.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <sstream>

string sToLower(const string & str)
{
	string lowStr = str;
	transform(lowStr.begin(),
		lowStr.end(),
		lowStr.begin(),
		::tolower);
	return lowStr;
}

RaceAnalyzer::RaceAnalyzer(const string & stageFilename, const string & riderFilename)
{
	//==========================================read and generate stage info==========================================
	ifstream stageFile(stageFilename);
	if (!stageFile.is_open())
		throw fileOpenFailure_;
	copy(istream_iterator<double>(stageFile), istream_iterator<double>(), back_inserter(mStageDistances));

	//==========================================read and generate rider info==========================================
	ifstream riderFile(riderFilename);
	if (!riderFile.is_open())
		throw fileOpenFailure_;
	vector<Rider>& mRiderRef = mRiders; //apparently need this trick to ref into lambda
	vector<string> riderLines;			//lines from the rider file

	//read in the rider file
	copy(istream_getline_iterator(riderFile), istream_getline_iterator(), back_inserter(riderLines));

	//loop over each element and create riders
	for_each(riderLines.begin(), riderLines.end(),[&mRiderRef](string line)
	{
		stringstream sin(line);
		string name, country, team;
		vector<int> times;

		sin >> name >> country >> team;
		copy(istream_iterator<int>(sin), istream_iterator<int>(), back_inserter(times));

		//push the new rider onto the vector
		mRiderRef.push_back(Rider(name, country, team, times));
	});
}

size_t RaceAnalyzer::numStages() const
{
	return (size_t)mStageDistances.size();
}

string RaceAnalyzer::getTeam(const string & riderName) const
{
	const Rider* riderP = getRider(riderName);
	return riderP != NULL ? riderP->getTeam() : ""; //TODO: Error?
}

string RaceAnalyzer::getCountry(const string & riderName) const
{
	const Rider* riderP = getRider(riderName);
	return riderP != NULL ? riderP->getCountry() : ""; //TODO: Error?
}

RaceAnalyzer::StrSet RaceAnalyzer::riders() const
{
	StrSet riderSet;
	transform(mRiders.begin(), mRiders.end(), riderSet.begin(), [](const Rider& rider) {return rider.getName(); });
	return riderSet;
}

RaceAnalyzer::StrSet RaceAnalyzer::teams() const
{
	StrSet teamSet;
	transform(mRiders.begin(), mRiders.end(), teamSet.begin(), [](const Rider& rider) {return rider.getTeam(); });
	return teamSet;
}

RaceAnalyzer::StrSet RaceAnalyzer::countries() const
{
	StrSet countrySet;
	transform(mRiders.begin(), mRiders.end(), countrySet.begin(), [](const Rider& rider) {return rider.getTeam(); });
	return countrySet;
}

RaceAnalyzer::Results RaceAnalyzer::riderResults(unsigned stage, const string & team, const string & country) const
{
	return Results();
}

Seconds RaceAnalyzer::teamTime(const string & teamName, unsigned stage, unsigned numRiders) const
{
	return Seconds();
}

RaceAnalyzer::MPH RaceAnalyzer::calcMPH(Seconds seconds, unsigned stage) const
{
	return MPH();
}

const Rider* RaceAnalyzer::getRider(const string & name) const
{
	//get name to lower to ensure match on case difference
	string lowName = sToLower(name);
	auto it = find_if(mRiders.begin(), mRiders.end(), [&lowName](const Rider& rider) {
		return sToLower(rider.getName()) == lowName;
	});

	//return pointer to rider
	return it == mRiders.end() ? &(*it) : NULL;
}


