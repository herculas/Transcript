#ifndef TRANSCRIPT_STROBE_128_H
#define TRANSCRIPT_STROBE_128_H

#include <array>
#include <string_view>
#include <vector>

namespace transcript::strobe {

using AlignedKeccakState = std::array<uint8_t, 200>;

class Strobe128 {
private:
    uint8_t position;
    uint8_t position_begin;
    uint8_t current_flags;
    AlignedKeccakState state{};

public:
    Strobe128() = delete;
    Strobe128(const Strobe128 &strobe);
    Strobe128(Strobe128 &&strobe) noexcept;

    explicit Strobe128(const std::string_view &protocol_label);

    void meta_ad(const std::vector<uint8_t> &data, bool more);
    void ad(const std::vector<uint8_t> &data, bool more);
    void prf(std::vector<uint8_t> &data, bool more);
    void key(const std::vector<uint8_t> &data, bool more);

    void meta_ad(const std::string_view &data, bool more);
    void ad(const std::string_view &data, bool more);
    void key(std::string_view &data, bool more);

private:
    void run_f();
    void absorb(const std::vector<uint8_t> &data);
    void overwrite(const std::vector<uint8_t> &data);

    void absorb(const std::string_view &data);
    void overwrite(const std::string_view &data);

    void squeeze(std::vector<uint8_t> &data);
    void begin_op(uint8_t flags, bool more);
};

} // namespace transcript::strobe

#endif //TRANSCRIPT_STROBE_128_H