#include <gtest/gtest.h>

#include <vector>

#include "builder/transcript.h"

using transcript::builder::Transcript;

TEST(Transcript, Equivalance) {
    Transcript trans{"test protocol"};
    trans.append_message("some label", "some data");
    std::vector<uint8_t> challenge(32, 0);
    trans.challenge_bytes("challenge", challenge);

    std::vector<uint8_t> challenge_expected{
            0x56, 0x9f, 0x2c, 0x4b, 0xb6, 0xb3, 0xeb, 0x7a,
            0x74, 0x8c, 0xb8, 0xed, 0xca, 0x0a, 0x84, 0x9a,
            0xb7, 0x65, 0xa2, 0x50, 0xce, 0x82, 0x59, 0x05,
            0x88, 0x27, 0x4f, 0x23, 0x42, 0xc3, 0x43, 0x88,
    };
    EXPECT_EQ(challenge, challenge_expected);
}

TEST(Transcript, CopyConstructor) {
    Transcript trans{"test protocol"};
    trans.append_message("some label", "some data");

    Transcript new_trans{trans};
    std::vector<uint8_t> challenge(32, 0);
    new_trans.challenge_bytes("challenge", challenge);

    std::vector<uint8_t> challenge_expected{
            0x56, 0x9f, 0x2c, 0x4b, 0xb6, 0xb3, 0xeb, 0x7a,
            0x74, 0x8c, 0xb8, 0xed, 0xca, 0x0a, 0x84, 0x9a,
            0xb7, 0x65, 0xa2, 0x50, 0xce, 0x82, 0x59, 0x05,
            0x88, 0x27, 0x4f, 0x23, 0x42, 0xc3, 0x43, 0x88,
    };
    EXPECT_EQ(challenge, challenge_expected);
}

TEST(Transcript, EquivalanceComplex) {
    Transcript trans{"test protocol"};
    trans.append_message("step1", "some data");

    Transcript new_trans{trans};
    std::vector<uint8_t> challenge(32, 0);
    const std::vector<uint8_t> data(1024, 99);
    for (int i = 0; i < 32; ++i) {
        new_trans.challenge_bytes("challenge", challenge);
        new_trans.append_message("bigdata", data);
        new_trans.append_message("challengedata", challenge);
    }

    std::vector<uint8_t> challenge_expected{
            0x13, 0x5e, 0xd1, 0x4b, 0x83, 0xe5, 0x8c, 0x11,
            0xc3, 0xaf, 0x31, 0x06, 0xe1, 0x2f, 0x41, 0x2c,
            0x1c, 0xeb, 0x55, 0xe2, 0xc4, 0xcf, 0xe1, 0x25,
            0x53, 0xfb, 0xcf, 0x28, 0x58, 0x51, 0x9e, 0x97,
    };
    EXPECT_EQ(challenge, challenge_expected);
}