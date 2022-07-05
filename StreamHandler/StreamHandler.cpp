#include "pch.h"
#include "framework.h"

#include "StreamHandler.h"
#include "StreamHandlerException.h"

namespace StreamHandler {
	Processing::Processing() {
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

	uint8_t Processing::handmade_sum_of_parameters(std::vector<uint8_t> parameters) {
		uint8_t result = 0;
		for (auto item : parameters) result = (uint8_t)(result + item);
		return result;
	}

	uint8_t Processing::product_of_parameters(std::vector<uint8_t> parameters) {
		return std::accumulate(parameters.begin(), parameters.end(), 1, std::multiplies<uint8_t>());
	}

	uint8_t Processing::handmade_product_of_parameters(std::vector<uint8_t> parameters) {
		uint8_t result = 1;
		for (auto item : parameters) result = (uint8_t)(result * item);
		return result;
	}

	uint8_t Processing::max_of_parameters(std::vector<uint8_t> parameters) {
		return *std::max_element(parameters.begin(), parameters.end());
	}

	uint8_t Processing::handmade_max_of_parameters(std::vector<uint8_t> parameters) {
		uint8_t result = parameters[0];
		for (auto item : parameters) result = result > item ? result : item;
		return result;
	}

	uint8_t Processing::min_of_parameters(std::vector<uint8_t> parameters) {
		return *std::min_element(parameters.begin(), parameters.end());
	}

	uint8_t Processing::handmade_min_of_parameters(std::vector<uint8_t> parameters) {
		uint8_t result = parameters[0];
		for (auto item : parameters) result = result < item ? result : item;
		return result;
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
				parameters.push_back((uint8_t)std::stoi(parameter.c_str()));
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

	uint8_t Processing::median(std::vector<uint8_t> r_stream) {
		size_t size = r_stream.size();

		if (size == 0) throw median_of_empty_list_exception();
		if (size % 2 == 0)  throw median_of_list_with_even_number_of_elements_exception();

		size /= 2;
		std::nth_element(r_stream.begin(), r_stream.begin() + size, r_stream.end());

		return r_stream[size];
	}

	uint8_t Processing::handmade_median(std::vector<uint8_t> r_stream) {
		size_t size = r_stream.size();

		if (size == 0) throw median_of_empty_list_exception();
		if (size == 1) return r_stream[0];
		if (size % 2 == 0)  throw median_of_list_with_even_number_of_elements_exception();

		size /= 2;
		handmade_nth_element(r_stream, 0, size, r_stream.size()-1);

		return r_stream[size];
	}

	uint8_t Processing::handmade_nth_element(std::vector<uint8_t> vec, int first, int k, int last) {
		if (k < 0 || k >= last - first + 1) throw handmade_nth_element_k_out_of_range_exception();
		auto i = partition(vec, first, last);
		if (i - first == k - 1) return vec[i];
		if (i - first > k - 1) return handmade_nth_element(vec, first, k, i - 1);
		return handmade_nth_element(vec, i + 1, k - i + first - 1, last);
	}

	int Processing::partition(std::vector<uint8_t> vec, int first, int last) {
		auto x = vec[last];
		auto i = first;
		uint8_t tmp;
		for (auto j = first; j <= last - 1; ++j) {
			if (vec[j] <= x) {
				tmp = vec[i];
				vec[i] = vec[j];
				vec[j] = tmp;
				++i;
			}
		}
		tmp = vec[i];
		vec[i] = vec[last];
		vec[last] = tmp;
		return i;
	}
}
