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

#ifndef INCLUDE_HAZELCAST_C_CLIENT_UTIL_ERRORHANDLING_HPP_
#define INCLUDE_HAZELCAST_C_CLIENT_UTIL_ERRORHANDLING_HPP_

#include <assert.h>

#include <string>

namespace hazelcast_c_client {
    namespace util {
        void saveMessageInErrPtr(char **errPtr, const char *message);

        void saveUnknownErrorOccurredMessageInErrPtr(char **errPtr);
    }
}

#endif
