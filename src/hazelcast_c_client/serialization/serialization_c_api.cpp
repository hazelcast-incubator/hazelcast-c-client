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
#include "hazelcast_c_client/util/errorhandling.hpp"

#include <string>
#include <type_traits>

using hazelcast::client::serialization::pimpl::Data;

using hazelcast_c_client::util::duplicateString;

using hazelcast_c_client::util::saveMessageInErrPtr;
using hazelcast_c_client::util::saveUnknownErrorOccurredMessageInErrPtr;

/* Serialization functions */
template <typename T>
static Hazelcast_Data_t *Hazelcast_Serialization_numberTypeToData(
    const Hazelcast_Client_t *client,
    T value,
    char **errPtr
) {
    static_assert(std::is_arithmetic<T>::value, "Bad T - must be arithmetic type.");

    assert(client != NULL);
    assert(client->context != NULL);

    try {
        Data hazelcastData = client->context->getSerializationService().toData(&value);

        Hazelcast_Data_t *data = new Hazelcast_Data_t();
        data->data = hazelcastData;

        return data;
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errPtr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errPtr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errPtr);
    }

    return NULL;
}

template <typename T>
static T Hazelcast_Serialization_dataToNumberType(
    const Hazelcast_Client_t *client,
    const Hazelcast_Data_t *data,
    const T defaultValue,
    char **errPtr
) {
    static_assert(std::is_arithmetic<T>::value, "Bad T - must be arithmetic type.");

    assert(client != NULL);
    assert(client->context != NULL);

    assert(data != NULL);

    try {
        std::auto_ptr<T> ptr = client->context->getSerializationService().toObject<T>(data->data);
        T *value = ptr.get();
        assert(value != NULL);

        return *value;
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errPtr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errPtr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errPtr);
    }

    return defaultValue;
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
    size_t len,
    char **errPtr
) {
    assert(client != NULL);
    assert(client->context != NULL);

    assert(stringValue != NULL);

    assert(len > 0);

    try {
        const std::string stdString(stringValue, len);
        Data hazelcastData = client->context->getSerializationService().toData(&stdString);

        Hazelcast_Data_t *data = new Hazelcast_Data_t();
        data->data = hazelcastData;

        return data;
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errPtr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errPtr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errPtr);
    }

    return NULL;
}

extern "C" char *Hazelcast_Serialization_dataToString(
    const Hazelcast_Client_t *client,
    const Hazelcast_Data_t *data,
    char **errPtr
) {
    assert(client != NULL);
    assert(client->context != NULL);

    assert(data != NULL);

    try {
        std::auto_ptr<std::string> stringPtr = client->context->getSerializationService().toObject<std::string>(data->data);
        std::string *stringValue = stringPtr.get();
        assert(stringValue != NULL);

        return duplicateString(stringValue->c_str(), stringValue->length());
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errPtr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errPtr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errPtr);
    }

    return NULL;
}

// int
extern "C" Hazelcast_Data_t *Hazelcast_Serialization_intToData(
    const Hazelcast_Client_t *client,
    int intValue,
    char **errPtr
) {
    return Hazelcast_Serialization_numberTypeToData(
        client,
        intValue,
        errPtr
    );
}

extern "C" int Hazelcast_Serialization_dataToInt(
    const Hazelcast_Client_t *client,
    const Hazelcast_Data_t *data,
    char **errPtr
) {
    return Hazelcast_Serialization_dataToNumberType<int>(
        client,
        data,
        HAZELCAST_UNKNOWN_INT_VALUE,
        errPtr
    );
}

// float
extern "C" Hazelcast_Data_t *Hazelcast_Serialization_floatToData(
    const Hazelcast_Client_t *client,
    float floatValue,
    char **errPtr
) {
    return Hazelcast_Serialization_numberTypeToData(
        client,
        floatValue,
        errPtr
    );
}

extern "C" float Hazelcast_Serialization_dataToFloat(
    const Hazelcast_Client_t *client,
    const Hazelcast_Data_t *data,
    char **errPtr
) {
    return Hazelcast_Serialization_dataToNumberType<float>(
        client,
        data,
        static_cast<float>(HAZELCAST_UNKNOWN_INT_VALUE),
        errPtr
    );
}

// double
extern "C" Hazelcast_Data_t *Hazelcast_Serialization_doubleToData(
    const Hazelcast_Client_t *client,
    double doubleValue,
    char **errPtr
) {
    return Hazelcast_Serialization_numberTypeToData(
        client,
        doubleValue,
        errPtr
    );
}

extern "C" double Hazelcast_Serialization_dataToDouble(
    const Hazelcast_Client_t *client,
    const Hazelcast_Data_t *data,
    char **errPtr
) {
    return Hazelcast_Serialization_dataToNumberType<double>(
        client,
        data,
        static_cast<double>(HAZELCAST_UNKNOWN_INT_VALUE),
        errPtr
    );
}
