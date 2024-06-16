#include "Resource.hpp"

std::string resourceToString(Resource type){
    switch (type)
    {
    case Resource::WOOD: return "WOOD";
    case Resource::WOOL: return "WOOL";
    case Resource::BRICK: return "BRICK";
    case Resource::OATS: return "OATS";
    case Resource::IRON: return "IRON";
    case Resource::DESERT: return "DESERT";
    default: return "NONE";

    }
}