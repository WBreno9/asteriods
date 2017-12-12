#ifndef HBAR_H
#define HBAR_H

#include <entity.h>

class HBar : public Entity
{
public:
    glm::vec2 barSize;
    float percent;

    HBar(glm::vec2 barSize);

    std::string GetTypeString() { return "HBar"; }

    void Update();
};

#endif