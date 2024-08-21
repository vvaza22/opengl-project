#ifndef _TempDir_
#define _TempDir_

class TempDir {
public:
  TempDir();
  ~TempDir();
  const char* GetPath() const;
private:
  char* tempDirPath;
};

#endif