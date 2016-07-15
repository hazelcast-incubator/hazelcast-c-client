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

static inline void assertHazelcastClient(const Hazelcast_Client_t *hazelcastClient) {
    assert(hazelcastClient != NULL);
    assert(hazelcastClient->client != NULL);
    assert(hazelcastClient->context != NULL);
}

static inline void assertHazelcastData(const Hazelcast_Data_t *hazelcastData) {
    assert(hazelcastData != NULL);
}

/* Map operations */
extern void Hazelcast_Map_set(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    const Hazelcast_Data_t *value,
    char** errPtr
) {
    assertHazelcastClient(hazelcastClient);

    assert(mapName != NULL);

    assertHazelcastData(key);
    assertHazelcastData(value);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);
        mapImpl.set(key->data, value->data, -1);
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errPtr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errPtr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errPtr);
    }
}

extern void Hazelcast_Map_setTTL(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    const Hazelcast_Data_t *value,
    long ttl,
    char** errPtr
) {
    assertHazelcastClient(hazelcastClient);

    assert(mapName != NULL);

    assertHazelcastData(key);
    assertHazelcastData(value);

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
    assertHazelcastClient(hazelcastClient);

    assert(mapName != NULL);

    assertHazelcastData(key);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        std::auto_ptr<Data> dataPtr = mapImpl.getData(key->data);
#pragma GCC diagnostic pop

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
    assertHazelcastClient(hazelcastClient);

    assert(mapName != NULL);

    assertHazelcastData(key);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);

        if (mapImpl.containsKey(key->data)) {
            return 1;
        }

        return 0;
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errPtr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errPtr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errPtr);
    }

    return HAZELCAST_UNKNOWN_INT_VALUE;
}

extern int Hazelcast_Map_containsValue(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *value,
    char **errPtr
) {
    assertHazelcastClient(hazelcastClient);

    assert(mapName != NULL);

    assertHazelcastData(value);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);

        if (mapImpl.containsValue(value->data)) {
            return 1;
        }

        return 0;
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errPtr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errPtr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errPtr);
    }

    return HAZELCAST_UNKNOWN_INT_VALUE;
}

extern void Hazelcast_Map_deleteEntry(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    char **errPtr
) {
    assertHazelcastClient(hazelcastClient);

    assert(mapName != NULL);

    assertHazelcastData(key);

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
    assertHazelcastClient(hazelcastClient);

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

    return HAZELCAST_UNKNOWN_INT_VALUE;
}

extern int Hazelcast_Map_isEmpty(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    char **errPtr
) {
    assertHazelcastClient(hazelcastClient);

    assert(mapName != NULL);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);

        if (mapImpl.isEmpty()) {
            return 1;
        }

        return 0;
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errPtr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errPtr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errPtr);
    }

    return HAZELCAST_UNKNOWN_INT_VALUE;
}

extern void Hazelcast_Map_clear(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    char **errPtr
) {
    assertHazelcastClient(hazelcastClient);

    assert(mapName != NULL);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);
        mapImpl.clear();
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errPtr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errPtr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errPtr);
    }
}

extern void Hazelcast_Map_flush(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    char **errPtr
) {
    assertHazelcastClient(hazelcastClient);

    assert(mapName != NULL);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);
        mapImpl.flush();
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errPtr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errPtr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errPtr);
    }
}

extern Hazelcast_Data_t *Hazelcast_Map_put(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    const Hazelcast_Data_t *value,
    char** errPtr
) {
    assertHazelcastClient(hazelcastClient);

    assert(mapName != NULL);

    assertHazelcastData(key);
    assertHazelcastData(value);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        std::auto_ptr<Data> dataPtr = mapImpl.putData(key->data, value->data);
#pragma GCC diagnostic pop

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

extern int Hazelcast_Map_tryPut(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    const Hazelcast_Data_t *value,
    long timeoutInMillis,
    char** errPtr
) {
    assertHazelcastClient(hazelcastClient);

    assert(mapName != NULL);

    assertHazelcastData(key);
    assertHazelcastData(value);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);

        if (mapImpl.tryPut(key->data, value->data, timeoutInMillis)) {
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

    return HAZELCAST_UNKNOWN_INT_VALUE;
}

extern Hazelcast_Data_t *Hazelcast_Map_remove(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    char** errPtr
) {
    assertHazelcastClient(hazelcastClient);

    assert(mapName != NULL);

    assertHazelcastData(key);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        std::auto_ptr<Data> dataPtr = mapImpl.removeData(key->data);
#pragma GCC diagnostic pop

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

extern int Hazelcast_Map_tryRemove(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    long timeoutInMillis,
    char **errPtr
) {
    assertHazelcastClient(hazelcastClient);

    assert(mapName != NULL);

    assertHazelcastData(key);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);

        if (mapImpl.tryRemove(key->data, timeoutInMillis)) {
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

    return HAZELCAST_UNKNOWN_INT_VALUE;
}

extern int Hazelcast_Map_removeKeyValue(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    const Hazelcast_Data_t *value,
    char** errPtr
) {
    assertHazelcastClient(hazelcastClient);

    assert(mapName != NULL);

    assertHazelcastData(key);
    assertHazelcastData(value);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);

        if (mapImpl.remove(key->data, value->data)) {
            return 1;
        }

        return 0;
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errPtr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errPtr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errPtr);
    }

    return HAZELCAST_UNKNOWN_INT_VALUE;
}

extern Hazelcast_Data_t *Hazelcast_Map_putTTL(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    const Hazelcast_Data_t *value,
    long ttlInMillis,
    char** errPtr
) {
    assertHazelcastClient(hazelcastClient);

    assert(mapName != NULL);

    assertHazelcastData(key);
    assertHazelcastData(value);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        std::auto_ptr<Data> dataPtr = mapImpl.putData(key->data, value->data, ttlInMillis);
#pragma GCC diagnostic pop

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

extern void Hazelcast_Map_putTransient(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    const Hazelcast_Data_t *value,
    long ttlInMillis,
    char** errPtr
) {
    assertHazelcastClient(hazelcastClient);

    assert(mapName != NULL);

    assertHazelcastData(key);
    assertHazelcastData(value);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);
        mapImpl.putTransient(key->data, value->data, ttlInMillis);
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errPtr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errPtr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errPtr);
    }
}

extern Hazelcast_Data_t *Hazelcast_Map_putIfAbsent(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    const Hazelcast_Data_t *value,
    char** errPtr
) {
    assertHazelcastClient(hazelcastClient);

    assert(mapName != NULL);

    assertHazelcastData(key);
    assertHazelcastData(value);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        std::auto_ptr<Data> dataPtr = mapImpl.putIfAbsentData(key->data, value->data, -1);
#pragma GCC diagnostic pop

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

extern Hazelcast_Data_t *Hazelcast_Map_putIfAbsentTTL(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    const Hazelcast_Data_t *value,
    long ttlInMillis,
    char** errPtr
) {
    assertHazelcastClient(hazelcastClient);

    assert(mapName != NULL);

    assertHazelcastData(key);
    assertHazelcastData(value);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        std::auto_ptr<Data> dataPtr = mapImpl.putIfAbsentData(key->data, value->data, ttlInMillis);
#pragma GCC diagnostic pop

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

extern int Hazelcast_Map_replaceValue(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    const Hazelcast_Data_t *oldValue,
    const Hazelcast_Data_t *newValue,
    char** errPtr
) {
    assertHazelcastClient(hazelcastClient);

    assert(mapName != NULL);

    assertHazelcastData(oldValue);
    assertHazelcastData(newValue);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);

        if (mapImpl.replace(key->data, oldValue->data, newValue->data)) {
            return 1;
        }

        return 0;
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errPtr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errPtr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errPtr);
    }

    return HAZELCAST_UNKNOWN_INT_VALUE;
}

extern void Hazelcast_Map_lock(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    char** errPtr
) {
    assertHazelcastClient(hazelcastClient);

    assert(mapName != NULL);

    assertHazelcastData(key);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);
        mapImpl.lock(key->data);
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errPtr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errPtr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errPtr);
    }
}

extern void Hazelcast_Map_lockLeaseTime(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    long leaseTime,
    char** errPtr
) {
    assertHazelcastClient(hazelcastClient);

    assert(mapName != NULL);

    assertHazelcastData(key);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);
        mapImpl.lock(key->data, leaseTime);
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errPtr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errPtr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errPtr);
    }
}

extern int Hazelcast_Map_isLocked(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    char** errPtr
) {
    assertHazelcastClient(hazelcastClient);

    assert(mapName != NULL);

    assertHazelcastData(key);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);

        if (mapImpl.isLocked(key->data)) {
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

    return HAZELCAST_UNKNOWN_INT_VALUE;
}

extern int Hazelcast_Map_tryLock(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    char** errPtr
) {
    assertHazelcastClient(hazelcastClient);

    assertHazelcastData(key);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);

        if (mapImpl.tryLock(key->data, 0)) {
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

    return HAZELCAST_UNKNOWN_INT_VALUE;
}

extern int Hazelcast_Map_tryLockLeaseTime(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    long leaseTime,
    char** errPtr
) {
    assertHazelcastClient(hazelcastClient);

    assert(mapName != NULL);

    assertHazelcastData(key);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);

        if (mapImpl.tryLock(key->data, leaseTime)) {
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

    return HAZELCAST_UNKNOWN_INT_VALUE;
}

extern void Hazelcast_Map_unlock(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    char** errPtr
) {
    assertHazelcastClient(hazelcastClient);

    assert(mapName != NULL);

    assertHazelcastData(key);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);
        mapImpl.unlock(key->data);
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errPtr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errPtr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errPtr);
    }
}

extern void Hazelcast_Map_forceUnlock(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    char** errPtr
) {
    assertHazelcastClient(hazelcastClient);

    assert(mapName != NULL);

    assertHazelcastData(key);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);
        mapImpl.unlock(key->data);
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errPtr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errPtr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errPtr);
    }
}

extern void Hazelcast_Map_evict(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    char** errPtr
) {
    assertHazelcastClient(hazelcastClient);

    assert(mapName != NULL);

    assertHazelcastData(key);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);
        mapImpl.evict(key->data);
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errPtr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errPtr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errPtr);
    }
}

extern void Hazelcast_Map_evictAll(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    char **errPtr
) {
    assertHazelcastClient(hazelcastClient);

    assert(mapName != NULL);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);
        mapImpl.evictAll();
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errPtr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errPtr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errPtr);
    }
}

extern void Hazelcast_Map_addIndex(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const char *attribute,
    size_t attribute_len,
    unsigned int ordered,
    char** errPtr
) {
    assertHazelcastClient(hazelcastClient);

    assert(mapName != NULL);

    assert(attribute != NULL);

    try {
        RawDataIMapImpl mapImpl(mapName, hazelcastClient->context);
        mapImpl.addIndex(std::string(attribute, attribute_len), (ordered ? true : false));
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errPtr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errPtr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errPtr);
    }
}

/*

// passing class method as argument

#include <iostream>

class aClass
{
public:
    void aTest(int a, int b) {
        std::cout << "aClass::aTest() " << a << ", " << b << std::endl;
    }
};

template<class T, class V>
void callingFunction(void (aClass::*method)(T, V), aClass& instance, T x, V y) {
    (instance.*method)(x, y);
}

int main(void) {
    aClass a;
    callingFunction<int, int>(&aClass::aTest, a, 3, 4);

    return 0;
}
 */
