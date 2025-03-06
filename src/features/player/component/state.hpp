namespace player
{
    struct state
    {
        enum State
        {
            idle,
            idle_left,
            idle_right,
            idle_back,
            walk,
            walk_left,
            walk_right,
            walk_back
        };
        State currentState;
    };
}