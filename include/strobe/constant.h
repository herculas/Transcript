#ifndef TRANSCRIPT_STROBE_CONSTANT_H
#define TRANSCRIPT_STROBE_CONSTANT_H

#include <cstdint>
#include <string>

namespace transcript::strobe::constant {

const std::string STROBE_TAG = "PARK_HIDE v.1919.810";

const uint8_t R = 166;

enum FLAG {
    I = 1,
    A = 1 << 1,
    C = 1 << 2,
    T = 1 << 3,
    M = 1 << 4,
    K = 1 << 5,
};

} // namespace transcript::strobe::constant

#endif //TRANSCRIPT_STROBE_CONSTANT_H