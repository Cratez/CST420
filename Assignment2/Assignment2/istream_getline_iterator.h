#ifndef ISTREAM_GETLINE_ITER
#define ISTREAM_GETLINE_ITER

#include <iterator>
#include <string>
#include <iostream>
class istream_getline_iterator: 
	public std::iterator<std::input_iterator_tag, std::string>
{
public:
	//Ctors
	istream_getline_iterator(std::istream& is);
	istream_getline_iterator();

	//operators
	std::string operator*();
	istream_getline_iterator& operator++();
	bool operator==(const istream_getline_iterator& rhs) const;
	bool operator!=(const istream_getline_iterator& rhs) const;

private:
	std::istream* m_is; //stream to be read from
	std::string m_line; //current line
	void readLine();
};

#endif
