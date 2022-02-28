#include "TestCasesLoader.h"
#include <sstream>

using namespace std;
using namespace FindOptimalSet;

test_cases_loader::test_cases_loader()
{
}

test_cases_loader::~test_cases_loader()
{
}

void test_cases_loader::load_test_cases(const string& testCasesFile)
{
	ifstream testFileStream(testCasesFile, std::ios::in);
	if (!testFileStream.is_open())
	{
		throw runtime_error("Can't open test cases file " + testCasesFile);
	}

	while (testFileStream)
	{
		uint64_t input_value;
		if (!read_input_value(testFileStream, input_value))
			break;

		vector<uint64_t> input_vector;
		if (!read_input_vector(testFileStream, input_vector))
			break;

		uint64_t expected_value;
		if (!read_expected_value(testFileStream, expected_value))
			break;

		testCases.push_back(make_tuple(input_value, input_vector, expected_value));
		if (!testFileStream)
			break;

		string empty_line;
		getline(testFileStream, empty_line);
	}

	testFileStream.close();
}

const std::vector<std::tuple<uint64_t, std::vector<uint64_t>, uint64_t>>& test_cases_loader::get_test_cases() const
{
	return testCases;
}

bool test_cases_loader::read_input_value(istream& testFileStream, uint64_t& T)
{
	if (!testFileStream)
		return false;

	string input_value;
	getline(testFileStream, input_value);

	stringstream str_stream(input_value);
	str_stream >> T;

	return true;
}

bool test_cases_loader::read_input_vector(istream& testFileStream, vector<uint64_t>& I)
{
	if (!testFileStream)
		return false;

	string input_vector_str;
	getline(testFileStream, input_vector_str);

	stringstream str_stream(input_vector_str);
	uint64_t val;
	while (str_stream >> val)
		I.push_back(val);

	return true;
}

bool test_cases_loader::read_expected_value(istream& testFileStream, uint64_t& S)
{
	if (!testFileStream)
		return false;

	string expected_value_str;
	getline(testFileStream, expected_value_str);

	stringstream str_stream(expected_value_str);
	str_stream >> S;

	return true;
}