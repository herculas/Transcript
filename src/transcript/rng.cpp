#include "transcript/rng.h"

#include "util/bit.h"
#include "util/random.h"

namespace transcript::transcript {

Rng::Rng(const strobe::Strobe128 &strobe) : strobe{strobe} {}

Rng::Rng(strobe::Strobe128 &&strobe) noexcept: strobe{std::move(strobe)} {}

uint32_t Rng::get_uint32() {
    return keccak::util::random::get_random<uint32_t>();
}

uint64_t Rng::get_uint64() {
    return keccak::util::random::get_random<uint64_t>();
}

void Rng::fill_bytes(std::vector<uint8_t> &destination) {
    const auto len_as_bytes = keccak::util::bit_operation::size_t_to_le_bytes(destination.size());
    const std::vector<uint8_t> len{len_as_bytes.begin(), len_as_bytes.end()};

    this->strobe.meta_ad(len, false);
    this->strobe.prf(destination, false);
}

} // namespace transcript::transcript