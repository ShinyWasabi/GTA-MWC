using System;

public class seed_random_number_generator
{
    private uint max_int = 0x7FFFFFFF;
    private uint max_float = 0x7FFFFF;
    private ulong mask = ((ulong)2 << 32) - 1;
    private ulong magic_number = 1557985959;

    private ulong seed0;
    private ulong seed1;

    private ulong next_seed()
    {
        ulong next_seed = magic_number * seed0 + seed1;
        seed0 = next_seed & 0xFFFFFFFF;
        seed1 = next_seed >> 32;
        return next_seed;
    }

    public seed_random_number_generator(ulong seedParam)
    {
        ulong seed = seedParam;
        ulong rolval = ((seed << 16) & mask) | ((seed >> 16) & mask);
        seed0 = seed != 0 ? seed : 1;
        seed1 = seed ^ rolval;
    }

    public int get_random_int_ranged(int min, int max)
    {
        if (min == max)
            return min;
        if (min >= max)
            return 0;
        ulong _next_seed = next_seed();
        return min + (int)(_next_seed & max_int) % (max - min + 1);
    }

    public float get_random_float_ranged(float min, float max)
    {
        if (min == max)
            return min;
        if (min >= max)
            return 0;
        float range = max - min;
        ulong _next_seed = next_seed();
        return min + (range * ((float)(_next_seed & max_float) / max_float));
    }
}

// Example Usage
class Program
{
    static void Main(string[] args)
    {
        seed_random_number_generator rng = new seed_random_number_generator(69420);
        for (int i = 0; i < 10; i++)
        {
            Console.WriteLine(rng.get_random_int_ranged(1, 10));
            Console.WriteLine(rng.get_random_float_ranged(1.0f, 10.0f));
        }
    }
}