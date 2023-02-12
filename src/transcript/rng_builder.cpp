#include "transcript/rng_builder.h"

#include <vector>

#include "util/bit.h"
#include "util/random.h"

namespace transcript::transcript {

RngBuilder::RngBuilder(const strobe::Strobe128 &strobe) : strobe{strobe} {}

RngBuilder::RngBuilder(strobe::Strobe128 &&strobe) noexcept: strobe{std::move(strobe)} {}

RngBuilder RngBuilder::rekey_with_witness_bytes(const std::string_view &label, const std::vector<uint8_t> &witness) {
    const auto len_as_bytes = keccak::util::bit_operation::size_t_to_le_bytes(witness.size());
    const std::vector<uint8_t> len{len_as_bytes.begin(), len_as_bytes.end()};

    this->strobe.meta_ad(label, false);
    this->strobe.meta_ad(len, true);
    this->strobe.key(witness, false);

    return *this;
}

Rng RngBuilder::finalize() {
    std::vector<uint8_t> random_bytes;
    random_bytes.reserve(32);
    for (int i = 0; i < 32; ++i)
        random_bytes[i] = keccak::util::random::get_random<uint8_t>();

    this->strobe.meta_ad("rng", false);
    this->strobe.key(random_bytes, false);

    return Rng{this->strobe};
}

} // namespace transcript::transcript
