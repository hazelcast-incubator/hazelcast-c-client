/*
 * Copyright (c) 2016, Max Beutel
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <assert.h>

#include "hazelcast_c_client/util/string.hpp"

#include "gtest/gtest.h"

#include <cstdlib>

using hazelcast_c_client::util::duplicateString;

TEST(Util, DuplicateString) {
    const char *initialString = "some string";
    size_t initialString_len = strlen(initialString);

    char *duplicatedString = duplicateString(initialString, initialString_len);

    ASSERT_STREQ(duplicatedString, initialString);
    ASSERT_EQ(strlen(duplicatedString), initialString_len);

    // assert that string is actually modifiable
    duplicatedString[0] = 'S';
    ASSERT_STREQ(duplicatedString, "Some string");

    free(duplicatedString);
}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

