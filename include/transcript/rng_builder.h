#ifndef TRANSCRIPT_RNG_BUILDER_H
#define TRANSCRIPT_RNG_BUILDER_H

#include "strobe/strobe_128.h"
#include "transcript/rng.h"

namespace transcript::transcript {

class RngBuilder {
private:
    strobe::Strobe128 strobe;

public:
    explicit RngBuilder(const strobe::Strobe128 &strobe);
    explicit RngBuilder(strobe::Strobe128 &&strobe) noexcept;

    RngBuilder rekey_with_witness_bytes(const std::string_view &label, const std::vector<uint8_t> &witness);
    Rng finalize();
};

} // namespace transcript::transcript

#endif //TRANSCRIPT_RNG_BUILDER_H