#include <gtest/gtest.h>

#include <vector>

#include "builder/transcript.h"

TEST(Transcript, Equivalance) {
    transcript::builder::Transcript trans{"test protocol"};
    trans.append_message("some label", "some data");
    std::vector<uint8_t> challenge(32, 0);
    trans.challenge_bytes("challenge", challenge);
}

TEST(Transcript, EquivalanceComplex) {
    transcript::builder::Transcript trans{"test protocol"};
    const std::vector<uint8_t> data(1024, 99);
    trans.append_message("step1", "some data");
    std::vector<uint8_t> challenge(32, 0);
    for (int i = 0; i < 32; ++i) {
        trans.challenge_bytes("challenge", challenge);
        trans.append_message("bigdata", data);
        trans.append_message("challengedata", challenge);
    }
}