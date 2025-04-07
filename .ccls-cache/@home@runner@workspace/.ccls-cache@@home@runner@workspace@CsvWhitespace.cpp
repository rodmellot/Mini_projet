#include <string>
#include <fstream> // pour ifstream
#include <sstream> // pour istringstream
#include <locale> // pour ctype, mask, locale
#include <iostream>
#include <vector>

#include "CsvWhitespace.h"

CsvWhitespace::CsvWhitespace(std::size_t refs):
	ctype(make_table(), false, refs)
{}

const CsvWhitespace::mask* CsvWhitespace::make_table()
{
	static std::vector<CsvWhitespace::mask> v(classic_table(), classic_table() + table_size);
	for (CsvWhitespace::mask& m : v) {
		m &= ~space;
	}
	v[';'] |= space;
	v['\n'] |= space;
	return v.data();
}
