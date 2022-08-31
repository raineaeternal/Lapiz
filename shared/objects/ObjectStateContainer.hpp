#pragma once

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Pose.hpp"
#include "UnityEngine/Vector3.hpp"

namespace Lapiz::Objects {
    class ObjectStateContainer {
        public:
            inline explicit ObjectStateContainer(UnityEngine::GameObject* mainParent) : ObjectStateContainer((mainParent && mainParent->m_CachedPtr.m_value) ? mainParent->get_transform() : nullptr) {}
            explicit ObjectStateContainer(UnityEngine::Transform* mainParent);
            void Revert();
        private:
            class ObjectState {
                public:
                    void Revert();
                    explicit ObjectState(UnityEngine::Transform* transform);
                private:
                    bool active;
                    UnityEngine::Pose pose;
                    UnityEngine::Vector3 scale;
                    UnityEngine::Transform* transform;
                    UnityEngine::Transform* parent;

            };
            static void Snapshot(UnityEngine::Transform* transform, std::vector<ObjectState>& populator);
            std::vector<ObjectState> objects;
    };
}