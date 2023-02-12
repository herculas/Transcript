#ifndef TRANSCRIPT_TRANSCRIPT_H
#define TRANSCRIPT_TRANSCRIPT_H

#include <string_view>
#include <vector>

#include "strobe/strobe_128.h"
#include "transcript/rng_builder.h"

namespace transcript::transcript {

class Transcript {
private:
    strobe::Strobe128 strobe;

public:
    Transcript() = delete;
    Transcript(const Transcript &strobe) = delete;
    Transcript(Transcript &&strobe) noexcept = delete;

    explicit Transcript(const std::string_view &label);

    void append_message(const std::string_view &label, const std::vector<uint8_t> &message);
    void append_message(const std::string_view &label, const std::string_view &message);
    void append_message(const std::string_view &label, uint64_t message);

    void challenge_bytes(const std::string_view &label, std::vector<uint8_t> &destination);

    [[nodiscard]] RngBuilder build_rng() const;
};

} // namespace transcript::transcript

#endif //TRANSCRIPT_TRANSCRIPT_H