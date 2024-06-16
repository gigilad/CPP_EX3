#ifndef RESOURCE_HPP
#define RESOURCE_HPP
#include <string>
#include <vector>
enum class Resource {WOOD, BRICK, WOOL, OATS ,IRON, DESERT, NONE};

std::string resourceToString(Resource type);

#endif