
class GameManager
{
private:
    int player_position;

public:
    // TODO: Should this be a singleton? Discuss as game progresses
    GameManager() = default;
    ~GameManager() = default;

    void set_player_position(int);
    int get_player_position();
};