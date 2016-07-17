#ifndef OCCURENCE_INDEXR
#define OCCURENCE_INDEXR

#include <map>
#include <string>
#include <vector>
#include <utility>
#include <set>
#include <iostream>

using namespace std;
class OccurenceIndexer {
	
public:
	//mutator
	void addOccurence(const string& word, int page, int line);

	//inspecter
	const vector<pair<int,int>>& getOccurences(const string& word);

	//print functions
	void printOccurences(const string& word);
	void printOccurences();

private:
	map<string, vector<pair<int, int>>> m_data;
};

#endif