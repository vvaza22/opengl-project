#ifndef _TempTextFile_
#define _TempTextFile_

#include <testutils/TempDir.hpp>

class TempTextFile {
public:
  TempTextFile(TempDir& tempDir, const char* fileContent);
  ~TempTextFile();
  const char* GetPath() const;
private:
  char* tempFilePath;
};

#endif