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
#include "hazelcast_c_client/util/string.hpp"

#include <string>
#include <type_traits>

using hazelcast::client::serialization::pimpl::Data;

using hazelcast_c_client::util::duplicateString;

/* Serialization functions */
// @FIXME is there any case in which SerializationService::toObject can return NULL?
// @FIXME is there any case where serialization can throw exceptions? (then we need to implement error handling)

template <typename T>
static Hazelcast_Data_t *Hazelcast_Serialization_numberTypeToData(
    const Hazelcast_Client_t *client,
    T value
) {
    static_assert(std::is_arithmetic<T>::value, "Bad T - must be arithmetic type.");

    assert(client != NULL);
    assert(client->context != NULL);

    Data hazelcastData = client->context->getSerializationService().toData(&value);

    Hazelcast_Data_t *data = new Hazelcast_Data_t();
    data->data = hazelcastData;

    return data;
}

template <typename T>
static T Hazelcast_Serialization_dataToNumberType(
    const Hazelcast_Client_t *client,
    const Hazelcast_Data_t *data
) {
    static_assert(std::is_arithmetic<T>::value, "Bad T - must be arithmetic type.");

    assert(client != NULL);
    assert(client->context != NULL);

    assert(data != NULL);

    std::auto_ptr<T> ptr = client->context->getSerializationService().toObject<T>(data->data);
    T *value = ptr.get();
    assert(value != NULL);

    return *value;
}

extern "C" void Hazelcast_Data_destroy(Hazelcast_Data_t *data) {
    if (data != NULL) {
        delete data;
    }
}

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

    const std::string stdString(stringValue, len);
    Data hazelcastData = client->context->getSerializationService().toData(&stdString);

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

    return duplicateString(stringValue->c_str(), stringValue->length());
}

// int
extern "C" Hazelcast_Data_t *Hazelcast_Serialization_intToData(
    const Hazelcast_Client_t *client,
    int intValue
) {
    return Hazelcast_Serialization_numberTypeToData(client, intValue);
}

extern "C" int Hazelcast_Serialization_dataToInt(
    const Hazelcast_Client_t *client,
    const Hazelcast_Data_t *data
) {
    return Hazelcast_Serialization_dataToNumberType<int>(client, data);
}

// float
extern "C" Hazelcast_Data_t *Hazelcast_Serialization_floatToData(
    const Hazelcast_Client_t *client,
    float floatValue
) {
    return Hazelcast_Serialization_numberTypeToData(client, floatValue);
}

extern "C" float Hazelcast_Serialization_dataToFloat(
    const Hazelcast_Client_t *client,
    const Hazelcast_Data_t *data
) {
    return Hazelcast_Serialization_dataToNumberType<float>(client, data);
}

// double
extern "C" Hazelcast_Data_t *Hazelcast_Serialization_doubleToData(
    const Hazelcast_Client_t *client,
    double doubleValue
) {
    return Hazelcast_Serialization_numberTypeToData(client, doubleValue);
}

extern "C" double Hazelcast_Serialization_dataToDouble(
    const Hazelcast_Client_t *client,
    const Hazelcast_Data_t *data
) {
    return Hazelcast_Serialization_dataToNumberType<double>(client, data);
}
