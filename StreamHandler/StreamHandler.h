#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <numeric>

namespace StreamHandler 
{
	class Processing
	{
	public:
		Processing();
		static uint8_t sum_of_parameters(std::vector<uint8_t> parameters);
		static uint8_t handmade_sum_of_parameters(std::vector<uint8_t> parameters);
		static uint8_t product_of_parameters(std::vector<uint8_t> parameters);
		static uint8_t handmade_product_of_parameters(std::vector<uint8_t> parameters);
		static uint8_t max_of_parameters(std::vector<uint8_t> parameters);
		static uint8_t handmade_max_of_parameters(std::vector<uint8_t> parameters);
		static uint8_t min_of_parameters(std::vector<uint8_t> parameters);
		static uint8_t handmade_min_of_parameters(std::vector<uint8_t> parameters);

		std::vector<uint8_t> compute_blocks(const std::string blocks);
		static uint8_t median(std::vector<uint8_t> r_stream);
		static uint8_t handmade_median(std::vector<uint8_t> r_stream);

	private:

		std::map<uint8_t, std::function<uint8_t(std::vector<uint8_t>)>> rules;

		static uint8_t handmade_nth_element(std::vector<uint8_t> vec, int first, int k, int last);
		static int partition(std::vector<uint8_t> vec, int first, int last);

	};
}