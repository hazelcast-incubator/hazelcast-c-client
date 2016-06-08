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

#include "hazelcast_c_client/client/client_c_api.hpp"
#include "hazelcast_c_client/serialization/serialization_c_api.hpp"
#include "hazelcast_c_client/util/errorhandling.hpp"
#include "hazelcast_c_client/map/RawDataIMapImpl.hpp"

using hazelcast::client::serialization::pimpl::Data;

using hazelcast_c_client::util::saveMessageInErrPtr;
using hazelcast_c_client::util::saveUnknownErrorOccurredMessageInErrPtr;

using hazelcast_c_client::map::RawDataIMapImpl;

/* Map operations */
extern void Hazelcast_Map_set(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    const Hazelcast_Data_t *value,
    long ttl,
    char** errPtr
) {
    assert(hazelcastClient != NULL);
    assert(hazelcastClient->client != NULL);
    assert(hazelcastClient->context != NULL);

    assert(mapName != NULL);

    assert(key != NULL);
    assert(value != NULL);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);
        mapImpl.set(key->data, value->data, ttl);
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errPtr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errPtr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errPtr);
    }
}

extern Hazelcast_Data_t *Hazelcast_Map_get(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    char **errPtr
) {
    assert(hazelcastClient != NULL);
    assert(hazelcastClient->client != NULL);
    assert(hazelcastClient->context != NULL);

    assert(mapName != NULL);

    assert(key != NULL);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);
        std::auto_ptr<Data> dataPtr = mapImpl.getData(key->data);
        Data *hazelcastData = dataPtr.get();

        if (hazelcastData != NULL) {
            Hazelcast_Data_t *data = new Hazelcast_Data_t();
            data->data = *hazelcastData;

            return data;
        }

        return NULL;
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errPtr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errPtr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errPtr);
    }

    return NULL;
}

extern int Hazelcast_Map_containsKey(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    char **errPtr
) {
    assert(hazelcastClient != NULL);
    assert(hazelcastClient->client != NULL);
    assert(hazelcastClient->context != NULL);

    assert(mapName != NULL);

    assert(key != NULL);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);

        if (mapImpl.containsKey(key->data)) {
            return 1;
        } else {
            return 0;
        }
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errPtr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errPtr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errPtr);
    }

    return -1;
}

extern void Hazelcast_Map_delete(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    char **errPtr
) {
    assert(hazelcastClient != NULL);
    assert(hazelcastClient->client != NULL);
    assert(hazelcastClient->context != NULL);

    assert(mapName != NULL);

    assert(key != NULL);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);
        mapImpl.deleteEntry(key->data);
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errPtr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errPtr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errPtr);
    }
}

extern int Hazelcast_Map_size(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    char **errPtr
) {
    assert(hazelcastClient != NULL);
    assert(hazelcastClient->client != NULL);
    assert(hazelcastClient->context != NULL);

    assert(mapName != NULL);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);
        return mapImpl.size();
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errPtr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errPtr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errPtr);
    }

    return -1;
}
