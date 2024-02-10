#include <iostream>
#include <cstdint>

class seed_random_number_generator {
private:
    uint32_t max_int = 0x7FFFFFFF;
    uint32_t max_float = 0x7FFFFF;
    uint64_t mask = (static_cast<uint64_t>(2) << 32) - 1;
    uint64_t magic_number = 1557985959;

    uint64_t seed0;
    uint64_t seed1;

    uint64_t next_seed() {
        uint64_t next_seed = magic_number * seed0 + seed1;
        seed0 = next_seed & 0xFFFFFFFF;
        seed1 = next_seed >> 32;
        return next_seed;
    }

public:
    seed_random_number_generator(uint64_t seed_param) {
        uint64_t seed = seed_param;
        uint64_t rolval = ((seed << 16) & mask) | ((seed >> 16) & mask);
        seed0 = seed ? seed : 1;
        seed1 = seed ^ rolval;
    }

    int get_random_int_ranged(int min, int max) {
        if (min == max)
            return min;
        if (min >= max)
            return 0;
        uint64_t _next_seed = next_seed();
        return min + (_next_seed & max_int) % (max - min + 1);
    }

    float get_random_float_ranged(float min, float max) {
        if (min == max)
            return min;
        if (min >= max)
            return 0;
        float range = max - min;
        uint64_t _next_seed = next_seed();
        return min + (range * (static_cast<float>(_next_seed & max_float) / max_float));
    }
};

// Example Usage
int main() {
    seed_random_number_generator rng(69420);
    for (int i = 0; i < 10; i++)
    {
        std::cout << rng.get_random_int_ranged(1, 10) << std::endl;
        std::cout << rng.get_random_float_ranged(1.0f, 10.0f) << std::endl;
    }

    return 0;
}