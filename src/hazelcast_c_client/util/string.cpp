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
#include <stdlib.h>

#include <algorithm>

#include "hazelcast_c_client/util/string.hpp"

namespace hazelcast_c_client {
    namespace util {
        char *duplicateString(const char *from, size_t from_len) {
            assert(from != NULL);
            assert(from_len > 0);

            char *to = reinterpret_cast<char *>(malloc(from_len + 1));
            assert(to != NULL);

            std::copy(from, from + from_len, to);
            to[from_len] = '\0';

            return to;
        }
    }
}
