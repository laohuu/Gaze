#include <Gaze.h>
#include "Events/KeyEvent.h"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ExampleLayer : public Gaze::Layer {
public:
    ExampleLayer() : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f) {
        m_VertexArray.reset(Gaze::VertexArray::Create());

        float vertices[3 * 7] = {
                -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
                0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
                0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        Gaze::Ref<Gaze::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(Gaze::VertexBuffer::Create(vertices, sizeof(vertices)));
        Gaze::BufferLayout layout = {
                {Gaze::ShaderDataType::Float3, "a_Position"},
                {Gaze::ShaderDataType::Float4, "a_Color"}
        };
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3] = {0, 1, 2};
        Gaze::Ref<Gaze::IndexBuffer> indexBuffer;
        indexBuffer.reset(Gaze::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_SquareVA.reset(Gaze::VertexArray::Create());

        float squareVertices[5 * 4] = {
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
        };

        Gaze::Ref<Gaze::VertexBuffer> squareVB;
        squareVB.reset(Gaze::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        squareVB->SetLayout({
                                    {Gaze::ShaderDataType::Float3, "a_Position"},
                                    {Gaze::ShaderDataType::Float2, "a_TexCoord"}
                            });
        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        Gaze::Ref<Gaze::IndexBuffer> squareIB;
        squareIB.reset(Gaze::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(squareIB);

        std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
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

        m_Shader.reset(Gaze::Shader::Create(vertexSrc, fragmentSrc));

        std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
			}
		)";

        std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			in vec3 v_Position;

            uniform vec3 u_Color;
			void main()
			{
				color = vec4(u_Color, 1.0f);
			}
		)";

        m_FlatColorShader.reset(Gaze::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

        m_TextureShader.reset(
                Gaze::Shader::Create("C:/Users/hangh/Documents/GitHub/Gaze/Sandbox/Assets/Shaders/Texture.glsl"));

        m_Texture = Gaze::Texture2D::Create(
                "C:/Users/hangh/Documents/GitHub/Gaze/Sandbox/Assets/Textures/Checkerboard.png");

        m_ChernoLogoTexture = Gaze::Texture2D::Create(
                "C:/Users/hangh/Documents/GitHub/Gaze/Sandbox/Assets/Textures/ChernoLogo.png");

        m_TextureShader->Bind();
        m_TextureShader->SetInt("u_Texture", 0);

    };

    virtual ~ExampleLayer() = default;

    void OnAttach() override {};

    void OnDetach() override {};

    void OnUpdate(Gaze::Timestep ts) override {
//        if (Gaze::Input::IsKeyPressed(Gaze::Key::Tab))
//            GZ_TRACE("Tab key is pressed (poll)!");

        if (Gaze::Input::IsKeyPressed(Gaze::Key::Left))
            m_CameraPosition.x -= m_CameraMoveSpeed * ts;
        else if (Gaze::Input::IsKeyPressed(Gaze::Key::Right))
            m_CameraPosition.x += m_CameraMoveSpeed * ts;

        if (Gaze::Input::IsKeyPressed(Gaze::Key::Up))
            m_CameraPosition.y += m_CameraMoveSpeed * ts;
        else if (Gaze::Input::IsKeyPressed(Gaze::Key::Down))
            m_CameraPosition.y -= m_CameraMoveSpeed * ts;

        if (Gaze::Input::IsKeyPressed(Gaze::Key::A))
            m_CameraRotation += m_CameraRotationSpeed * ts;
        if (Gaze::Input::IsKeyPressed(Gaze::Key::D))
            m_CameraRotation -= m_CameraRotationSpeed * ts;

        Gaze::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        Gaze::RenderCommand::Clear();

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        Gaze::Renderer::BeginScene(m_Camera);


        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        m_FlatColorShader->Bind();
        m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);

        for (int y = 0; y < 20; y++) {
            for (int x = 0; x < 20; x++) {
                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                Gaze::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
            }
        }

        m_Texture->Bind();
        Gaze::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        m_ChernoLogoTexture->Bind();
        Gaze::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

//        // Triangle
//        Gaze::Renderer::Submit(m_Shader, m_VertexArray);

        Gaze::Renderer::EndScene();
    };

    void OnImGuiRender() override {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
    };

    void OnEvent(Gaze::Event &event) override {
        if (event.GetEventType() == Gaze::EventType::KeyPressed) {
            auto &e = (Gaze::KeyPressedEvent &) event;
            if (e.GetKeyCode() == Gaze::Key::Tab)
                GZ_TRACE("Tab key is pressed (event)!");

            GZ_TRACE("{0}", (char) e.GetKeyCode());
        }
    };

private:
    Gaze::Ref<Gaze::Shader> m_Shader;
    Gaze::Ref<Gaze::VertexArray> m_VertexArray;

    Gaze::Ref<Gaze::Shader> m_FlatColorShader, m_TextureShader;
    Gaze::Ref<Gaze::VertexArray> m_SquareVA;

    Gaze::Ref<Gaze::Texture2D> m_Texture, m_ChernoLogoTexture;

    Gaze::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 5.0f;

    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 180.0f;

    glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};

};


class Sandbox : public Gaze::Application {
public:
    Sandbox() {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox() {}

private:

};

Gaze::Application *Gaze::CreateApplication() {
    return new Sandbox();
}
