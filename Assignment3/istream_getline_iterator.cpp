#include "istream_getline_iterator.h"


istream_getline_iterator::istream_getline_iterator(std::istream& is) : m_is(&is)
{
	readLine();
}

istream_getline_iterator::istream_getline_iterator() : m_is(0) { }

std::string istream_getline_iterator::operator*()
{
	return m_line;
}

istream_getline_iterator& istream_getline_iterator::operator++()
{
	readLine();
	return *this;
}

bool istream_getline_iterator::operator==(const istream_getline_iterator& rhs) const
{
	return rhs.m_is == m_is;
}

bool istream_getline_iterator::operator!=(const istream_getline_iterator& rhs) const
{
	return !(*this == rhs);
}

void istream_getline_iterator::readLine() {
	if (m_is && !std::getline(*m_is, m_line)) m_is = 0;
}
