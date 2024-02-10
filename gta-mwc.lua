seed_random_number_generator = {}
seed_random_number_generator.__index = seed_random_number_generator

function seed_random_number_generator.new(seed_param)
    local self = setmetatable({}, seed_random_number_generator)
    self.max_int = 0x7FFFFFFF
    self.max_float = 0x7FFFFF
    self.mask = (2 ^ 32 - 1)
    self.magic_number = 1557985959

    local seed = seed_param
    local rolval = (seed << 16 & self.mask) | (seed >> 16 & self.mask)
    self.seed0 = seed ~= 0 and seed or 1
    self.seed1 = seed ~ rolval
    return self
end

function seed_random_number_generator:next_seed()
    local next_seed = self.magic_number * self.seed0 + self.seed1
    self.seed0 = next_seed & 0xFFFFFFFF
    self.seed1 = next_seed >> 32
    return next_seed
end

function seed_random_number_generator:get_random_int_ranged(min_val, max_val)
    if min_val == max_val then
        return min_val
    end
    if min_val >= max_val then
        return 0
    end
    local next_seed = self:next_seed()
    return min_val + ((next_seed & self.max_int) % (max_val - min_val + 1))
end

function seed_random_number_generator:get_random_float_ranged(min_val, max_val)
    if min_val == max_val then
        return min_val
    end
    if min_val >= max_val then
        return 0
    end
    local range_val = max_val - min_val
    local next_seed = self:next_seed()
    return min_val + (range_val * ((next_seed & self.max_float) / self.max_float))
end

-- Example Usage
local rng = seed_random_number_generator.new(69720)
for i = 1, 10 do
    print(rng:get_random_int_ranged(1, 10))
    print(rng:get_random_float_ranged(1.0, 10.0))
end