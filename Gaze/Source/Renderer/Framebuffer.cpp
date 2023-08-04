#include "Framebuffer.h"
#include "GazePCH.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"
#include "Renderer/Renderer.h"

namespace Gaze
{

    Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
    {

        Ref<Framebuffer> result = nullptr;
        switch (RendererAPI::Current())
        {
            case RendererAPIType::None:
                GZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPIType::OpenGL:
                result = Ref<OpenGLFramebuffer>::Create(spec);
                FramebufferPool::GetGlobal()->Add(result);
                return result;
        }
        GZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    FramebufferPool* FramebufferPool::s_Instance = new FramebufferPool;

    FramebufferPool::FramebufferPool(uint32_t maxFBs /* = 32 */) {}

    FramebufferPool::~FramebufferPool() {}

    std::weak_ptr<Framebuffer> FramebufferPool::AllocateBuffer()
    {
        // m_Pool.push_back();
        return std::weak_ptr<Framebuffer>();
    }

    void FramebufferPool::Add(const Ref<Framebuffer>& framebuffer) { m_Pool.push_back(framebuffer); }
} // namespace Gaze