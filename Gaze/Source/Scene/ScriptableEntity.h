#ifndef GAZE_ENGINE_SCRIPTABLEENTITY_H
#define GAZE_ENGINE_SCRIPTABLEENTITY_H

#include "Entity.h"

namespace Gaze {

    class ScriptableEntity {
    public:
        template<typename T>
        T &GetComponent() {
            return m_Entity.GetComponent<T>();
        }

    private:
        Entity m_Entity;

        friend class Scene;
    };

} // Gaze

#endif //GAZE_ENGINE_SCRIPTABLEENTITY_H
