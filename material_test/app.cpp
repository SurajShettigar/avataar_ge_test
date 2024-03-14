#include "app.hpp"

#include "globals.hpp"

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

}

void App::render() {
    m_renderer.render(m_aspect_ratio);
}

void App::lateUpdate() {

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
            int width = 0;
            int height = 0;
            glfwGetFramebufferSize(m_curr_window, &width, &height);
            m_aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
            update();

            glViewport(0, 0, width, height);

            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            render();

            glfwSwapBuffers(m_curr_window);
            glfwPollEvents();

            lateUpdate();
        }
    }
    clean();
    return status;
}
