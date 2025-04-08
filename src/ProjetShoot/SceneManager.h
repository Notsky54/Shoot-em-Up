#include "Menu.h"
#include "Scene.h"
#include <map>
#include <string>

class SceneManager : public sf::Drawable
{
private:
    std::map<std::string, Scene*> scenes;
    Scene* currentScene;     // Scène active

public:
    SceneManager();
    ~SceneManager();
    void AddScene(const std::string& name, Scene* scene);
    void SetCurrentScene(const std::string& name);
    Scene* GetCurrentScene() const;
    void SpawnEnemy();
    void Update(float deltaTime);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

