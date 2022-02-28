#pragma once
#include <vector>
#include <string>
#include <fstream>

namespace FindOptimalSet
{
	class test_cases_loader
	{
	public:
		test_cases_loader();
		~test_cases_loader();

		void load_test_cases(const std::string& testCasesFile);

		const std::vector<std::tuple<uint64_t, std::vector<uint64_t>, uint64_t>>& get_test_cases() const;

	private:
		bool read_input_value(std::istream& testFileStream, uint64_t& T);
		bool read_input_vector(std::istream& testFileStream, std::vector<uint64_t>& I);
		bool read_expected_value(std::istream& testFileStream, uint64_t& S);

	private:
		std::vector<std::tuple<uint64_t, std::vector<uint64_t>, uint64_t>> testCases;
	};
}