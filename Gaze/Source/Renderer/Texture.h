#ifndef GAZE_ENGINE_TEXTURE_H
#define GAZE_ENGINE_TEXTURE_H

#include "Core/Base.h"
#include "Image.h"
#include "RendererAPI.h"
#include <Asset/Asset.h>
#include <Core/Buffer.h>

#include <string>

namespace Gaze
{
    struct TextureSpecification
    {
        uint32_t    Width  = 1;
        uint32_t    Height = 1;
        ImageFormat Format = ImageFormat::RGBA;

        TextureWrap   SamplerWrap   = TextureWrap::Repeat;
        TextureFilter SamplerFilter = TextureFilter::Linear;

        bool GenerateMips = true;

        std::string DebugName;
    };

    class Texture : public Asset
    {
    public:
        ~Texture() override = default;

        virtual const TextureSpecification& GetSpecification() const = 0;

        virtual uint32_t   GetWidth() const         = 0;
        virtual uint32_t   GetHeight() const        = 0;
        virtual RendererID GetRendererID() const    = 0;
        virtual uint32_t   GetMipLevelCount() const = 0;

        virtual const std::string& GetPath() const = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;

        virtual bool IsLoaded() const = 0;

        static uint32_t GetBPP(ImageFormat format);
        static uint32_t CalculateMipMapCount(uint32_t width, uint32_t height);

        virtual bool operator==(const Texture& other) const = 0;
    };

    class Texture2D : public Texture
    {
    public:
        static Ref<Texture2D> Create(const TextureSpecification& specification);
        static Ref<Texture2D> Create(const std::string& path, bool srgb = false);

        virtual void Lock()   = 0;
        virtual void Unlock() = 0;

        virtual void   Resize(uint32_t width, uint32_t height) = 0;
        virtual Buffer GetWriteableBuffer()                    = 0;

        virtual bool IsLoaded() const = 0;

        virtual const std::string& GetPath() const = 0;
    };

    class TextureCube : public Texture
    {
    public:
        static Ref<TextureCube> Create(const TextureSpecification& specification);
        static Ref<TextureCube> Create(const std::string& path);

        virtual const std::string& GetPath() const = 0;
    };

} // namespace Gaze

#endif // GAZE_ENGINE_TEXTURE_H
