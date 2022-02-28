#include "FindOptimalSet.h"
#include "TestCasesLoader.h"

using namespace std;
using namespace FindOptimalSet;

void run_test_cases(const test_cases_loader& loader)
{
	optimal_set_finder set_finder;
	auto testCases = loader.get_test_cases();
	for each (auto& test in testCases)
	{
		auto [T, I, S] = test;

		vector<uint64_t> result_set;
		uint64_t result_s;

		set_finder.find_largest_sum(T, I, result_set, result_s);

		uint64_t result_set_sum = 0;
		for each (auto & val in result_set)
		{
			cout << val << " ";
		}

		if (result_set.size() == 0)
			cout << "<empty>";

		cout << endl << endl;
	}
}

int main(int argc, char** argv)
{
	auto testCasesFile = "test.txt";

	// if test file name if passed as an argument to the testing executable, use it
	if (argc == 2)
	{
		testCasesFile = argv[1];
	}

	test_cases_loader loader;
	try
	{
		loader.load_test_cases(testCasesFile);
		run_test_cases(loader);
	}
	catch (std::exception& ex)
	{
		cout << "Error loading test cases: " + string(ex.what());
	}
}