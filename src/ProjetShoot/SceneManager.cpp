#include "SceneManager.h"

SceneManager::SceneManager()
{
    currentScene = nullptr;
}

SceneManager::~SceneManager()
{
    for (auto& pair : scenes)
    {
        delete pair.second;
    }
}

void SceneManager::AddScene(const std::string& name, Scene* scene)
{
    scenes[name] = scene;
}

void SceneManager::SetCurrentScene(const std::string& name)
{
    auto it = scenes.find(name);
    if (it != scenes.end())
    {
        currentScene = it->second;
    }
}

Scene* SceneManager::GetCurrentScene() const
{
    return currentScene;
}

void SceneManager::SpawnEnemy()
{
    if (currentScene)
    {

        currentScene->SpawnEnemy(0);
    }
}


void SceneManager::Update(float deltaTime)
{
    if (currentScene)
    {
        currentScene->Update(deltaTime);
    }
}

void SceneManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (currentScene)
    {
        target.draw(*currentScene, states);
    }
}