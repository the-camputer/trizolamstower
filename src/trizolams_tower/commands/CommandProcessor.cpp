#include "CommandProcessor.h"

CommandProcessor::CommandProcessor(std::shared_ptr<GameManager> gm, std::shared_ptr<SceneManager> sm)
{
    m_gm_ptr = gm;
    m_sm_ptr = sm;
}