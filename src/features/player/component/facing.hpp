namespace player
{
    struct facing
    {
        enum Facing
        {
            down,
            left,
            right,
            up
        };
        Facing currentFacing;
    };
}