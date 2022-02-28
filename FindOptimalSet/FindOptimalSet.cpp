#include "FindOptimalSet.h"
#include <set>
#include <numeric>
#include <algorithm>

using namespace FindOptimalSet;

optimal_set_finder::optimal_set_finder()
{
}

optimal_set_finder::~optimal_set_finder()
{
}

void optimal_set_finder::find_largest_sum(uint64_t T, const std::vector<uint64_t>& I, std::vector<uint64_t>& M, uint64_t& S)
{
	S = 0;

	// if elements array is empty, set S = 0 and return empty M - it's not possible find a required subset
	if (I.size() == 0) return;

	// store sorted unique elements in set
	std::set<uint64_t> unique_elements;
	unique_elements.insert(I.begin(), I.end());

	// if T is less than the minimum element in the input vector, return S=0, and empty M vectors - it's not possible find a required subset
	auto smallest_element = *(unique_elements.begin());
	if (T < smallest_element)  return;

	// calculate sum of all elements
	uint64_t sum_of_all_elements = 0;
	for each (const uint64_t & el in unique_elements)
	{
		sum_of_all_elements += el;
	}

	// if calculated sum is less or equal to T, return all elements as a required subset
	if (sum_of_all_elements <= T)
	{
		S = sum_of_all_elements;
		M.assign(unique_elements.begin(), unique_elements.end());
		return;
	}

	// find upper_bound of elements, that are <= to T, because elements > T can't be a part of the required subset
	auto foundIt = unique_elements.lower_bound(T);

	// if found value equals to T, return the element as a subset
	if (foundIt != unique_elements.end() && *foundIt == T)
	{
		S = T;
		M.push_back(*foundIt);
		return;
	}

	// find optimal set recursively
	find_optimal_set_recursive(T, S, M, unique_elements.begin(), unique_elements);
}

void optimal_set_finder::find_optimal_set_recursive(uint64_t T, uint64_t& S, std::vector<uint64_t>& M, const std::set<uint64_t>::iterator& it, const std::set<uint64_t>& elements)
{
	auto current_sum = S;
	auto current_set = M;
	for (auto local_it = it; local_it != elements.end(); ++local_it)
	{
		// next value makes the sum greater than input, stop execution
		if (current_sum + *local_it > T)
			break;

		// add next value to the sum
		current_sum += *local_it;
		current_set.push_back(*local_it);

		// if required sum is found, stop execution
		if (current_sum == T)
		{
			S = current_sum;
			M = current_set;
			break;
		}

		// save current sum/set on this step before moving forward
		auto temp_current_sum = current_sum;
		auto temp_current_set = current_set;

		// process next element
		find_optimal_set_recursive(T, current_sum, current_set, std::next(local_it), elements);
		
		// if calculated sum is larger than S, update S and M
		if (current_sum > S)
		{
			S = current_sum;
			M = current_set;

			// if required sum is found, stop execution
			if (S == T)
				break;
		}

		// restore sum/set from the current step
		current_sum = temp_current_sum;
		current_set = temp_current_set;

		// remove current value from the sum/set and proceed to the next
		current_sum -= *local_it;
		current_set.pop_back();
	}
}
