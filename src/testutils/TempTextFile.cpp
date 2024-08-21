#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>

#include <testutils/TempDir.hpp>
#include <testutils/TempTextFile.hpp>

const char* kTempTextFileTemplate = "/TempTextFileXXXXXX";

TempTextFile::TempTextFile(TempDir& tempDir, const char* fileContent) {
  // Temporary directory file path
  tempFilePath = new char[std::strlen(tempDir.GetPath()) + std::strlen(kTempTextFileTemplate) + 1];
  assert(tempFilePath != nullptr);

  // Populate tempFilePath
  char* result;
  result = std::strcpy(tempFilePath, tempDir.GetPath());
  assert(result != nullptr);
  result = std::strcat(tempFilePath, kTempTextFileTemplate);
  assert(result != nullptr);

  // Create temporary directory
  int fileDescriptor = mkstemp(tempFilePath);
  assert(fileDescriptor != -1);

  // Open the file write the content
  std::ofstream ofs(tempFilePath);
  assert(ofs.is_open());
  ofs << fileContent;
  ofs.close();

  this->tempFilePath = tempFilePath;
}

TempTextFile::~TempTextFile() {
  // Deallocate file name
  delete[] this->tempFilePath;
}

const char* TempTextFile::GetPath() const {
  return this->tempFilePath;
}
