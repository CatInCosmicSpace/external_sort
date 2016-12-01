#include "external_sort.hpp"
#include <catch.hpp>
#include <chrono>

SCENARIO("file - 8 mb, memory - 1 mb", "[8 - 1]") {
	auto begin = std::chrono::high_resolution_clock::now();
	external_sort("8", "sorted8", 1024 * 1024);
	auto end = std::chrono::high_resolution_clock::now();
	auto res = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
	std::cout << "8 mb time: " << res << std::endl;
	std::ifstream output_first("sorted8"), output_second("sorted8");
	data first, second;
	bool flag = true;
	bool check = false;
	output_second >> first.last_name >> first.first_name >> first.year;
	while (output_second) {
		output_first >> first.last_name >> first.first_name >> first.year;
		output_second >> second.last_name >> second.first_name >> second.year;
		if (!output_second) {
			check = true;
			break;
		}
		if (!(first <= second)) {
			output_first.close();
			output_second.close();
			flag = false;
			break;
		}
	}

	REQUIRE(flag);
	REQUIRE(check);
	REQUIRE(res);
}

SCENARIO("file - 15 mb, memory - 4 mb", "[15 - 4]") {
	auto begin = std::chrono::high_resolution_clock::now();
	external_sort("15", "sorted15", 4 * 1024 * 1024);
	auto end = std::chrono::high_resolution_clock::now();
	auto res = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
	std::cout << "15 mb time: " << res << std::endl;
	std::ifstream output_first("sorted15"), output_second("sorted15");
	data first, second;
	bool flag = true;
	bool check = false;
	output_second >> first.last_name >> first.first_name >> first.year;
	while (output_second) {
		output_first >> first.last_name >> first.first_name >> first.year;
		output_second >> second.last_name >> second.first_name >> second.year;
		if (!output_second) {
			check = true;
			break;
		}
		if (!(first <= second)) {
			output_first.close();
			output_second.close();
			flag = false;
			break;
		}
	}

	REQUIRE(flag);
	REQUIRE(check);
	REQUIRE(res);
}

SCENARIO("file - 32 mb, memory - 17 mb", "[32 - 17]") {
	auto begin = std::chrono::high_resolution_clock::now();
	external_sort("32", "sorted32", 1024 * 1024);
	auto end = std::chrono::high_resolution_clock::now();
	auto res = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
	std::cout << "32 mb time: " << res << std::endl;
	std::ifstream output_first("sorted32"), output_second("sorted32");
	data first, second;
	bool flag = true;
	bool check = false;
	output_second >> first.last_name >> first.first_name >> first.year;
	while (output_second) {
		output_first >> first.last_name >> first.first_name >> first.year;
		output_second >> second.last_name >> second.first_name >> second.year;
		if (!output_second) {
			check = true;
			break;
		}
		if (!(first <= second)) {
			output_first.close();
			output_second.close();
			flag = false;
			break;
		}
	}

	REQUIRE(flag);
	REQUIRE(check);
	REQUIRE(res);
}