#include <cassert>
#include <cstdlib>
#include <cstring>

#include <filesystem> // C++17

#include <testutils/TempDir.hpp>

const char* kTempDirTemplate = "/tmp/TestTempDirXXXXXX";

TempDir::TempDir() {
  // Temporary directory file path
  tempDirPath = strdup(kTempDirTemplate);
  assert(tempDirPath != nullptr);

  // Create temporary directory
  char* result = mkdtemp(tempDirPath);
  assert(result != nullptr);

  this->tempDirPath = tempDirPath;
}

TempDir::~TempDir() {
  // Remove temporary directory
  std::filesystem::remove_all(this->tempDirPath);
  // Deallocate directory name
  std::free(this->tempDirPath);
}

const char* TempDir::GetPath() const {
  return this->tempDirPath;
}
