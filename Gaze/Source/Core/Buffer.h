#ifndef GAZE_ENGINE_CORE_BUFFER_H
#define GAZE_ENGINE_CORE_BUFFER_H

#include <cstdint>
#include <cstring>

namespace Gaze
{

    typedef unsigned char byte;

    // Non-owning raw buffer class
    struct Buffer
    {
        void*    Data;
        uint64_t Size;

        Buffer() : Data(nullptr), Size(0) {}

        Buffer(const void* data, uint64_t size = 0) : Data((void*)data), Size(size) {}

        static Buffer Copy(const Buffer& other)
        {
            Buffer buffer;
            buffer.Allocate(other.Size);
            memcpy(buffer.Data, other.Data, other.Size);
            return buffer;
        }

        static Buffer Copy(const void* data, uint64_t size)
        {
            Buffer buffer;
            buffer.Allocate(size);
            memcpy(buffer.Data, data, size);
            return buffer;
        }

        void Allocate(uint64_t size)
        {
            Release();

            if (size == 0)
                return;

            Data = new byte[size];
            Size = size;
        }

        void Release()
        {
            delete[] (byte*)Data;
            Data = nullptr;
            Size = 0;
        }

        void ZeroInitialize()
        {
            if (Data)
                memset(Data, 0, Size);
        }

        template<typename T>
        T& Read(uint64_t offset = 0)
        {
            return *(T*)((byte*)Data + offset);
        }

        template<typename T>
        const T& Read(uint64_t offset = 0) const
        {
            return *(T*)((byte*)Data + offset);
        }

        byte* ReadBytes(uint64_t size, uint64_t offset) const
        {
            GZ_CORE_ASSERT(offset + size <= Size, "Buffer overflow!");
            byte* buffer = new byte[size];
            memcpy(buffer, (byte*)Data + offset, size);
            return buffer;
        }

        void Write(const void* data, uint64_t size, uint64_t offset = 0)
        {
            GZ_CORE_ASSERT(offset + size <= Size, "Buffer overflow!");
            memcpy((byte*)Data + offset, data, size);
        }

        operator bool() const { return Data; }

        byte& operator[](int index) { return ((byte*)Data)[index]; }

        byte operator[](int index) const { return ((byte*)Data)[index]; }

        template<typename T>
        T* As() const
        {
            return (T*)Data;
        }

        inline uint64_t GetSize() const { return Size; }
    };

    struct BufferSafe : public Buffer
    {
        ~BufferSafe() { Release(); }

        static BufferSafe Copy(const void* data, uint64_t size)
        {
            BufferSafe buffer;
            buffer.Allocate(size);
            memcpy(buffer.Data, data, size);
            return buffer;
        }
    };

} // namespace Gaze

#endif // GAZE_ENGINE_CORE_BUFFER_H
