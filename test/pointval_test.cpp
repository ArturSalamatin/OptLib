#include <iostream>
#include <optlib/Points/SetOfPoints/PointVals/PointVal.h>
#include <optlib/Points/SetOfPoints/PointVals/PointValOperators.h>

#include <gtest/gtest.h>

using namespace OptLib;

TEST(PointValTest, TestCtors)
{
    PointVal<3> rp;
    rp[1] = 2.4;
    auto rp1{PointVal<3>{rp}};
    auto rp2 = rp1;
    auto rp3 = PointVal<3>{{1.0, 2.0, 3.0}, 3.0};
    auto rp4{std::move(rp2)};
    auto rp5 = std::move(rp4);
}

TEST(PointValTest, TestOperators)
{
    PointVal<3> rp6{{2.0, 1.0, 3.0}, 7.8};
    std::cout << rp6 << std::endl;
    rp6 += 3.0;
    rp6 -= 3.0;

    // auto rp7{rp6 + 1.0};
    // auto rp8{rp6 - 1.0};
    // auto rp9 = rp6 * 2.0;
    // auto rp91 = 2.0 * rp6;
    // auto rp10 = rp6 / 2.0;
    // auto rp11 = abs(rp6);
    // auto rp12 = sqrt(rp6);
    // auto rp13 = rp6 / 2.0;
    // auto rp14 = rp6 / 2.0;
    // auto rp15{1.0 + rp6};
    // auto rp16{1.0 - rp6};

    // auto dp1{dot_product(rp7, rp8)};
    // auto dp2{norm(rp7)};
    // auto dp3{dist(rp7, rp8)};
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}