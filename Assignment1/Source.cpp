#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>
#include <unordered_map>
#include "console_graphics.h"

using namespace std;

class TextToggle {
private:
	string m_text;
	bool m_toggle;
public:
	TextToggle(string text) : m_toggle(false), m_text(text) {};

	void toggle() {
		m_toggle = !m_toggle;
		if (m_toggle) {
			printText(m_text.c_str(), 0, 80 - m_text.length());
		}
		else {
			drawBlock(0, 80 - m_text.length(), 1, m_text.length(), BLACK);
		}
	}
};

void main()
{
	unordered_map<string, bool> map;
	vector<string> dictionary, reducedDict;
	ifstream filestream;
	string filename, input;
	bool foundAnagram = false;
	TextToggle tt("Working...");


	//cin >> filename;
	filename = "dictionary.txt";
	filestream.open(filename);

	//costly initial copy in, opted against initsize
	copy(istream_iterator<string>(filestream), istream_iterator<string>(), back_inserter(dictionary));

	//loop asking for input
	while (cout << "Search for anagrams for: " && cin >> input) {	
		//copy values of matching size into reduced dict to search over
		copy_if(dictionary.begin(), dictionary.end(), back_inserter(reducedDict), [input](string s) {return (s.length() == input.length() && s != input); });

		//binary search for value
		if (binary_search(dictionary.begin(), dictionary.end(), input)) {//verify the value is in the dict

			sort(input.begin(), input.end());//sort for initial anagram searchs
			do {//loop over iterations
				if (binary_search(reducedDict.begin(), reducedDict.end(), input)) {
					cout << input << " ";
					foundAnagram = true;
				}
			}	
			while (next_permutation(input.begin(), input.end()));

			//break line or output no anagrams message
			if (!foundAnagram) {
				cout << "No anagrams were found!" << endl;
			}
			else
				cout << endl;
			
		}
		else {
			cout << input << " is not a valid word!" << endl;
		}

		//clear for next loop
		foundAnagram = false;
		reducedDict.clear();
	}
	/*sort(test.begin(), test.end());
	do
		cout << test << endl;
	while (next_permutation(test.begin(), test.end()));
	cin.ignore();
	cin.get();*/
	//string filename;
	//ifstream fileStream;

	////open file
	//cout << "Please enter doctionary file: ";
	//cin >> filename;
	//fileStream.open(filename);

	////File open error handling
	//while (!fileStream.is_open()) {
	//	cout << "File did not open. Please try another file: ";
	//	cin >> filename;
	//	fileStream.open(filename);
	//}

	//fileStream.close();
}
//
//vector<string> dictionary(INIT_DICT_SIZE);
//ifstream filestream;
//string filename, input;
////cin >> filename;
////filename = "dictionary.txt";
//filestream.open(filename);
//
//copy(istream_iterator<string>(filestream), istream_iterator<string>(), dictionary.begin());//back_inserter(dictionary));
//
//while (true) {
//	if (cin >> input && find(dictionary.begin(), dictionary.end(), input) != dictionary.end()) {
//		sort(input.begin(), input.end());
//		do {
//			if (find(dictionary.begin(), dictionary.end(), input) != dictionary.end())
//				cout << input << " ";
//		} while (next_permutation(input.begin(), input.end()));
//		cout << endl;
//	}
//}