class seed_random_number_generator:
    max_int = 0x7FFFFFFF
    max_float = 0x7FFFFF
    mask = (2 ** 32 - 1)
    magic_number = 1557985959

    def __init__(self, seed_param):
        seed = seed_param
        rolval = ((seed << 16) & self.mask) | ((seed >> 16) & self.mask)
        self.seed0 = seed if seed else 1
        self.seed1 = seed ^ rolval

    def next_seed(self):
        next_seed = self.magic_number * self.seed0 + self.seed1
        self.seed0 = next_seed & 0xFFFFFFFF
        self.seed1 = next_seed >> 32
        return next_seed

    def get_random_int_ranged(self, min_val, max_val):
        if min_val == max_val:
            return min_val
        if min_val >= max_val:
            return 0
        next_seed = self.next_seed()
        return min_val + (next_seed & self.max_int) % (max_val - min_val + 1)

    def get_random_float_ranged(self, min_val, max_val):
        if min_val == max_val:
            return min_val
        if min_val >= max_val:
            return 0
        range_val = max_val - min_val
        next_seed = self.next_seed()
        return min_val + (range_val * (next_seed & self.max_float) / self.max_float)

# Example Usage
rng = seed_random_number_generator(69420)
for i in range(10):
    print("Random integer:", rng.get_random_int_ranged(1, 10))
    print("Random float:", rng.get_random_float_ranged(1.0, 10.0))