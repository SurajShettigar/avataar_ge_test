#include "app.hpp"

#include "globals.hpp"
#include <iostream>

int App::init() {
    if (glfwInit()) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        m_curr_window = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_NAME.c_str(),
                                         nullptr, nullptr);
        if (m_curr_window == nullptr)
            return 1;

        glfwMakeContextCurrent(m_curr_window);
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
            return 1;

        if (!m_renderer.init())
            return 2;
        return 0;
    }
    return 1; // Non-zero status code indicates failure
}

void App::update() {
    int state = glfwGetKey(m_curr_window, GLFW_KEY_ESCAPE);
    if (state == GLFW_PRESS) {
        glfwSetWindowShouldClose(m_curr_window, 1);
    }

    state = glfwGetMouseButton(m_curr_window, GLFW_MOUSE_BUTTON_1);
    if (state == GLFW_PRESS && !m_mouse_clicked) {
        double x_pos, y_pos;
        glfwGetCursorPos(m_curr_window, &x_pos, &y_pos);
        m_renderer.update(x_pos, y_pos);
        m_mouse_clicked = true;
    }
}

void App::render() {
    m_renderer.render(m_width, m_height);
}

void App::lateUpdate() {
    int state = glfwGetMouseButton(m_curr_window, GLFW_MOUSE_BUTTON_1);
    m_mouse_clicked = state == GLFW_PRESS;
}

void App::clean() {
    m_renderer.clean();
    if (m_curr_window != nullptr) {
        glfwDestroyWindow(m_curr_window);
        m_curr_window = nullptr;
    }
    glfwTerminate();
}

int App::run() {
    int status = init();
    if (!status) {
        while (!glfwWindowShouldClose(m_curr_window)) {
            glfwPollEvents();
            update();

            glfwGetFramebufferSize(m_curr_window, &m_width, &m_height);

            glViewport(0, 0, m_width, m_height);
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            render();

            glfwSwapBuffers(m_curr_window);

            lateUpdate();
        }
    }
    clean();
    return status;
}
