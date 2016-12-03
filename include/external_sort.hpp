#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <memory>
#include <set>
#include <queue>
#include <array>
#include <functional>

struct data {
	std::string last_name; // probably size 50
	std::string first_name; // probably size 50
	uint16_t year;

	auto operator<(data const & data) const -> bool {
		return  first_name < data.first_name;
	}
	auto operator<=(data const & data) const -> bool {
		return  first_name <= data.first_name;
	}
};

auto external_sort(const std::string && file_name, const std::string && output_name, const uint_fast64_t && memory_size, const size_t exp_size = 65) -> void;

auto gen_file(const std::string file_name, const uint_fast64_t file_size) -> void;

auto to_string(const size_t sz) -> const std::string;

auto external_sort(const std::string && file_name, const std::string && output_name, const uint_fast64_t && memory_size, const size_t exp_size) -> void {
	std::ifstream input(file_name);
	if (input.bad()) {
		throw std::bad_exception();
	}
	size_t subpieces = memory_size / exp_size;

	size_t pieces;
	{
		std::unique_ptr<data[]> data_to_sort(new data[subpieces]);
		for (pieces = 0; input; ++pieces) {
			std::ofstream temp_file(to_string(pieces));
			size_t i;
			for (i = 0; i < subpieces; ++i) {
				input >> data_to_sort[i].last_name >> data_to_sort[i].first_name >> data_to_sort[i].year;
				//std::getline(input, data_to_sort[i]);
				if (!input) {
					break;
				}
			}
			std::sort(data_to_sort.get(), data_to_sort.get() + i, [](const auto & a, const auto & b) {
				return a.first_name < b.first_name;
			});

			for (size_t j = 0; j < i; ++j) {
				temp_file << data_to_sort[j].last_name << " " << data_to_sort[j].first_name << " " << data_to_sort[j].year << "\n";
				//temp_file << data_to_sort[j] << std::endl;
			}
			temp_file.close();
		}
	}
	size_t toDelete = pieces;
	std::ofstream sorted_file(output_name);
	std::vector<std::ifstream *> files;
	std::vector<data> datas;
	for (size_t i = 0; i < pieces; ++i) {
		files.push_back(new std::ifstream());
		(*files[i]).open(to_string(i));
		datas.push_back(data());
	}

	for (size_t i = 0; i < pieces; ++i) {
		(*files[i]) >> datas[i].last_name >> datas[i].first_name >> datas[i].year;
		//std::getline((*files[i]), datas[i]);
	}
	for (int i = 0; i < pieces; ++i) {
		if (!(*files[i])) {
			(*files[i]).close();
			files.erase(files.begin() + i);
			datas.erase(datas.begin() + i);
			--i;
			--pieces;
		}
	}
	while (pieces > 1) {
		size_t minind = 0;
		for (size_t i = 1; i < pieces; ++i) {
			if (datas[i] < datas[minind]) {
				minind = i;
			}
		}
		sorted_file << datas[minind].last_name << " " << datas[minind].first_name << " " << datas[minind].year << "\n";
		(*files[minind]) >> datas[minind].last_name >> datas[minind].first_name >> datas[minind].year;
		//std::getline(*files[minind], datas[minind]);
		if (!(*files[minind])) {
			(*files[minind]).close();
			files.erase(files.begin() + minind);
			datas.erase(datas.begin() + minind);
			--pieces;
		}
	}
	while (*files[0]) {
		sorted_file << datas[0].last_name << " " << datas[0].first_name << " " << datas[0].year << "\n";
		(*files[0]) >> datas[0].last_name >> datas[0].first_name >> datas[0].year;
		//std::getline(*files[0], datas[0]);
	}
	(*files[0]).close();
	files.clear();
	datas.clear();
	sorted_file.close();
	for (size_t i = 0; i < toDelete; ++i) {
		std::remove(to_string(i).c_str());
	}
}


auto gen_file(const std::string file_name, const uint_fast64_t file_size) -> void {
	std::string first_names[] = { "Jake", "Mike", "John", "James", "Carl","Daryl", "Rick", "Sam" };
	std::string last_names[] = { "Shepard", "Sparrow", "Kennedy", "Klain", "Ivanov", "Petrov",
		"McCormick", "White", "Black", "Holmes", "Watson" };
	std::ofstream file;
	file.open(file_name);
	if (file.good()) {
		while (file.tellp() < file_size) {
			file << last_names[rand() % 11].data() << " "
				<< first_names[rand() % 8].data() << " "
				<< 1950 + rand() % 2016 << "\n";
		}
		file.close();
	}
	else {
		throw std::bad_exception();
	}
}

auto to_string(const size_t sz) -> const std::string{
	std::stringstream ss;
ss << sz << ".tmp";

return ss.str();
}
