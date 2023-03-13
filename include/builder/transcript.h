#ifndef TRANSCRIPT_TRANSCRIPT_H
#define TRANSCRIPT_TRANSCRIPT_H

#include <string_view>
#include <vector>

#include "builder/rng_builder.h"
#include "strobe/strobe_128.h"

namespace transcript::builder {

class Transcript {
private:
    strobe::Strobe128 strobe;

public:
    Transcript() = delete;
    Transcript(const Transcript &strobe);
    Transcript(Transcript &&strobe) noexcept;

    explicit Transcript(const std::string_view &label);

    void append_message(const std::string_view &label, const std::vector<uint8_t> &message);
    void append_message(const std::string_view &label, const std::string_view &message);
    void append_message(const std::string_view &label, uint64_t message);

    void challenge_bytes(const std::string_view &label, std::vector<uint8_t> &destination);

    [[nodiscard]] RngBuilder build_rng() const;
};

} // namespace transcript::builder

#endif //TRANSCRIPT_TRANSCRIPT_H