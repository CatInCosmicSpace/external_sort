#include <clocale>
#include "external_sort.h"

int main(int argc, char* argv[]) {
	if (argc == 4) {
		setlocale(LC_ALL, "");
		// You can change 512 to other number in Mb
		external_sort(static_cast<std::string>(argv[1]), static_cast<std::string>(argv[2]), std::stoi(argv[3]));
		std::cout << "File succesfully sorted" << std::endl;
	}
	else if (argc == 4 && static_cast<std::string>(argv[1]) == "gen") {
		gen_file(static_cast<std::string>(argv[2]), std::stoul(static_cast<std::string>(argv[3])));
		std::cout << "File succesfully generated" << std::endl;
	}
	else {
		std::cout << "Input: external_sort.exe %input_filename% %output_filename% %size_of_piece%" << std::endl;
		std::cout << "Or to generate random filled file: external_sort.exe gen %filename% %size in bytes%" << std::endl;
	}
	return 0;
}
