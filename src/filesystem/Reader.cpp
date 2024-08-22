#include <filesystem/Reader.hpp>
#include <fstream>
#include <sstream>

std::string filesystem::ReadTextFile(const std::string& filePath) {
	std::ifstream ifs;

	// Throw exception on failure
	ifs.exceptions(std::ifstream::badbit | std::ifstream::failbit);

	try {
		// Try opening the file
		ifs.open(filePath);

		// Take ifs stream buffer and move the contents of the buffer to stringstream
		// Basically read the whole file content
		std::ostringstream oss;
		oss << ifs.rdbuf();

		// Return file contents
		return oss.str();
	} catch(std::ifstream::failure& e) {
		std::ostringstream errorMsg;
		errorMsg << "Error: Could not read file " << filePath << " " << e.what();

		throw std::runtime_error(errorMsg.str());
	}
}
