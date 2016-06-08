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

#include "hazelcast_c_client/util/errorhandling.hpp"
#include "hazelcast_c_client/util/string.hpp"

#include <assert.h>
#include <string>

namespace hazelcast_c_client {
    namespace util {
        void saveMessageInErrPtr(char **errPtr, const char *message) {
            assert(errPtr != NULL);

            if (message == NULL) {
                const char *defaultMessage = "(HAZELCAST ERROR occurred, but message was empty)";
                size_t defaultMessage_len = strlen(defaultMessage);

                *errPtr = duplicateString(defaultMessage, defaultMessage_len);
            } else {
                size_t message_len = strlen(message);

                // let's be nice
                if (*errPtr != NULL) {
                    free(*errPtr);
                }

                *errPtr = duplicateString(message, message_len);
            }
        }

        void saveUnknownErrorOccurredMessageInErrPtr(char **errPtr) {
            assert(errPtr != NULL);

            saveMessageInErrPtr(errPtr, "Unknown failure occurred. Possible memory corruption.");
        }
    }
}
