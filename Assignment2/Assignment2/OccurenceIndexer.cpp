#include "OccurenceIndexer.h"

void OccurenceIndexer::addOccurence(const string & word, int page, int line)
{
	m_data[word].push_back(make_pair(page, line));
}

const vector<pair<int, int>>& OccurenceIndexer::getOccurences(const string & word)
{
	return m_data[word];
}

void OccurenceIndexer::printOccurences(const string & word)
{
	const vector<pair<int, int>>& myVect = m_data[word];
	if (myVect.size() > 0) {
		cout << word << endl << "  ";

		bool first = true;
		for (pair<int, int> occurence : myVect) {
			if (!first) cout << ", "; else first = false;
			cout << occurence.first << "." << occurence.second;
		}
		cout << endl;
	}
}

void OccurenceIndexer::printOccurences()
{
	for (pair<string, vector<pair<int, int>>> var : m_data)
	{
		printOccurences(var.first);
	}
}
