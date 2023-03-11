#include "strobe/strobe_128.h"

#include <cassert>
#include <string>

#include "core.h"

#include "strobe/constant.h"
#include "utils/state.h"
#include "utils/encode.h"

namespace transcript::strobe {

using util::state::aggregate_state;
using util::state::partition_state;
using util::encoding::str_to_bytes;

Strobe128::Strobe128(const Strobe128 &strobe) = default;

Strobe128::Strobe128(Strobe128 &&strobe) noexcept = default;

Strobe128::Strobe128(const std::string_view &protocol_label)
        : position{0}, position_begin{0}, current_flags{0}, state{} {
    AlignedKeccakState temp_state{0};
    const std::array<uint8_t, 6> first_line = {1, strobe::constant::R + 2, 1, 0, 1, 96};
    const std::string second_line = constant::STROBE_TAG;

    std::copy(first_line.begin(), first_line.end(), temp_state.begin());
    std::copy(second_line.begin(), second_line.end(), temp_state.begin() + 6);

    std::array<uint64_t, 25> aggregated_state = aggregate_state(temp_state);
    keccak::util::keccak_f(aggregated_state);

    this->state = partition_state(aggregated_state);
    this->meta_ad(protocol_label, false);
}

void Strobe128::meta_ad(const std::vector<uint8_t> &data, bool more) {
    this->begin_op(constant::FLAG::M | constant::FLAG::A, more);
    this->absorb(data);
}

void Strobe128::meta_ad(const std::string_view &data, bool more) {
    std::vector<uint8_t> vec = str_to_bytes(data);
    this->meta_ad(vec, more);
}

void Strobe128::ad(const std::vector<uint8_t> &data, bool more) {
    this->begin_op(constant::FLAG::A, more);
    this->absorb(data);
}

void Strobe128::ad(const std::string_view &data, bool more) {
    std::vector<uint8_t> vec = str_to_bytes(data);
    this->ad(vec, more);
}

void Strobe128::prf(std::vector<uint8_t> &data, bool more) {
    this->begin_op(constant::FLAG::I | constant::FLAG::A | constant::FLAG::C, more);
    this->squeeze(data);
}

void Strobe128::key(const std::vector<uint8_t> &data, bool more) {
    this->begin_op(constant::FLAG::A | constant::FLAG::C, more);
    this->overwrite(data);
}

void Strobe128::key(std::string_view &data, bool more) {
    std::vector<uint8_t> vec = str_to_bytes(data);
    this->key(vec, more);
}

void Strobe128::run_f() {
    this->state[this->position] ^= this->position_begin;
    this->state[this->position + 1] ^= 0x04;
    this->state[constant::R + 1] ^= 0x80;

    std::array<uint64_t, 25> aggregated_state = aggregate_state(this->state);
    keccak::util::keccak_f(aggregated_state);

    this->state = partition_state(aggregated_state);
    this->position = 0;
    this->position_begin = 0;
}

void Strobe128::absorb(const std::vector<uint8_t> &data) {
    for (uint8_t byte: data) {
        this->state[this->position] ^= byte;
        this->position += 1;
        if (this->position == constant::R)
            this->run_f();
    }
}

void Strobe128::absorb(const std::string_view &data) {
    std::vector<uint8_t> vec = transcript::util::encoding::str_to_bytes(data);
    this->absorb(vec);
}

void Strobe128::overwrite(const std::vector<uint8_t> &data) {
    for (uint8_t byte: data) {
        this->state[this->position] = byte;
        this->position += 1;
        if (this->position == constant::R)
            this->run_f();
    }
}

void Strobe128::overwrite(const std::string_view &data) {
    std::vector<uint8_t> vec = transcript::util::encoding::str_to_bytes(data);
    this->overwrite(vec);
}

void Strobe128::squeeze(std::vector<uint8_t> &data) {
    for (uint8_t &byte: data) {
        byte = this->state[this->position];
        this->state[this->position] = 0;
        this->position += 1;
        if (this->position == constant::R)
            this->run_f();
    }
}

void Strobe128::begin_op(uint8_t flags, bool more) {
    // checks if we are continuing an operation
    if (more) {
        assert(this->current_flags == flags);
        return;
    }

    // skips adjusting direction information (we just use AD, PRF)
    assert((flags & constant::FLAG::T) == 0);

    const uint8_t old_begin = this->position_begin;
    this->position_begin = this->position + 1;
    this->current_flags = flags;

    this->absorb({old_begin, flags});

    const bool force_f = 0 != (flags & (constant::FLAG::C | constant::FLAG::K));
    if (force_f && this->position != 0)
        this->run_f();
}

} // namespace transcript::strobe