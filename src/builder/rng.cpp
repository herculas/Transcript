#include "builder/rng.h"

#include "utils/bit.h"

namespace transcript::builder {

using rng::util::bit::to_le_bytes;
using strobe::Strobe128;

TranscriptRng::TranscriptRng(const Strobe128 &strobe) : strobe{strobe} {}

TranscriptRng::TranscriptRng(Strobe128 &&strobe) noexcept: strobe{std::move(strobe)} {}

uint32_t TranscriptRng::get_uint32() {
    return 0;
}

uint64_t TranscriptRng::get_uint64() {
    return 0;
}

void TranscriptRng::fill_bytes(const std::span<uint8_t> &dest) {
    const auto len = to_le_bytes<uint32_t>(dest.size());
    const std::vector<uint8_t> dest_len{len.begin(), len.end()};
    std::vector<uint8_t> dest_con{dest.begin(), dest.end()};
    this->strobe.meta_ad(dest_len, false);
    this->strobe.prf(dest_con, false);
}

} // namespace transcript::builder