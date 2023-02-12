#ifndef TRANSCRIPT_RANDOM_H
#define TRANSCRIPT_RANDOM_H

#include <cstdint>
#include <random>

namespace keccak::util::random {

template<typename T>
requires std::is_integral<T>::value
T get_random(T max = std::numeric_limits<T>::max()) noexcept {
    std::random_device device;
    std::default_random_engine randomEngine(device());
    std::uniform_int_distribution<uint64_t> distribution{0, max};
    return distribution(randomEngine);
}

} // namespace keccak::util::random

#endif //TRANSCRIPT_RANDOM_H