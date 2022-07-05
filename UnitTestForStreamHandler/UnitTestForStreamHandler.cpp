#include "pch.h"
#include "CppUnitTest.h"
#include "StreamHandler.h"
#include <StreamHandlerException.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestForStreamHandler
{
	TEST_CLASS(UnitTestForStreamHandler)
	{
	public:
		

		TEST_METHOD(TestRCalculationMethods)
		{
			std::vector<uint8_t> test_parameters{1,2,3,4,5,8,243};
			Assert::AreEqual(StreamHandler::Processing::sum_of_parameters(test_parameters), 
				StreamHandler::Processing::handmade_sum_of_parameters(test_parameters),
				L"Wrong sum of parameters.");
			Assert::AreEqual(StreamHandler::Processing::product_of_parameters(test_parameters), 
				StreamHandler::Processing::handmade_product_of_parameters(test_parameters),
				L"Wrong product of parameters.");
			Assert::AreEqual(StreamHandler::Processing::max_of_parameters(test_parameters), 
				StreamHandler::Processing::handmade_max_of_parameters(test_parameters),
				L"Wrong max of parameters.");
			Assert::AreEqual(StreamHandler::Processing::min_of_parameters(test_parameters), 
				StreamHandler::Processing::handmade_min_of_parameters(test_parameters),
				L"Wrong min of parameters.");
		}

		TEST_METHOD(TestComputeBlock)
		{
			std::string test_block("1 5 6\n2 8 6 5\n3 6 7 8 7 8 9 123\n1 5 5\n1 6 5\n2 7 7 7\n3 6 7 8 7 5 5\n4 6 7 8 7 5 5");
			std::vector<uint8_t> test_r_stream{11, 240, 123, 10, 11, 87, 8, 5};
			uint8_t test_median = 11;
			auto sh = StreamHandler::Processing();
			auto r_stream = sh.compute_blocks(test_block);

			Assert::AreEqual(test_r_stream.size(), r_stream.size(), 
				L"Block parsing failure in compute_block.");

			for (int i = 0; i < test_r_stream.size(); ++i) Assert::AreEqual(test_r_stream[i], r_stream[i], 
				L"Test Rs and aren't equal with compute_block result.");


			Assert::ExpectException<compute_block_on_empty_stream_exception>([&sh] {sh.compute_blocks(""); }, 
				L"compute_block_on_empty_stream_exception was expected.");

			Assert::ExpectException<no_parameters_received_for_device_exception>([&sh] {sh.compute_blocks("1"); },
				L"no_parameters_received_for_device_exception was expected.");

			Assert::ExpectException<rule_not_exist_exception>([&sh] {sh.compute_blocks("5 1 2 34"); },
				L"rule_not_exist_exception was expected.");

			Assert::ExpectException<std::invalid_argument>([&sh] {sh.compute_blocks("1 s d f"); },
				L"std::invalid_argument was expected.");
		}

		TEST_METHOD(TestMedian)
		{
			std::vector<uint8_t> r_stream{ 11, 240, 123, 10, 11, 87, 8, 5 };

			Assert::ExpectException<median_of_list_with_even_number_of_elements_exception>([&r_stream] {StreamHandler::Processing::median(r_stream); },
				L"median_of_list_with_even_number_of_elements_exception was expected.");

			r_stream = { 11, 240, 123, 10, 11, 87, 8, 5 };
			Assert::ExpectException<median_of_list_with_even_number_of_elements_exception>([&r_stream] {StreamHandler::Processing::handmade_median(r_stream); },
				L"median_of_list_with_even_number_of_elements_exception was expected.");

			r_stream = { 240, 123, 10, 11, 87, 8, 5 };
			uint8_t test_median = 11;

			auto median = StreamHandler::Processing::median(r_stream);

			Assert::AreEqual(test_median, median,
				L"Wrong meadian.");

			r_stream = { 240, 123, 10, 11, 87, 8, 5 };
			median = StreamHandler::Processing::handmade_median(r_stream);

			Assert::AreEqual(test_median, median,
				L"Wrong meadian.");


			Assert::ExpectException<median_of_empty_list_exception>([&r_stream] {StreamHandler::Processing::median({}); },
				L"median_of_empty_list_exception was expected.");

			Assert::ExpectException<median_of_empty_list_exception>([&r_stream] {StreamHandler::Processing::handmade_median({}); },
				L"median_of_empty_list_exception was expected.");
			
			median = StreamHandler::Processing::handmade_median({11});
			Assert::AreEqual(test_median, median,
				L"Wrong meadian.");

		}
	};
}
