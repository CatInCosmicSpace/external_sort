#include "external_sort.hpp"
#include <catch.hpp>

SCENARIO("file - 8 mb, memory - 1 mb", "[8 - 1]") {
	external_sort("8", "sorted8", 1024 * 1024);

	std::ifstream output_first("sorted8"), output_second("sorted8");
	data first, second;
	bool flag = true;
	output_second >> first.last_name >> first.first_name >> first.year;
	while (output_second) {
		output_first >> first.last_name >> first.first_name >> first.year;
		output_second >> second.last_name >> second.first_name >> second.year;
		if (!output_second) break;
		if (!(first <= second)) {
			output_first.close();
			output_second.close();
			flag = false;
			break;
		}
	}

	REQUIRE(flag);
}

SCENARIO("file - 15 mb, memory - 4 mb", "[15 - 4]") {
	external_sort("15", "sorted15", 4 * 1024 * 1024);

	std::ifstream output("sorted15");
	data first, second;
	bool flag = true;
	output >> first.last_name >> first.first_name >> first.year;
	while (output) {
		output >> second.last_name >> second.first_name >> second.year;
		if (!output) break;
		if (!(first < second)) {
			flag = false;
			break;
		}
		first = second;
	}

	REQUIRE(flag);
}

SCENARIO("file - 32 mb, memory - 17 mb", "[32 - 17]") {
	external_sort("15", "sorted15", 17 * 1024 * 1024);

	std::ifstream output("sorted32");
	data first, second;
	bool flag = true;
	output >> first.last_name >> first.first_name >> first.year;
	while (output) {
		output >> second.last_name >> second.first_name >> second.year;
		if (!output) break;
		if (!(first < second)) {
			flag = false;
			break;
		}
		first = second;
	}

	REQUIRE(flag);
}
