{
    int x;
    int y;

    x = 5;

    if (x > 0)
    {
        y = x;
    }
    else
        y = 0;

    while (y > 0)
        y = y - 1;

    for (x = 0; x < 10; x = x + 1)
        y = y + x;

    return y;
}
