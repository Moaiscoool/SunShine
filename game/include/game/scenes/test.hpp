#pragma once
#include <engine/engine.hpp>

class TestScene : public Scene {
    public:
        TestScene() { id = "test"; }
        bool Init(Engine* engine) override;
        void Update() override;
};