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

#include "hazelcast_c_client/serialization/serialization_c_api.hpp"
#include "hazelcast_c_client/client/client_c_api.hpp"

#include <string>

using hazelcast::client::HazelcastClient;
using hazelcast::client::ClientConfig;
using hazelcast::client::Address;
using hazelcast::client::LogLevel;
using hazelcast::client::proxy::IMapImpl;
using hazelcast::client::spi::ClientContext;
using hazelcast::client::serialization::pimpl::Data;

/* Serialization functions */
// @FIXME is there any case in which SerializationService::toObject can return NULL?
// @FIXME is there any case where serialization can throw exceptions? (then we need to implement error handling)

// string
extern "C" Hazelcast_Data_t *Hazelcast_Serialization_stringToData(
    const Hazelcast_Client_t *client,
    const char *stringValue,
    size_t len
) {
    assert(client != NULL);
    assert(client->context != NULL);

    assert(stringValue != NULL);

    assert(len > 0);

    const std::string stdstr(stringValue, len);
    Data hazelcastData = client->context->getSerializationService().toData(&stdstr);

    Hazelcast_Data_t *data = new Hazelcast_Data_t();
    data->data = hazelcastData;

    return data;
}

extern "C" char *Hazelcast_Serialization_dataToString(
    const Hazelcast_Client_t *client,
    const Hazelcast_Data_t *data
) {
    assert(client != NULL);
    assert(client->context != NULL);

    assert(data != NULL);

    std::auto_ptr<std::string> stringPtr = client->context->getSerializationService().toObject<std::string>(data->data);
    std::string *stringValue = stringPtr.get();
    assert(stringValue != NULL);

    return strdup(stringValue->c_str());
}

// int
extern "C" Hazelcast_Data_t *Hazelcast_Serialization_intToData(
    const Hazelcast_Client_t *client,
    int intValue
) {
    assert(client != NULL);
    assert(client->context != NULL);

    Data hazelcastData = client->context->getSerializationService().toData(&intValue);

    Hazelcast_Data_t *data = new Hazelcast_Data_t();
    data->data = hazelcastData;

    return data;
}

extern "C" int Hazelcast_Serialization_dataToInt(
    const Hazelcast_Client_t *client,
    const Hazelcast_Data_t *data
) {
    assert(client != NULL);
    assert(client->context != NULL);

    assert(data != NULL);

    std::auto_ptr<int> intPtr = client->context->getSerializationService().toObject<int>(data->data);
    int *intValue = intPtr.get();
    assert(intValue != NULL);

    return *intValue;
}

extern "C" void Hazelcast_Data_destroy(Hazelcast_Data_t *data) {
    if (data != NULL) {
        delete data;
    }
}
