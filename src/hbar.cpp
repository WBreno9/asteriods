#include <hbar.h>

HBar::HBar(glm::vec2 barSize_) : barSize(barSize_)
{
    pos = glm::vec2(0.0f);
    rotation = 0.0f;
    visible = false;

    Update();
}

void HBar::Update()
{
    vertices.clear();
    vertices.push_back(glm::vec2(barSize.x * percent , barSize.y));
    vertices.push_back(glm::vec2(barSize.x * percent, -barSize.y));
    vertices.push_back(glm::vec2(-barSize.x * percent, -barSize.y));
    vertices.push_back(glm::vec2(-barSize.x * percent, barSize.y));
    vertices.push_back(vertices[0]);

    UpdateMatrix();
}