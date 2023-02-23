#ifndef TRANSCRIPT_STATE_H
#define TRANSCRIPT_STATE_H

#include <array>
#include <cstdint>

namespace transcript::util::state {

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

} // namespace keccak::util::bit_operation

#endif //TRANSCRIPT_STATE_H