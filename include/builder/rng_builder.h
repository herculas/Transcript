#ifndef TRANSCRIPT_RNG_BUILDER_H
#define TRANSCRIPT_RNG_BUILDER_H

#include "core/rng.h"

#include "builder/rng.h"
#include "strobe/strobe_128.h"

namespace transcript::builder {

class RngBuilder {
private:
    strobe::Strobe128 strobe;

public:
    explicit RngBuilder(const strobe::Strobe128 &strobe);
    explicit RngBuilder(strobe::Strobe128 &&strobe) noexcept;

    RngBuilder rekey_with_witness_bytes(const std::string_view &label, const std::vector<uint8_t> &witness);
    TranscriptRng finalize(rng::core::RngCore &rng);
};

} // namespace transcript::builder

#endif //TRANSCRIPT_RNG_BUILDER_H