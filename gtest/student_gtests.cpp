#include <gtest/gtest.h>
#include <string.h>

#include <algorithm>

#include "string.hpp"
#include "alloc.hpp"

TEST(StringFunction, strlen) {
    EXPECT_EQ(String::strlen(""), 0);
    EXPECT_EQ(String::strlen("foo"), 3);
}

TEST(StringFunction, strcpy) {
    char result[10];
    EXPECT_EQ(String::strcpy(result, "foo"), result);
    EXPECT_STREQ(result, "foo");

    EXPECT_EQ(String::strcpy(result, "a"), result);
    EXPECT_STREQ(result, "a");

    EXPECT_EQ(String::strcpy(result, ""), result);
    EXPECT_STREQ(result, "");
}

TEST(StringFunction, strdup) {
    const char *src = "ethereal";
    char *copy = String::strdup(src);
    EXPECT_STREQ(copy, "ethereal");
    EXPECT_NE(copy, src);
    delete[] copy;

    char *empty = String::strdup("");
    EXPECT_STREQ(empty, "");
    delete[] empty;
}

TEST(StringFunction, strncpy) {
	char result[20];
    EXPECT_EQ(String::strncpy(result, "altruistic", 10), result);
    EXPECT_STREQ(result, "altruistic");

    EXPECT_EQ(String::strncpy(result, "queen", 12), result);
    EXPECT_STREQ(result, "queen");

    EXPECT_EQ(String::strncpy(result, "whimsical", 0), result);
    EXPECT_STREQ(result, "");

    EXPECT_EQ(String::strncpy(result, "", 5), result);
    EXPECT_STREQ(result, "");
}

TEST(StringFunction, strcat) {
    char a[30] = "star";
    EXPECT_EQ(String::strcat(a, "wings"), a);
    EXPECT_STREQ(a, "starwings");

    char b[30] = "";
    String::strcat(b, "moon");
    EXPECT_STREQ(b, "moon");
}

TEST(StringFunction, strncat) {
    char b[30] = "star";
    String::strncat(b, "signs", 8);
    EXPECT_STREQ(b, "starsigns");

    char c[30] = "wings";
    String::strncat(c, "halloween", 0);
    EXPECT_STREQ(c, "wings");
}

TEST(StringFunction, strcmp) {
    EXPECT_EQ(String::strcmp("", ""), 0);
    EXPECT_LT(String::strcmp("star", "stars"), 0);
    EXPECT_GT(String::strcmp("stars", "star"), 0);
	EXPECT_LT(String::strcmp("", "a"), 0);
}

TEST(StringFunction, strncmp) {
    EXPECT_LT(String::strncmp("constellation", "constellations", 14), 0);
    EXPECT_EQ(String::strncmp("moon", "wings", 0), 0);
    EXPECT_LT(String::strncmp("star", "stars", 5), 0);
}

TEST(StringFunction, reverse_cpy) {
	char result[20];
    String::reverse_cpy(result, "wings");
    EXPECT_STREQ(result, "sgniw");

	String::reverse_cpy(result, "halloween");
    EXPECT_STREQ(result, "neewollah");
}

TEST(StringFunction, strchr) {
    const char *w = "whimsical";
    EXPECT_EQ(String::strchr(w, 'i'), w + 2);
    EXPECT_EQ(String::strchr(w, 'w'), w);
}

TEST(StringFunction, strstr) {
    const char *c = "constellations";
    EXPECT_EQ(String::strstr(c, "const"), c);
    EXPECT_EQ(String::strstr(c, "tions"), c + 9);
    EXPECT_EQ(String::strstr(c, "stel"), c + 3);
    EXPECT_EQ(String::strstr(c, ""), c);
}
