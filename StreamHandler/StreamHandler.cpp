#include "pch.h"
#include "framework.h"

#include "StreamHandler.h"
#include "StreamHandlerException.h"

namespace StreamHandler {
	Processing::Processing(int W):MAX_QUEUE_SIZE(W) {
		if (W<3 || W>1000001 || W%2 == 0) throw wrong_queue_size_exception();
		rules = {
			{(uint8_t)1, Processing::sum_of_parameters},
			{(uint8_t)2, Processing::product_of_parameters},
			{(uint8_t)3, Processing::max_of_parameters},
			{(uint8_t)4, Processing::min_of_parameters}
		};
	}
	uint8_t Processing::sum_of_parameters(std::vector<uint8_t> parameters) {
		return std::accumulate(parameters.begin(), parameters.end(), decltype(parameters)::value_type((uint8_t)0));
	}

	uint8_t Processing::product_of_parameters(std::vector<uint8_t> parameters) {
		return std::accumulate(parameters.begin(), parameters.end(), 1, std::multiplies<uint8_t>());
	}


	uint8_t Processing::max_of_parameters(std::vector<uint8_t> parameters) {
		return *std::max_element(parameters.begin(), parameters.end());
	}

	uint8_t Processing::min_of_parameters(std::vector<uint8_t> parameters) {
		return *std::min_element(parameters.begin(), parameters.end());
	}

	std::vector<uint8_t> Processing::compute_blocks(const std::string blocks) {
		std::istringstream block_stream(blocks);
		std::vector<uint8_t> result = {};
		std::string block;

		while (std::getline(block_stream, block)) {
			std::vector<uint8_t> parameters;
			std::string parameter;
			std::istringstream params(block);
			while (std::getline(params, parameter, ' ')) {
				parameters.push_back((uint8_t)std::stoi(parameter));
			}
			uint8_t device_type;
			if (parameters.size() > 1) {
				device_type = parameters[0];
				parameters.erase(parameters.begin());
				if (rules.count(device_type)) {
					result.push_back(rules[device_type](parameters));
				} else {
					throw rule_not_exist_exception();
				}
			} else {
				throw no_parameters_received_for_device_exception();
			}
		}

		if (result.size() < 1) throw compute_block_on_empty_stream_exception();

		return result;
	}

	void Processing::push(uint8_t element) {
		if (queue.size() == MAX_QUEUE_SIZE) {
			queue_item_count[queue.front()] -= 1;
			queue.pop();
		}
		queue.push(element);
		queue_item_count[element] += 1;
	}
	void Processing::push(std::vector<uint8_t> elements) {
		for (auto item : elements) push(item);
	}
	bool Processing::queue_is_full() { return queue.size() == MAX_QUEUE_SIZE; }

	uint8_t Processing::median() {
		if (queue.size() < MAX_QUEUE_SIZE) throw median_on_not_full_queue_exception();
		int median_index = MAX_QUEUE_SIZE / 2 + 1;
		int i = 0;
		uint8_t item = (uint8_t)0;
		for (; item < 256;++item) {
			i += queue_item_count[item];
			if (i >= median_index) {
				break;
			}
		}
		return item;
	}
}
