#include <iostream>
#include <set>
#include <vector>
#include <utility>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <sstream>
#include "istream_getline_iterator.h"
#include "OccurenceIndexer.h"

using namespace std;

string stripPunct(string text) 
{
	text.erase(
		std::remove_if(text.begin(), text.end(), ispunct), 
		text.end());
	return text;
}

string& toLower(string& str) {
	//this will blow up with non ascii
	//transform(str.begin(),//src begin
		//str.end(), //src end
		//str.begin(), //dest begin
		//::tolower); //transform
	for_each(str.begin(), str.end(), [](char& c) {c = tolower(c); });
	return str;
}

void processFile(const vector<string>& documentLines, const vector<string>& skipWords, OccurenceIndexer& oIndexer) 
{
	int currentPageNum = 1;
	int currentLineNum = 1;
	for (const string& curLine : documentLines)//int currentLineNum = 0; (unsigned)currentLineNum < documentLines.size(); currentLineNum++) 
	{
		//const string& curLine = documentLines[currentLineNum];
		if (curLine == "<newpage>") {
			//reset to next page
			currentPageNum++;
			currentLineNum = 0;
		}
		else if (curLine != "") {
			vector<string> words(10);//words on the line
			istringstream iss(curLine);//string stream to break appart words

			//break appart lines and store into words
			copy(istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(words));

			//iterate over each word
			for (string word : words) {
				string cWord = stripPunct(word);

				const bool isSkipWord = binary_search(skipWords.begin(), skipWords.end(), cWord);//skipWords.find(word) != skipWords.end();
				if (!isSkipWord) {
					oIndexer.addOccurence(cWord, currentPageNum, currentLineNum);
				}
			}
		}

		//increment line
		currentLineNum++;
	}
}

template <class T>
class To_Lower_Back_Inser : public back_insert_iterator<T> {
public:
	To_Lower_Back_Inser(T type) : back_insert_iterator<T>(type){}

	void operator=()
};

int main()
{
	//data declarations
	string documentPath, skipfilePath;
	ifstream ifstream;
	vector<string> skipWords;
	vector<string> documentLines;
	OccurenceIndexer oIndexer;

	//get the documents
	cout << "Please enter the file names -- <document> <skipfile>: ";
	cin >> documentPath >> skipfilePath;

	//open document and read it in
	ifstream.open(documentPath);
	if (!ifstream.is_open()) {
		cout << "Document File did not open!";
		exit(-1);
	}
	copy(istream_getline_iterator(ifstream), istream_getline_iterator(), back_inserter(documentLines));
	ifstream.close();

	//read in skip words
	ifstream.open(skipfilePath);
	if (!ifstream.is_open()) {
		cout << "Skip File did not open!";
		exit(-2);
	}
	copy(istream_iterator<string>(ifstream),istream_iterator<string>(),back_inserter(skipWords));//inserter(skipWords,skipWords.begin()));
	ifstream.close();

	for (auto& line : documentLines) {
		toLower(line);
	}
	for (auto& sWord : skipWords) {
		toLower(sWord);
	}
	sort(skipWords.begin(),skipWords.end()); //sort skipwords for binary search

	//process the file
	processFile(documentLines, skipWords, oIndexer);
	oIndexer.printOccurences();

	cin.ignore(256, '\n');
	cin.get();

	return 0;
}