#include "CommandProcessor.h"
#include "TravelCommand.h"

CommandProcessor::CommandProcessor(std::shared_ptr<GameManager> gm, std::shared_ptr<SceneManager> sm)
{
    m_gm_ptr = gm;
    m_sm_ptr = sm;

    m_processors = {
        {"travel-command", new TravelCommand{}},
    };
}

PayloadGenerator CommandProcessor::get_payload_generator(std::string command_name)
{
    auto processor = m_processors[command_name];
    return processor->get_payload_generator();
}

void CommandProcessor::process_command(Rule::PlayerCommand command)
{
    auto processor = m_processors[command.type];
    processor->handle_command(*m_gm_ptr, *m_sm_ptr, command);
}

CommandProcessor::~CommandProcessor()
{
    // TODO: DELETE M_PROCESSORS POINTERS
    for (auto const &[key, value] : m_processors)
    {
        delete (value);
    }
}