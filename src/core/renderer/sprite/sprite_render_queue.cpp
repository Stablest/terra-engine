#include "sprite_render_queue.hpp"

#include <algorithm>

void SpriteRenderQueue::submit(const SpriteDrawCommand &command) {
    command.sortKey_ = command.texture_;
    commands_.push_back(command);
}

void SpriteRenderQueue::clear() {
    commands_.clear();
}

void SpriteRenderQueue::sort() {
    std::ranges::sort(commands_, [](const SpriteDrawCommand &a, const SpriteDrawCommand &b) {
        return a.sortKey_ < b.sortKey_;
    });
}

const std::vector<SpriteDrawCommand> &SpriteRenderQueue::getCommands() const {
    return commands_;
}
