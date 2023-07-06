#ifndef GAZE_ENGINE_UUID_H
#define GAZE_ENGINE_UUID_H

namespace Gaze
{
    // "UUID" (universally unique identifier) or GUID is (usually) a 128-bit integer
    class UUID
    {
    public:
        UUID();
        UUID(uint64_t uuid);
        UUID(const UUID& other) = default;

        operator uint64_t() { return m_UUID; }
        operator const uint64_t() const { return m_UUID; }

    private:
        uint64_t m_UUID;
    };
} // namespace Gaze

namespace std
{
    template<typename T>
    struct hash;

    template<>
    struct hash<Gaze::UUID>
    {
        std::size_t operator()(const Gaze::UUID& uuid) const { return uuid; }
    };
} // namespace std

#endif // GAZE_ENGINE_UUID_H
