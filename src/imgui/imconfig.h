//-----------------------------------------------------------------------------
// USER IMPLEMENTATION
// This file contains compile-time options for ImGui.
// Other options (memory allocation overrides, callbacks, etc.) can be set at runtime via the ImGuiIO structure - ImGui::GetIO().
//-----------------------------------------------------------------------------

#pragma once

#include <SFML/System/Vector2.hpp>

#define IM_VEC2_CLASS_EXTRA                                                 \
        ImVec2(const sf::Vector2f& v) { x = v.x; y = v.y; }                 \
        operator sf::Vector2f() const { return sf::Vector2f(x, y); }