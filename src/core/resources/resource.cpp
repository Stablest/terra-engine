#include "resource.hpp"
#include <filesystem>

const std::filesystem::path &Resource::getPath() const {
    return path_;
}
