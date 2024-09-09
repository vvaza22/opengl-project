#pragma once

#include <string>
#include <structures/FloatArray.hpp>
#include <mesh/MeshBuilder.hpp>

namespace filesystem {
	std::string ReadTextFile(const std::string& filePath);
	FloatArray* ReadFloatArray(const std::string& filePath);
	MeshBuilder* ReadObject(const std::string& filePath);
}
