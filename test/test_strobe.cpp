#include <gtest/gtest.h>

#include <vector>

#include "strobe/strobe_128.h"

TEST(Strobe128, conformance) {
    transcript::strobe::Strobe128 strobe("Conformance Test Protocol");

    std::vector<uint8_t> message(1024, 99);

    strobe.meta_ad("ms", false);
    strobe.meta_ad("g", true);
    strobe.ad(message, false);

    std::vector<uint8_t> prf(32, 0);

    strobe.meta_ad("prf", false);
    strobe.prf(prf, false);


    strobe.meta_ad("key", false);
    strobe.key(prf, false);

    prf = std::vector<uint8_t>(32, 0);

    strobe.meta_ad("prf", false);
    strobe.prf(prf, false);
}