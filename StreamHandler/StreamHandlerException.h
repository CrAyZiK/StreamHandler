#pragma once

#include <exception>

class median_of_empty_list_exception :public std::exception {
	virtual const char* what() const throw() {
		return "Attempt to take the median of an empty list of numbers.  "
			"The median of an empty list is undefined.";
	}
};

class median_of_list_with_even_number_of_elements_exception :public std::exception {
	virtual const char* what() const throw() {
		return "Attempt to take the median of list with an even number of elements.  "
			"The median of of list with an even number of elements isn't implemented.";
	}
};

class compute_block_on_empty_stream_exception :public std::exception {
	virtual const char* what() const throw() {
		return "Attempt to compute block on an empty stream.";
	}
};

class rule_not_exist_exception :public std::exception {
	virtual const char* what() const throw() {
		return "Rule isn't exist for the given device type.";
	}
};

class no_parameters_received_for_device_exception :public std::exception {
	virtual const char* what() const throw() {
		return "No parameters received for the device.";
	}
};

class handmade_nth_element_k_out_of_range_exception :public std::exception {
	virtual const char* what() const throw() {
		return "k out of rannge in handmade_nth_element.";
	}
};