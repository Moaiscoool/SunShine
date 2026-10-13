#include <engine/engine.hpp>
#include <game/scenes/scenes.hpp>

class Engine;

bool SceneManager::Init(Engine* engine){
    if(!engine){
        return false;
    }
    m_engine = engine;
    m_engine->console.InfoLog("Succesfuly Started SceneManager!");
    return true;
}

void SceneManager::Shutdown(){
    
}

bool SceneManager::LoadScene(const std::string& id) {
    auto it = scenes.find(id);
    if (it == scenes.end()) {
        m_engine->console.ErrorLog("Failed to load Scene With ID: " + id);
        return false;
    }
    if (CurrentScene) CurrentScene->Shutdown();
    CurrentScene = it->second.get();
    if (!CurrentScene->Init(m_engine)) { CurrentScene = nullptr; return false; }
    return true;
}

bool Scene::Init(Engine* engine){
    if(!engine){
        return false;
    }
    m_engine = engine;
    m_engine->console.InfoLog("Succesfuly Loaded " + id + " Scene!");
    return true;
}

void Scene::Update(){

}

void Scene::Shutdown(){
    
}