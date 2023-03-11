#ifndef TRANSCRIPT_RNG_H
#define TRANSCRIPT_RNG_H

#include <cstdint>
#include <span>
#include <vector>

#include "core/rng.h"

#include "strobe/strobe_128.h"

namespace transcript::builder {

class TranscriptRng : public rng::core::RngCore {
private:
    strobe::Strobe128 strobe;

public:
    explicit TranscriptRng(const strobe::Strobe128 &strobe);
    explicit TranscriptRng(strobe::Strobe128 &&strobe) noexcept;

    uint32_t get_uint32() override;
    uint64_t get_uint64() override;
    void fill_bytes(const std::span<uint8_t> &dest) override;
};

} // namespace transcript::builder

#endif //TRANSCRIPT_RNG_H