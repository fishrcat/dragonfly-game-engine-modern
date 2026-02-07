// input_manager.h — Manager of player input (keyboard and mouse)

#pragma once

// Engine
#include "manager.h"

#define IM df::InputManager::getInstance()

namespace df {

class InputManager : public Manager {
    public:
    InputManager(const InputManager&) = delete;  // Disable copy
    auto operator=(const InputManager&) -> InputManager& =
                                               delete;  // Disable assignment

    static auto getInstance() -> InputManager&;  // Singleton

    [[nodiscard]] auto startUp()
        -> StartupResult override;  // Enforce startup checks
    void shutDown() noexcept override;

    static void getInput();

    private:
    InputManager();
};

}  // namespace df
