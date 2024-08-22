#ifndef _ModelFactory_
#define _ModelFactory_

#include <model/Model.hpp>
#include <string>

class ModelFactory {
public:
  Model* CreateModel(const std::string& path);
};

#endif