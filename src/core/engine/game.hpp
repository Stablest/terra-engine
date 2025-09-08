#pragma once

class IGame {
public:
    virtual ~IGame() = default;
    virtual void create() = 0;
    virtual void update() = 0;
};