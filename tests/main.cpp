//#define CATCH_CONFIG_MAIN
//#include <catch.hpp>
#include <clocale>

int main(int argc, char* argv[]) {
  setlocale(LC_ALL, "");
	if (argc == 4) {
    if (static_cast<std::string>(argv[1]) == "gen") {		
        gen_file(static_cast<std::string>(argv[2]), std::stoul(static_cast<std::string>(argv[3])));
	      std::cout << "File succesfully generated" << std::endl;
      }
    else {
		  external_sort(static_cast<std::string>(argv[1]), static_cast<std::string>(argv[2]), std::stoi(argv[3]) * 1024 * 1024);
		  std::cout << "File succesfully sorted" << std::endl;
    }
	}
	else {
		std::cout << "Input: external_sort.exe %input_filename% %output_filename% %size_of_piece%" << std::endl;
		std::cout << "Or to generate random filled file: external_sort.exe gen %filename% %size in bytes%" << std::endl;
	}
	return 0;
}
