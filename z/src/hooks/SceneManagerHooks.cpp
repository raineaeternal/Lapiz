#include "UnityEngine/SceneManagement/Scene.hpp"
#include "UnityEngine/SceneManagement/SceneManager.hpp"
#include "utilities/HookingUtility.hpp"

MAKE_HOOK_MATCH(
    SceneManager_Internal_ActiveSceneChanged,
    &UnityEngine::SceneManagement::SceneManager::Internal_ActiveSceneChanged,
    void, UnityEngine::SceneManagement::Scene prevScene,
    UnityEngine::SceneManagement::Scene nextScene) {
    SceneManager_Internal_ActiveSceneChanged(prevScene, nextScene);
    if (prevScene.IsValid() && nextScene.IsValid()) {
        std::string prevSceneName(prevScene.get_name());
        std::string nextSceneName(nextScene.get_name());
        getLogger().info("Scene change from %s to %s", prevSceneName.c_str(),
                         nextSceneName.c_str());
        static bool hasInited = false;
        if (prevSceneName == "QuestInit") { hasInited = true; }
        if (hasInited && prevSceneName == "EmptyTransition" &&
            nextSceneName.find("Menu") != std::string::npos) {
            hasInited = false;
            // Setup persistent objects.
            // todo impl main thread scheduler.
        }
    }
}

void InstallSceneManagerHooks(Logger &logger){
    INSTALL_HOOK(logger, SceneManager_Internal_ActiveSceneChanged)}

zInstallHooks(InstallSceneManagerHooks);