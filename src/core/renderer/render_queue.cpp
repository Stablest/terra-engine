#include "render_queue.hpp"
#include <algorithm>
#include "renderer.hpp"

void RenderQueue::submit(const DrawCommand &command) {
    command.sortKey_ = (static_cast<uint64_t>(command.shader_) << 32) | command.texture_;
    commands_.push_back(command);
}

void RenderQueue::clear() {
    commands_.clear();
}

void RenderQueue::sort() {
    std::ranges::sort(commands_, [](const DrawCommand &a, const DrawCommand &b) {
        return a.sortKey_ < b.sortKey_;
    });
}

const std::vector<DrawCommand> &RenderQueue::getCommands() const {
    return commands_;
}
