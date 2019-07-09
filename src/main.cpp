#include <unistd.h>
#include <getopt.h>

#include <string>
#include <vector>
#include <iostream>

void parseCmd(int argc, char *argv[]);

int main(int argc, char *argv[]) {
	parseCmd(argc, argv);
}

void printUsage(std::string className) {
	std::cout << "Usage: " << className << " [-option] class [args...]" << std::endl;
}

void parseCmd(int argc, char *argv[]) {
	using std::string;

	bool helpFlag = false;
	bool versionFlag = false;
	string cp;
	int opt;

	struct option long_options[] = {
		{"help", no_argument, NULL, 'h'},
		{"version", no_argument, NULL, 'v'},
		{"cp", required_argument, NULL, 'c'},
		{"classpath", required_argument, NULL, 'c'},
		{0, 0, 0, 0}
	};
	const char *optionString = "h";
	int option_index = 0;
	
	while ( (opt = getopt_long_only(argc, argv, optionString, long_options, &option_index)) != -1 ) {
		std::cout << "optind:" << optind << std::endl;

		switch(opt) {
			case 'h':
				helpFlag = true;
				std::cout << "help Flag\n";
				break;
			case 'v':
				versionFlag = true;
				std::cout << "vertionFlag\n";
				break;
			case 'c':
				cp = string(optarg);
				std::cout << "cp " << cp << std::endl;
				break;
			default:
				printUsage(argv[0]);
		}

	}
	std::cout << "helpFlag=" << helpFlag << ", versionFlag=" << versionFlag << ", cp=" << cp << std::endl;
	std::cout << "optind:" << optind << std::endl;
	
	if (optind < argc) {
		string mainClass(argv[optind++]);
		std::cout << "main class:" << mainClass << std::endl;
		std::vector<string> args;
		for (int i = optind; i < argc; ++i) {
			args.push_back(string(argv[i]));
			std::cout << "args[" << i-optind << "]=" << args[i - optind] << std::endl;
		}
	} else {
		printUsage(argv[0]);
	}
}
