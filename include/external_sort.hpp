#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <memory>


struct data {
	std::string last_name;
	std::string first_name;
	uint16_t year;
	
	auto operator<(data const & data) const -> bool {
		return  std::make_pair(last_name, first_name)
			<   std::make_pair(data.last_name, data.first_name);
	}
	auto operator<=(data const & data) const -> bool {
		return      std::make_pair(static_cast<std::string>(last_name), static_cast<std::string>(first_name))
			<=   std::make_pair(static_cast<std::string>(data.last_name), static_cast<std::string>(data.first_name));
	}
};

auto external_sort(const std::string && file_name, const std::string && output_name, const uint_fast64_t && memory_size) -> void;

auto gen_file(const std::string file_name, const uint_fast64_t file_size) -> void;

auto to_string(const size_t sz) -> const std::string;

auto external_sort(const std::string && file_name, const std::string && output_name, const uint_fast64_t && memory_size) -> void {
	std::ifstream input(file_name);
	if (input.bad()) {
		throw std::bad_exception();
	}
	size_t subpieces = memory_size / 105;

	size_t pieces;
	{
		std::unique_ptr<std::string[]> data_to_sort(new std::string[subpieces]);
		for (pieces = 0; input; ++pieces) {
			std::ofstream temp_file(to_string(pieces));
			size_t i;
			for (i = 0; i < subpieces; ++i) {
				std::getline(input, data_to_sort[i]);
				if (!input) {
					break;
				}
			}
			std::sort(data_to_sort.get(), data_to_sort.get() + i, [](const auto & a, const auto & b) {
				return a < b;
			});

			for (size_t j = 0; j < i; ++j) {
				temp_file << data_to_sort[j] << std::endl;
			}
			temp_file.close();
		}
	}
	size_t toDelete = pieces;
	std::ofstream sorted_file(output_name);
	std::vector<std::ifstream *> files;
	std::vector<std::string> datas;
	for (size_t i = 0; i < pieces; ++i) {
		files.push_back(new std::ifstream());
		(*files[i]).open(to_string(i));
		datas.push_back(std::string());
	}

	for (size_t i = 0; i < pieces; ++i) {
		std::getline((*files[i]), datas[i]);
	}
	for (int i = 0; i < pieces; ++i)
		if (!(*files[i])) {
			(*files[i]).close();
			files.erase(files.begin() + i);
			datas.erase(datas.begin() + i);
			--i;
			--pieces;
		}
	while (pieces > 1) {
		size_t minind = 0;
		for (size_t i = 1; i < pieces; ++i)
			if (datas[i] < datas[minind])
				minind = i;

		sorted_file << datas[minind] << std::endl;
		std::getline(*files[minind], datas[minind]);
		if (!(*files[minind])) {
			(*files[minind]).close();
			files.erase(files.begin() + minind);
			datas.erase(datas.begin() + minind);
			--pieces;
		}
	}
	while (*files[0]) {
		sorted_file << datas[0] << std::endl;
		std::getline(*files[0], datas[0]);
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
