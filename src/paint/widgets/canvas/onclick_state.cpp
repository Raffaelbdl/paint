#include "canvas.h"

bool OnClickState::ShouldExit()
{
    // Exit if mouse up
    return !ImGui::IsMouseDown(ImGuiMouseButton(0));
}