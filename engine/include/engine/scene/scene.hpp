#pragma once
#include <engine/engine.hpp>

class Scene {
    private:
        Engine* m_engine;
    
    public:
        virtual ~Scene() = default;

        bool Init(Engine* engine);
        void update();
        void Shutdown();
};