#ifndef TRANSCRIPT_BIT_H
#define TRANSCRIPT_BIT_H

#include <array>
#include <cassert>
#include <cstdint>
#include <type_traits>

namespace keccak::util::bit_operation {

constexpr std::array<uint64_t, 25> aggregate_state(const std::array<uint8_t, 200> &state) {
    std::array<uint64_t, 25> aggregated_state{};
    for (int i = 0; i < state.size(); i += 8)
        for (int j = 0; j < 8; ++j)
            aggregated_state[i / 8] += static_cast<uint64_t>(state[i + j] & 0x00ff) << (j * 8);
    return aggregated_state;
}

constexpr std::array<uint8_t, 200> partition_state(const std::array<uint64_t, 25> &aggregated_state) {
    std::array<uint8_t, 200> state{};
    for (int i = 0; i < state.size(); i += 8)
        for (int j = 0; j < 8; ++j)
            state[i + j] = static_cast<uint8_t>(aggregated_state[i / 8] >> (j * 8)) & 0x00ff;
    return state;
}

constexpr std::array<uint8_t, sizeof(uint64_t)> uint64_to_le_bytes(uint64_t value) {
    std::array<uint8_t, sizeof(uint64_t)> bytes{0};
    for (int i = 0; i < sizeof(uint64_t); ++i)
        bytes[i] = static_cast<uint8_t>(value >> (i * 8)) & 0x00ff;
    return bytes;
}

constexpr std::array<uint8_t, sizeof(uint32_t)> size_t_to_le_bytes(size_t value) {
    assert(value <= std::numeric_limits<uint32_t>::max());
    std::array<uint8_t, sizeof(uint32_t)> bytes{0};
    for (int i = 0; i < sizeof(uint32_t); ++i)
        bytes[i] = static_cast<uint8_t>(static_cast<uint32_t>(value) >> (i * 8)) & 0x00ff;
    return bytes;
}

} // namespace keccak::util::bit_operation

#endif //TRANSCRIPT_BIT_H