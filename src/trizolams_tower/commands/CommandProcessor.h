#pragma once

#include "ICommand.h"
#include "../managers/GameManager.h"
#include "../managers/SceneManager.h"
#include <memory>
#include <string>
#include <unordered_map>

class CommandProcessor
{
private:
    std::unordered_map<std::string, ICommand> m_processors;
    std::shared_ptr<GameManager> m_gm_ptr;
    std::shared_ptr<SceneManager> m_sm_ptr;

public:
    CommandProcessor(std::shared_ptr<GameManager>, std::shared_ptr<SceneManager>);
    ~CommandProcessor() = default;
    void get_payload_generator(std::string);
    void process_command();
};