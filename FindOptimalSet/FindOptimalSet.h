#pragma once

#include <iostream>
#include <vector>
#include <cstdint>
#include <set>

namespace FindOptimalSet
{
	class optimal_set_finder
	{
	public:
		optimal_set_finder();
		~optimal_set_finder();

		void find_largest_sum(uint64_t T, const std::vector<uint64_t>& I, std::vector<uint64_t>& M, uint64_t& S);

	private:
		void find_optimal_set_recursive(uint64_t T, uint64_t& S, std::vector<uint64_t>& M, const std::set<uint64_t>::iterator& it, const std::set<uint64_t>& elements);
	};
}	