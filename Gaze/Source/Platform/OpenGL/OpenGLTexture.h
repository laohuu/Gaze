#ifndef GAZE_ENGINE_OPENGLTEXTURE_H
#define GAZE_ENGINE_OPENGLTEXTURE_H

#include "Renderer/Texture.h"

#include <glad/glad.h>

namespace Gaze
{

    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const TextureSpecification& specification);
        OpenGLTexture2D(const std::string& path, bool srgb);
        virtual ~OpenGLTexture2D();

        const TextureSpecification& GetSpecification() const override { return m_Specification; }

        uint32_t GetWidth() const override { return m_Specification.Width; }
        uint32_t GetHeight() const override { return m_Specification.Height; }
        // This function currently returns the expected number of mips based on image size,
        // not present mips in data
        uint32_t GetMipLevelCount() const override;

        void Lock() override;
        void Unlock() override;

        void   Resize(uint32_t width, uint32_t height) override;
        Buffer GetWriteableBuffer() override;

        RendererID GetRendererID() const override { return m_RendererID; }

        const std::string& GetPath() const override { return m_Path; }

        void Bind(uint32_t slot = 0) const override;

        bool IsLoaded() const override { return m_IsLoaded; }

        bool operator==(const Texture& other) const override { return m_RendererID == other.GetRendererID(); }

    private:
        TextureSpecification m_Specification;

        std::string m_Path;

        Buffer m_ImageData;

        RendererID m_RendererID;
        GLenum     m_InternalFormat, m_DataFormat;

        bool m_IsHDR    = false;
        bool m_Locked   = false;
        bool m_IsLoaded = false;
    };

    class OpenGLTextureCube : public TextureCube
    {
    public:
        OpenGLTextureCube(const TextureSpecification& specification);
        OpenGLTextureCube(const std::string& path);
        virtual ~OpenGLTextureCube();

        const TextureSpecification& GetSpecification() const override { return m_Specification; }

        virtual void Bind(uint32_t slot = 0) const;

        uint32_t GetWidth() const override { return m_Specification.Width; }
        uint32_t GetHeight() const override { return m_Specification.Height; }
        // This function currently returns the expected number of mips based on image size,
        // not present mips in data
        uint32_t GetMipLevelCount() const override;

        const std::string& GetPath() const override { return m_FilePath; }

        RendererID GetRendererID() const override { return m_RendererID; }

        bool operator==(const Texture& other) const override
        {
            return m_RendererID == ((OpenGLTextureCube&)other).m_RendererID;
        }

    private:
        TextureSpecification m_Specification;

        RendererID     m_RendererID;
        unsigned char* m_ImageData;

        std::string m_FilePath;
    };

} // namespace Gaze

#endif // GAZE_ENGINE_OPENGLTEXTURE_H
