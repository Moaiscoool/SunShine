#pragma once
#include <engine/engine.hpp>

class Engine;

class Scene {
    private:
    
    public:
        virtual ~Scene() = default;

        Engine* m_engine;
        
        std::string id = "base";

        virtual bool Init(Engine* engine);
        virtual void Update();
        virtual void Shutdown();
};

class SceneManager {
    private:

    public:
        Engine* m_engine = nullptr;
        Scene* CurrentScene = nullptr;
        std::unordered_map<std::string, std::unique_ptr<Scene>> scenes;

        void Register(std::unique_ptr<Scene> scene) { scenes[scene->id] = std::move(scene); }
        
        bool Init(Engine* engine);
        void Shutdown();

        bool LoadScene(const std::string& id);
        void UnloadScene();
        void PauseScene();
        void ResumeScene();
};