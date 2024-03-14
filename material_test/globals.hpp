// Copyright 2024 Suraj Shettigar
// SPDX-License-Identifier: Apache-2.0

#ifndef MATERIAL_TEST_GLOBALS_HPP
#define MATERIAL_TEST_GLOBALS_HPP

#include <cstdint>
#include <limits>
#include <string>
#include <vector>

static const uint32_t INVALID_OPENGL_OBJECT_ID = std::numeric_limits<uint32_t>::max();

// Window Defaults
static const uint16_t DEFAULT_WINDOW_WIDTH = 1280;
static const uint16_t DEFAULT_WINDOW_HEIGHT = 720;
static const std::string DEFAULT_WINDOW_NAME = "Material Test";

// Shader / Material Defaults
static const std::string DEFAULT_SHADER_DIRECTORY = SHADER_DIR;
static const std::string DEFAULT_SHADER_EXTENSION_VERTEX = ".vert";
static const std::string DEFAULT_SHADER_EXTENSION_FRAGMENT = ".frag";
static const std::string DEFAULT_SHADER_NAME = "material_lambert";
static const std::string SHADER_UNIFORM_NAME_TRANSFORM = "transform";

// Model Defaults
static const std::string DEFAULT_MODEL_DIRECTORY = DATA_DIR;
static const std::string MODEL_SPHERE_FILEPATH = DEFAULT_MODEL_DIRECTORY + "/Sphere.obj";

// Camera Defaults
static const float DEFAULT_CAM_ORTHO_SIZE = 3.75f;
static const float DEFAULT_CAM_Z_NEAR = 0.01f;
static const float DEFAULT_CAM_Z_FAR = 20.0f;


static inline float map(float x, float in_min, float in_max, float out_min, float out_max) {
    return out_min + ((x - in_min) * (out_max - out_min) / (in_max - in_min));
}

#endif //MATERIAL_TEST_GLOBALS_HPP
