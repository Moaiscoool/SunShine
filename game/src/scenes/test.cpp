#include <game/game.hpp>

bool TestScene::Init(Engine* engine){
    if(!engine){
        return false;
    }
    m_engine = engine;
    m_engine->console.InfoLog("Succesfuly Loaded " + id + " Scene!");
    return true;
}

void TestScene::Update(){
    m_engine->console.InfoLog("TestScene Update!");
}