#include "texture_loader.hpp"
#include <vector>
#include "texture_resource.hpp"
#include "misc/error/error.hpp"
#include "stb/stb_image.h"

bool ImageLoader::canLoad(const std::string &extension) {
    return extension == ".png" || extension == ".jpg" || extension == ".jpeg";
}

std::unique_ptr<Resource> ImageLoader::load(const std::filesystem::path &filePath) {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(false);
    unsigned char *data = stbi_load(filePath.string().c_str(), &width, &height, &channels, 0);
    if (!data) {
        handleWarningError("TEXTURE_LOADER::LOADING_DATA_FAILED");
        return nullptr;
    }
    const size_t bufferSize = static_cast<size_t>(width) * height * channels;
    const std::vector<unsigned char> buffer(data, data + bufferSize);
    auto resource = TextureResource{width, height, channels, filePath.string(), buffer};
    stbi_image_free(data);
    return std::make_unique<TextureResource>(resource);
}

std::unique_ptr<Resource> ImageLoader::getFallback() {
    constexpr int size = 4;
    constexpr int channels = 3;
    std::vector<unsigned char> buffer(size * size * channels);
    for (int i = 0; i < size * size; i++) {
        buffer[i * channels + 0] = 255;
        buffer[i * channels + 1] = 255;
        buffer[i * channels + 2] = 255;
    }
    auto resource = TextureResource{size, size, channels, "fallback/texture", buffer};
    return std::make_unique<TextureResource>(resource);
}
