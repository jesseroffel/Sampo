#pragma once
// General include header that contains most functionality for any client application using Sampo // 
#include "sampo/core/core_definitions.hpp"

#include "sampo/core/application.hpp"
#include "sampo/core/layer.hpp"
#include "sampo/core/log.hpp"
#include "sampo/core/timestep.hpp"

#include "sampo/events/event.hpp"

// TODO - Add optional includes when not rendering
#include "sampo/graphics/renderer.hpp"
#include "sampo/graphics/render_command.hpp"

#include "sampo/graphics/buffer.hpp"
#include "sampo/graphics/shader.hpp"
#include "sampo/graphics/texture.hpp"
#include "sampo/graphics/vertex_array.hpp"
#include "sampo/graphics/camera.hpp"

#include "sampo/input/input.hpp"
#include "sampo/input/gamepad.hpp"
#include "sampo/input/orthographic_camera_controller.hpp"