#include "external_sort.hpp"
#include <catch.hpp>

SCENARIO("Very small", "[sort_very_small_file]") {
	external_sort("random_very_small.txt", "output_very_small.txt", 64);

	std::ifstream expected("expected_very_small.txt");
	std::ifstream output("output_very_small.txt");
	std::string first, second;
	
	bool flag = true;

	while (expected || output) {
		std::getline(expected, first);
		std::getline(output, second);
		if (first != second) {
			flag = false;
			break;
		}
	}

	expected.close();
	output.close();
	
	REQUIRE(flag);
}

SCENARIO("Small", "[sort_small_file]") {
	external_sort("random_small.txt", "output_small.txt", 64 * 1024);

	std::ifstream expected("expected_small.txt");
	std::ifstream output("output_small.txt");
	std::string first, second;
	
	bool flag = true;

	while (expected || output) {
		std::getline(expected, first);
		std::getline(output, second);
		if (first != second) {
			flag = false;
			break;
		}
	}

	expected.close();
	output.close();
	
	REQUIRE(flag);
}

SCENARIO("Medium", "[sort_medium_file]") {
	external_sort("random_medium.txt", "output_medium.txt", 1024 * 1024 * 4);

	std::ifstream expected("expected_medium.txt");
	std::ifstream output("output_medium.txt");
	std::string first, second;
	
	bool flag = true;

	while (expected || output) {
		std::getline(expected, first);
		std::getline(output, second);
		if (first != second) {
			flag = false;
			break;
		}
	}

	expected.close();
	output.close();
	
	REQUIRE(flag);
}
