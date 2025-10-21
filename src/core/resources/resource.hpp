#pragma once
#include <filesystem>
#include "core/object/object.hpp"

class Resource : public Class<Resource, Object> {
    std::filesystem::path path_;

public:
    explicit Resource(std::filesystem::path path) : path_(std::move(path)) {
    }

    [[nodiscard]] const std::filesystem::path &getPath() const;
};
