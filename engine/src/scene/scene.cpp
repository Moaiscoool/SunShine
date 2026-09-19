#include <engine/engine.hpp>

bool Scene::Init(Engine* engine){
    if(!engine){
        return false;
    }
    m_engine = engine;
    return true;
}