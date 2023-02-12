#ifndef TRANSCRIPT_STROBE_CONSTANT_H
#define TRANSCRIPT_STROBE_CONSTANT_H

#include <cstdint>
#include <string>

namespace transcript::strobe::constant {

const std::string STROBE_TAG = "PARK_HIDE v.1919.810";

const uint8_t R = 166;

const uint8_t FLAG_I = 1;
const uint8_t FLAG_A = 1 << 1;
const uint8_t FLAG_C = 1 << 2;
const uint8_t FLAG_T = 1 << 3;
const uint8_t FLAG_M = 1 << 4;
const uint8_t FLAG_K = 1 << 5;

} // namespace transcript::strobe::constant

#endif //TRANSCRIPT_STROBE_CONSTANT_H