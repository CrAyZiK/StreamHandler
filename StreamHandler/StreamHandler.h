#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <queue>

namespace StreamHandler 
{
	class Processing
	{
	public:
		Processing(int W);
		static uint8_t sum_of_parameters(std::vector<uint8_t> parameters);
		static uint8_t product_of_parameters(std::vector<uint8_t> parameters);
		static uint8_t max_of_parameters(std::vector<uint8_t> parameters);
		static uint8_t min_of_parameters(std::vector<uint8_t> parameters);

		std::vector<uint8_t> compute_blocks(const std::string blocks);
		uint8_t median();
		void push(uint8_t element);
		void push(std::vector<uint8_t> elements);
		bool queue_is_full();
	private:
		int MAX_QUEUE_SIZE;

		uint32_t queue_item_count[256] = {0};

		std::queue<uint8_t> queue;
		std::map<uint8_t, std::function<uint8_t(std::vector<uint8_t>)>> rules;
	};
}
