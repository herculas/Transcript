#ifndef TRANSCRIPT_RNG_H
#define TRANSCRIPT_RNG_H

#include <cstdint>
#include <vector>

#include "strobe/strobe_128.h"

namespace transcript::transcript {

class Rng {
private:
    strobe::Strobe128 strobe;

public:
    explicit Rng(const strobe::Strobe128 &strobe);
    explicit Rng(strobe::Strobe128 &&strobe) noexcept;

    static uint32_t get_uint32();
    static uint64_t get_uint64();

    void fill_bytes(std::vector<uint8_t> &destination);
};

} // namespace transcript::transcript

#endif //TRANSCRIPT_RNG_H