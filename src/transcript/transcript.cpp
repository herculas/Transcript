#include "transcript/transcript.h"

#include <array>

#include "transcript/constant.h"
#include "util/bit.h"

namespace transcript::transcript {

Transcript::Transcript(const std::string_view &label) : strobe{constant::PROTOCOL_LABEL} {
    this->append_message("dom-sep", label);
}

void Transcript::append_message(const std::string_view &label, const std::vector<uint8_t> &message) {
    const auto len_as_bytes = keccak::util::bit_operation::size_t_to_le_bytes(message.size());
    const std::vector<uint8_t> len{len_as_bytes.begin(), len_as_bytes.end()};

    this->strobe.meta_ad(label, false);
    this->strobe.meta_ad(len, true);
    this->strobe.ad(message, false);
}

void Transcript::append_message(const std::string_view &label, const std::string_view &message) {
    const auto len_as_bytes = keccak::util::bit_operation::size_t_to_le_bytes(message.size());
    const std::vector<uint8_t> len{len_as_bytes.begin(), len_as_bytes.end()};

    this->strobe.meta_ad(label, false);
    this->strobe.meta_ad(len, true);
    this->strobe.ad(message, false);
}

void Transcript::append_message(const std::string_view &label, uint64_t message) {
    const auto message_as_bytes = keccak::util::bit_operation::uint64_to_le_bytes(message);
    const std::vector<uint8_t> encoded_message{message_as_bytes.begin(), message_as_bytes.end()};

    this->append_message(label, encoded_message);
}

void Transcript::challenge_bytes(const std::string_view &label, std::vector<uint8_t> &destination) {
    const auto len_as_bytes = keccak::util::bit_operation::size_t_to_le_bytes(destination.size());
    const std::vector<uint8_t> len{len_as_bytes.begin(), len_as_bytes.end()};

    this->strobe.meta_ad(label, false);
    this->strobe.meta_ad(len, true);
    this->strobe.prf(destination, false);
}

RngBuilder Transcript::build_rng() const {
    return RngBuilder(this->strobe);
}

} // namespace transcript::transcript