#pragma once

class Command {
public:
    virtual ~Command() {}
    virtual void execute(float dt) = 0;
};
