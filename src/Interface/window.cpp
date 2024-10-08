#include "window.hpp"
#include "callback_functions.hpp"

#include <stdexcept>
#include "spdlog/spdlog.h"
#include <glad/glad.h>

using namespace Inferonix::Interface;

window::window(int width, int height) :
    _width{ width },
    _height{ height }
{
    create();
    _initialized = true;
}

window::~window()
{ }

void window::init()
{
    _initialized = glfwInit();
    if(!_initialized)
        throw std::runtime_error("GLFW initialization failed!");

    spdlog::info("GLFW was initialized successfully"); // todo

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
}

void window::create()
{
    init();
    _instance = glfwCreateWindow(_width, _height, "Engine", nullptr, nullptr);

	if (_instance == nullptr)
	{
		spdlog::error("Error while creating window");
		this->destroy();
		return;
	}

    spdlog::info("Window was created successfully");

	glfwMakeContextCurrent(_instance);
    glfwSetFramebufferSizeCallback(_instance, framebuffer_size_callback);

    // After making context, glad is going to be initialized:
	// maybe assertion?! from return value of gladLL (int)
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc> (glfwGetProcAddress)))
	{
		throw std::runtime_error("Error while initializing GLAD");
    }

}

bool window::should_close() const
{
    return glfwWindowShouldClose(_instance);
}

void window::poll_events()
{
    glfwPollEvents();
}

void window::swap_buffers()
{
    glfwSwapBuffers(_instance);
}

void window::destroy()
{
    glfwTerminate();
    _instance = nullptr;
}

GLFWwindow& window::get()
{
    return *_instance;
}

bool window::key_pressed(int key)
{
    return glfwGetKey(_instance, key);
}

void window::close()
{
    glfwSetWindowShouldClose(_instance, GLFW_TRUE);
}

