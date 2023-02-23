#ifndef TRANSCRIPT_ENCODE_H
#define TRANSCRIPT_ENCODE_H

#include <string_view>
#include <vector>

namespace transcript::util::encoding {

std::vector<uint8_t> str_to_bytes(const std::string_view &str) {
    std::vector<uint8_t> res;
    res.reserve(str.size());
    for (char i: str) res.push_back(i);
    return res;
}

} // namespace keccak::util::encoding

#endif //TRANSCRIPT_ENCODE_H