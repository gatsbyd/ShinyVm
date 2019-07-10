#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>

#include <string>
#include <vector>
#include <iostream>


struct cmd {
	bool helpFlag;
	bool versionFlag;
	std::string cp;
	std::string className;
	std::vector<std::string> args;
	
	cmd() :helpFlag(false), versionFlag(false) {}
};

cmd parseCmd(int argc, char *argv[]);
void printUsage(std::string className);
void startJVM(const cmd&);

int main(int argc, char *argv[]) {
	cmd cmd;

	cmd = parseCmd(argc, argv);
	if (cmd.helpFlag) {
		printUsage(argv[0]);
	} else if (cmd.versionFlag) {
		std::cout << "version 0.0.1\n";
	} else {
		startJVM(cmd);		
	}
}

void printUsage(std::string className) {
	std::cout << "Usage: " << className << " [-option] class [args...]" << std::endl;
}

cmd parseCmd(int argc, char *argv[]) {
	using std::string;

	cmd cmd;
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
		switch(opt) {
			case 'h':
				cmd.helpFlag = true;
				break;
			case 'v':
				cmd.versionFlag = true;
				break;
			case 'c':
				cmd.cp = string(optarg);
				break;
			default:
				printUsage(argv[0]);
				exit(1);
		}

	}
	
	if (optind < argc) {
		cmd.className = string(argv[optind++]);
		for (int i = optind; i < argc; ++i) {
			cmd.args.push_back(string(argv[i]));
		}
	}
	return cmd;
}

void startJVM(const cmd& cmd) {
	std::cout << "start jvm\n";
	std::cout << "helpFlag=" << cmd.helpFlag << ", versionFlag=" << cmd.versionFlag << ", cp=" << cmd.cp
			<< ", class=" << cmd.className << ", args=";
	for (const std::string& s: cmd.args) {
		std::cout << s << " ";
	}
	std::cout << std::endl;
}
