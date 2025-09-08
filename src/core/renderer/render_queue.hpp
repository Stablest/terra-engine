#pragma once
#include <vector>

struct DrawCommand;

class RenderQueue {
    std::vector<DrawCommand> commands_;
public:
    void submit(const DrawCommand& command);
    void clear();
    void sort();
    [[nodiscard]] const std::vector<DrawCommand>& getCommands() const;
};
