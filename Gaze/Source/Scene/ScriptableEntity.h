#ifndef GAZE_ENGINE_SCRIPTABLEENTITY_H
#define GAZE_ENGINE_SCRIPTABLEENTITY_H

#include "Entity.h"

namespace Gaze {

    class ScriptableEntity {
    public:
        virtual ~ScriptableEntity() = default;

        template<typename T>
        T &GetComponent() {
            return m_Entity.GetComponent<T>();
        }

    protected:
        virtual void OnCreate() {}

        virtual void OnDestroy() {}

        virtual void OnUpdate(Timestep ts) {}

    private:
        Entity m_Entity;

        friend class Scene;
    };

} // Gaze

#endif //GAZE_ENGINE_SCRIPTABLEENTITY_H
