#ifndef MATERIAL_TEST_APP_HPP
#define MATERIAL_TEST_APP_HPP

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "renderer.hpp"

class App {
public:
    explicit App(int argc, char **argv) {};

    ~App() { clean(); };

    // Disable copy
    App(const App &app) = delete;

    App &operator=(const App &app) = delete;

    int run();

private:
    GLFWwindow *m_curr_window = nullptr;

    int32_t m_width = 0;
    int32_t m_height = 0;
    bool m_mouse_clicked = false;

    Renderer m_renderer = Renderer{};

    int init();

    void update();

    void render();

    void lateUpdate();

    void clean();
};


#endif //MATERIAL_TEST_APP_HPP
