include_directories(commands)

add_library(
    PlayerCommandFactory

    OBJECT

    PlayerCommandFactory.cpp

    PlayerCommandFactory.h
    CommandTypes.h
    PlayerCommand.h
)