#ifndef _filesystem_hpp_
#define _filesystem_hpp_

#include <string>
#include <structures/FloatArray.hpp>

namespace filesystem {
	std::string ReadTextFile(const std::string& filePath);
	FloatArray* ReadFloatArray(const std::string& filePath);
}

#endif