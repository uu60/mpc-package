import random

def generate_triplets(bits, count):
    max_val = 2 ** (bits - 1) - 1
    mask = max_val
    triplets = []
    for _ in range(count):
        a = random.randint(0, max_val)
        b = random.randint(0, max_val)
        result = a * b
        result &= mask  # 保留结果的低 bits 位
        triplets.append((a, b, result))
    return triplets

def split_to_sums(value):
    # Split the value into two summands
    if value == 0:
        return 0, 0
    part1 = random.randint(0, value)
    part2 = value - part1
    return part1, part2

def format_triplets_for_cpp(triplets, bits):
    type_map = {
        1: "bool",
        8: "int8_t",
        16: "int16_t",
        32: "int32_t",
        64: "int64_t"
    }
    cpp_type = type_map[bits]
    formatted_triplets = []
    for a, b, result in triplets:
        a1, a2 = split_to_sums(a)
        b1, b2 = split_to_sums(b)
        r1, r2 = split_to_sums(result)
        formatted_triplets.append(f"{{{{{a1}, {a2}}}, {{{b1}, {b2}}}, {{{r1}, {r2}}}}}")
    return f"std::array<std::tuple<std::pair<{cpp_type}, {cpp_type}>, std::pair<{cpp_type}, {cpp_type}>, std::pair<{cpp_type}, {cpp_type}>>, {len(triplets)}> triplets_{bits} = {{{{{', '.join(formatted_triplets)}}}}};"


if __name__ == '__main__':
    # Generate and format triplets for different bit sizes
    bit_sizes = [1, 8, 16, 32, 64]
    triplets_count = 100  # Number of triplets to generate for each bit size

    for bits in bit_sizes:
        triplets = generate_triplets(bits, triplets_count)
        cpp_code = format_triplets_for_cpp(triplets, bits)
        print(cpp_code)
        print()