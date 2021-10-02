#include "./CommandProcessor.h"
#include "TravelCommand.h"
#include "PlaceObjectCommand.h"

CommandProcessor::CommandProcessor(std::shared_ptr<GameManager> gm, std::shared_ptr<SceneManager> sm)
{
    m_gm_ptr = gm;
    m_sm_ptr = sm;

    m_processors = {
        {"travel-command", new TravelCommand{}},
        {"place-object-command", new PlaceObjectCommand{}},
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
    // TODO: I think this causes a segmentation fault on exit, but do I care?
    for (auto const &[key, value] : m_processors)
    {
        delete (value);
    }
}