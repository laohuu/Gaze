#ifndef GAZE_ENGINE_UUID_H
#define GAZE_ENGINE_UUID_H

#include "xhash"

namespace Gaze {

    class UUID {
    public:
        UUID();

        UUID(uint64_t uuid);

        UUID(const UUID &) = default;

        operator uint64_t() const { return m_UUID; }

    private:
        uint64_t m_UUID;
    };

} // Gaze

namespace std {
    
    template<typename T>
    struct hash;

    template<>
    struct hash<Gaze::UUID> {
        std::size_t operator()(const Gaze::UUID &uuid) const {
            return (uint64_t) uuid;
        }
    };

}

#endif //GAZE_ENGINE_UUID_H
