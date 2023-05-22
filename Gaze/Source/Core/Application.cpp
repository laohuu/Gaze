#include "GazePCH.h"
#include "Application.h"

#include "Core/Log.h"

#include <glad/glad.h>

#include <memory>

namespace Gaze {

    Application *Application::s_Instance = nullptr;

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
        switch (type) {
            case Gaze::ShaderDataType::Float:
                return GL_FLOAT;
            case Gaze::ShaderDataType::Float2:
                return GL_FLOAT;
            case Gaze::ShaderDataType::Float3:
                return GL_FLOAT;
            case Gaze::ShaderDataType::Float4:
                return GL_FLOAT;
            case Gaze::ShaderDataType::Mat3:
                return GL_FLOAT;
            case Gaze::ShaderDataType::Mat4:
                return GL_FLOAT;
            case Gaze::ShaderDataType::Int:
                return GL_INT;
            case Gaze::ShaderDataType::Int2:
                return GL_INT;
            case Gaze::ShaderDataType::Int3:
                return GL_INT;
            case Gaze::ShaderDataType::Int4:
                return GL_INT;
            case Gaze::ShaderDataType::Bool:
                return GL_BOOL;
        }

        GZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    Application::Application() {
        GZ_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(GZ_BIND_EVENT_FN(OnEvent));
        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        GZ_CORE_INFO("OpenGL Info:");
        GZ_CORE_INFO("GL_VENDOR: {0}", (char *) glGetString(GL_VENDOR));
        GZ_CORE_INFO("GL_RENDERER: {0}", (char *) glGetString(GL_RENDERER));
        GZ_CORE_INFO("GL_VERSION: {0}", (char *) glGetString(GL_VERSION));

        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);

        float vertices[3 * 7] = {
                -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
                0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
                0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        {
            BufferLayout layout = {
                    {ShaderDataType::Float3, "a_Position"},
                    {ShaderDataType::Float4, "a_Color"}
            };

            m_VertexBuffer->SetLayout(layout);
        }

        uint32_t index = 0;
        const auto &layout = m_VertexBuffer->GetLayout();
        for (const auto &element: layout) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                                  element.GetComponentCount(),
                                  ShaderDataTypeToOpenGLBaseType(element.Type),
                                  element.Normalized ? GL_TRUE : GL_FALSE,
                                  layout.GetStride(),
                                  (const void *) element.Offset);
            index++;
        }

        uint32_t indices[3] = {0, 1, 2};
        m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

        std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0f);
			}
		)";

        std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5f + 0.5f, 1.0f);
				color = v_Color;
			}
		)";

        m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
    }

    Application::~Application() {

    }

    void Application::PushLayer(Layer *layer) {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *layer) {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }


    void Application::OnEvent(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(GZ_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(GZ_BIND_EVENT_FN(Application::OnWindowResize));

        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
            if (e.Handled)
                break;
            (*it)->OnEvent(e);
        }
    }

    void Application::Run() {
        WindowResizeEvent e(1280, 720);
        if (e.IsInCategory(EventCategoryApplication)) {
            GZ_TRACE(e.ToString());
        }
        while (m_Running) {
            glClearColor(1.0f, 0.5f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->Bind();

            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

            for (Layer *layer: m_LayerStack)
                layer->OnUpdate();

            m_ImGuiLayer->Begin();
            for (Layer *layer: m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent &e) {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent &e) {
        if (e.GetWidth() == 0 || e.GetHeight() == 0) {
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;
        return false;
    }

} // Gaze