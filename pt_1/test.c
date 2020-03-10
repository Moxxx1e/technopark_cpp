#include "gtest/gtest.h"
#include "filter.h"

TEST(filter, empty_string)
{
    const char* const string = "";
    ASSERT_EQ(isStringGood(string), 0);
}

TEST(filter, carriage_return_symbol)
{
    ASSERT_EQ(isStringGood("\n"), 0);
}

TEST(isStringGood, three_dif_symbols)
{
    const char* const  test_string = "kol\n";
    ASSERT_EQ(isStringGood(test_string), 1);
}

TEST(isStringGood, usual_string)
{
    ASSERT_EQ(isStringGood("just a usual string\n"), 1);
}

TEST(isStringGood, string_without_carriage)
{
    ASSERT_EQ(isStringGood("just a usual string"), 1);
}

TEST(isStringGood, same_symbols_string)
{
    ASSERT_EQ(isStringGood("kkkkkkk\n"), 0);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

