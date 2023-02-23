#include "builder/rng_builder.h"

#include <array>
#include <vector>

#include "utils/bit.h"

namespace transcript::builder {

using rng::core::RngCore;
using rng::util::bit::to_le_bytes;
using strobe::Strobe128;

RngBuilder::RngBuilder(const Strobe128 &strobe) : strobe{strobe} {}

RngBuilder::RngBuilder(Strobe128 &&strobe) noexcept: strobe{std::move(strobe)} {}

RngBuilder RngBuilder::rekey_with_witness_bytes(const std::string_view &label, const std::vector<uint8_t> &witness) {
    const auto len_as_bytes = to_le_bytes<uint32_t>(witness.size());
    const std::vector<uint8_t> len{len_as_bytes.begin(), len_as_bytes.end()};

    this->strobe.meta_ad(label, false);
    this->strobe.meta_ad(len, true);
    this->strobe.key(witness, false);

    return *this;
}

TranscriptRng RngBuilder::finalize(RngCore &rng) {
    std::array<uint8_t, 32> bytes{};
    rng.fill_bytes(bytes);
    std::vector<uint8_t> random_bytes{bytes.begin(), bytes.end()};

    this->strobe.meta_ad("rng", false);
    this->strobe.key(random_bytes, false);

    return TranscriptRng{this->strobe};
}

} // namespace transcript::builder
