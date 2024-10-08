#pragma once

#include "shader_program.hpp"
#include "buffer.hpp"
#include "vertex_array.hpp"
#include "GLFW/glfw3.h"

#include <cmath>
#include <utility>
#include <vector>


#include "transform.hpp"
#include <spdlog/spdlog.h>

namespace Inferonix::Renderer
{
    struct render_entity_data
    {
        std::vector<float> vertices;
        std::vector<int> indices;
        transform transform{};
        bool dynamically_colored;

        virtual ~render_entity_data() = default;

        virtual void update(float delta_time){}

    };

    struct render_entity
    {
        std::unique_ptr<shader_program> ShaderProgram;
        std::unique_ptr<vertex_array> VertexArray;
        std::unique_ptr<vertex_buffer> VertexBuffer;
        std::unique_ptr<index_buffer> IndexBuffer;

        std::shared_ptr<render_entity_data> RenderEntityData;


        render_entity() = default;
        ~render_entity() = default;

        render_entity(const render_entity&) = delete;
        render_entity& operator=(const render_entity&) = delete;

        render_entity(render_entity&&) = default;
        render_entity& operator=(render_entity&&) = default;
    };


    class renderer
    {
    public:
        renderer();
        ~renderer() = default;
        void render();
        void add_render_entity(const std::shared_ptr<render_entity_data>& data);
        static void set_clear_color(float r, float g, float b, float a);
        static void clear();
        static void log_info();
        static std::shared_ptr<render_entity> create_render_entity(std::shared_ptr<render_entity_data>);

    private:
        std::vector<std::shared_ptr<render_entity>> _render_entities;

    };
}
