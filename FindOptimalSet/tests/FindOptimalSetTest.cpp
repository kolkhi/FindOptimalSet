#include "..\FindOptimalSet.h"
#include "..\TestCasesLoader.h"

#define BOOST_TEST_MODULE FindOptimalSet
#include <boost/test/included/unit_test.hpp>

using namespace std;
using namespace FindOptimalSet;

struct test_cases_fixture
{
	test_cases_loader loader;

	test_cases_fixture()
	{
		auto testCasesFile = "test.txt";

		// if test file name if passed as an argument to the testing executable, use it
		if (boost::unit_test::framework::master_test_suite().argc == 2)
		{
			testCasesFile = boost::unit_test::framework::master_test_suite().argv[1];
		}

		try
		{
			loader.load_test_cases(testCasesFile);
		}
		catch (std::exception& ex)
		{
			BOOST_ERROR("Error loading test cases: " + string(ex.what()));
		}
	}

	~test_cases_fixture()
	{
	}

	bool is_valid()
	{
		return loader.get_test_cases().size() > 0;
	}
};

BOOST_AUTO_TEST_SUITE(optimal_set_finder_test)

BOOST_FIXTURE_TEST_CASE(test_cases, test_cases_fixture)
{
	BOOST_REQUIRE(is_valid());
	optimal_set_finder set_finder;
	auto testCases = loader.get_test_cases();
	for each (auto& test in testCases)
	{
		auto [T, I, S] = test;

		vector<uint64_t> result_set;
		uint64_t result_s;

		set_finder.find_largest_sum(T, I, result_set, result_s);

		BOOST_REQUIRE_EQUAL(result_s, S);

		auto is_sorted = std::is_sorted(result_set.begin(), result_set.end());
		BOOST_REQUIRE_EQUAL(is_sorted, true);

		uint64_t result_set_sum = 0;
		for each (auto & val in result_set)
		{
			result_set_sum += val;
		}

		BOOST_REQUIRE_EQUAL(result_s, result_set_sum);
	}
}

BOOST_AUTO_TEST_CASE(test_when_input_vector_is_empty)
{
	optimal_set_finder set_finder;

	vector<uint64_t> result_set;
	uint64_t result_s;
	set_finder.find_largest_sum(0, vector<uint64_t>(), result_set, result_s);

	BOOST_REQUIRE_EQUAL(result_s, 0);
	BOOST_REQUIRE_EQUAL(result_set.size(), 0);

}

BOOST_AUTO_TEST_CASE(test_when_input_vector_sum_is_less_or_equal_to_input_number)
{
	optimal_set_finder set_finder;

	uint64_t t = 5000;
	vector<uint64_t> input{ 100, 1, 20, 34, 100 };
	vector<uint64_t> result_set;
	uint64_t result_s;
	set_finder.find_largest_sum(t, input, result_set, result_s);

	set<uint64_t> unique_elements;
	unique_elements.insert(input.begin(), input.end());
	uint64_t sum = 0;
	for each (auto & uint64_t in unique_elements)
	{
		sum += uint64_t;
	}

	BOOST_REQUIRE_EQUAL(result_s, sum);
	BOOST_CHECK_EQUAL_COLLECTIONS(result_set.begin(), result_set.end(), unique_elements.begin(), unique_elements.end());
}

BOOST_AUTO_TEST_CASE(test_when_input_number_is_less_then_input_vector_minimum)
{
	optimal_set_finder set_finder;

	uint64_t t = 2;
	vector<uint64_t> input{ 40, 20, 200, 100 };
	vector<uint64_t> result_set;
	uint64_t result_s;

	set_finder.find_largest_sum(t, input, result_set, result_s);

	BOOST_REQUIRE_EQUAL(result_s, 0);
	BOOST_REQUIRE_EQUAL(result_set.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()