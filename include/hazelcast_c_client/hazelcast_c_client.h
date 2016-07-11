/*
 * Copyright (c) 2016, Contributors
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

#ifndef INCLUDE_HAZELCAST_C_CLIENT_H_
#define INCLUDE_HAZELCAST_C_CLIENT_H_

#include <stdlib.h>

#include <stddef.h>

/* Environment macros

   HAZELCAST_LINKED_AS_SHARED_LIBRARY
                            - Define to 1 when compiling tests that use
                              Google Test as a shared library (known as
                              DLL on Windows).
   HAZELCAST_CREATE_SHARED_LIBRARY
                            - Define to 1 when compiling Google Test itself
                              as a shared library.
*/

// define attribute for exported functions
#ifdef _MSC_VER
# if HAZELCAST_LINKED_AS_SHARED_LIBRARY
#  define HAZELCAST_API_ __declspec(dllimport)
# elif HAZELCAST_CREATE_SHARED_LIBRARY
#  define HAZELCAST_API_ __declspec(dllexport)
# endif
#elif __GNUC__ >= 4 || defined(__clang__)
# define HAZELCAST_API_ __attribute__((visibility ("default")))
#endif // _MSC_VER

#ifndef HAZELCAST_API_
#define HAZELCAST_API_
#endif

/* General macros */

// placeholder value for unknown int values used for returning bool's
#define HAZELCAST_UNKNOWN_INT_VALUE (-1)

/* Exported API */
#ifdef __cplusplus
extern "C" {
#endif

/* Exported types */
typedef unsigned char Hazelcast_byte_t;

typedef struct Hazelcast_ClientConfig_t Hazelcast_ClientConfig_t;

typedef struct Hazelcast_Client_t Hazelcast_Client_t;

typedef struct Hazelcast_Data_t Hazelcast_Data_t;

typedef enum {
    HAZELCAST_LOG_LEVEL_SEVERE = 100,
    HAZELCAST_LOG_LEVEL_WARNING = 90,
    HAZELCAST_LOG_LEVEL_INFO = 50,
    HAZELCAST_LOG_LEVEL_FINEST = 20,
} HAZELCAST_LOG_LEVEL;

/* Serialization */
extern HAZELCAST_API_ void Hazelcast_Data_destroy(Hazelcast_Data_t *data);

// string
extern HAZELCAST_API_ Hazelcast_Data_t *Hazelcast_Serialization_stringToData(
    const Hazelcast_Client_t *client,
    const char *stringValue,
    size_t len
);

extern HAZELCAST_API_ char *Hazelcast_Serialization_dataToString(
    const Hazelcast_Client_t *client,
    const Hazelcast_Data_t *data
);

// integer
extern HAZELCAST_API_ Hazelcast_Data_t *Hazelcast_Serialization_intToData(
    const Hazelcast_Client_t *client,
    int intValue
);

extern HAZELCAST_API_ int Hazelcast_Serialization_dataToInt(
    const Hazelcast_Client_t *client,
    const Hazelcast_Data_t *data
);

// float
extern HAZELCAST_API_ Hazelcast_Data_t *Hazelcast_Serialization_floatToData(
    const Hazelcast_Client_t *client,
    float floatValue
);

extern HAZELCAST_API_ float Hazelcast_Serialization_dataToFloat(
    const Hazelcast_Client_t *client,
    const Hazelcast_Data_t *data
);

// double
extern HAZELCAST_API_ Hazelcast_Data_t *Hazelcast_Serialization_doubleToData(
    const Hazelcast_Client_t *client,
    double doubleValue
);

extern HAZELCAST_API_ double Hazelcast_Serialization_dataToDouble(
    const Hazelcast_Client_t *client,
    const Hazelcast_Data_t *data
);

/* Configuration */
extern HAZELCAST_API_ Hazelcast_ClientConfig_t* Hazelcast_ClientConfig_create();

extern HAZELCAST_API_ void Hazelcast_ClientConfig_destroy(Hazelcast_ClientConfig_t *clientConfig);

extern HAZELCAST_API_ void Hazelcast_ClientConfig_addAddress(
    const Hazelcast_ClientConfig_t *clientConfig,
    const char *networkAddress,
    int port
);

extern HAZELCAST_API_ void Hazelcast_ClientConfig_setLogLevel(
    const Hazelcast_ClientConfig_t *clientConfig,
    HAZELCAST_LOG_LEVEL logLevel
);

/* Client */
extern HAZELCAST_API_ Hazelcast_Client_t *Hazelcast_Client_create(
    Hazelcast_ClientConfig_t *clientConfig,
    char **errPtr
);

extern HAZELCAST_API_ void Hazelcast_Client_destroy(Hazelcast_Client_t *client);

/*
   Map operations
   see https://github.com/hazelcast/hazelcast-cpp-client/blob/v3.6.2/hazelcast/include/hazelcast/client/IMap.h
*/

extern HAZELCAST_API_ void Hazelcast_Map_set(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    const Hazelcast_Data_t *value,
    char** errPtr
);

extern HAZELCAST_API_ void Hazelcast_Map_setTTL(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    const Hazelcast_Data_t *value,
    long ttl,
    char** errPtr
);

extern HAZELCAST_API_ Hazelcast_Data_t *Hazelcast_Map_get(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    char **errPtr
);

extern HAZELCAST_API_ int Hazelcast_Map_containsKey(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    char **errPtr
);

extern HAZELCAST_API_ int Hazelcast_Map_containsValue(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *value,
    char **errPtr
);

extern HAZELCAST_API_ void Hazelcast_Map_deleteEntry(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    char **errPtr
);

extern HAZELCAST_API_ int Hazelcast_Map_removeKeyValue(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    const Hazelcast_Data_t *value,
    char** errPtr
);

extern HAZELCAST_API_ Hazelcast_Data_t *Hazelcast_Map_remove(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    char** errPtr
);

extern HAZELCAST_API_ Hazelcast_Data_t *Hazelcast_Map_put(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    const Hazelcast_Data_t *value,
    char** errPtr
);

extern HAZELCAST_API_ int Hazelcast_Map_tryRemove(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    long timeoutInMillis,
    char **errPtr
);

extern HAZELCAST_API_ int Hazelcast_Map_tryPut(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    const Hazelcast_Data_t *value,
    long timeoutInMillis,
    char** errPtr
);

extern HAZELCAST_API_ int Hazelcast_Map_size(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    char **errPtr
);

extern HAZELCAST_API_ int Hazelcast_Map_isEmpty(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    char **errPtr
);

extern HAZELCAST_API_ void Hazelcast_Map_flush(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    char **errPtr
);

extern HAZELCAST_API_ void Hazelcast_Map_clear(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    char **errPtr
);

extern HAZELCAST_API_ void Hazelcast_Map_evictAll(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    char **errPtr
);

extern HAZELCAST_API_ void Hazelcast_Map_evict(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    char** errPtr
);

extern HAZELCAST_API_ void Hazelcast_Map_lock(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    char** errPtr
);

extern HAZELCAST_API_ void Hazelcast_Map_lockLeaseTime(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    long leaseTime,
    char** errPtr
);

extern HAZELCAST_API_ int Hazelcast_Map_isLocked(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    char** errPtr
);

extern HAZELCAST_API_ int Hazelcast_Map_tryLock(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    char** errPtr
);

extern HAZELCAST_API_ int Hazelcast_Map_tryLockLeaseTime(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    long leaseTime,
    char** errPtr
);

extern HAZELCAST_API_ void Hazelcast_Map_unlock(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    char** errPtr
);

extern HAZELCAST_API_ void Hazelcast_Map_forceUnlock(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    char** errPtr
);

extern HAZELCAST_API_ void Hazelcast_Map_addIndex(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const char *attribute,
    size_t attribute_len,
    unsigned int ordered,
    char** errPtr
);

extern HAZELCAST_API_ Hazelcast_Data_t *Hazelcast_Map_replace(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    const Hazelcast_Data_t *value,
    char** errPtr
);

extern HAZELCAST_API_ int Hazelcast_Map_replaceValue(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    const Hazelcast_Data_t *oldValue,
    const Hazelcast_Data_t *newValue,
    char** errPtr
);

extern HAZELCAST_API_ Hazelcast_Data_t *Hazelcast_Map_putTTL(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    const Hazelcast_Data_t *value,
    long ttlInMillis,
    char** errPtr
);

extern HAZELCAST_API_ void Hazelcast_Map_putTransient(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    const Hazelcast_Data_t *value,
    long ttlInMillis,
    char** errPtr
);

extern HAZELCAST_API_ Hazelcast_Data_t *Hazelcast_Map_putIfAbsent(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    const Hazelcast_Data_t *value,
    char** errPtr
);

extern HAZELCAST_API_ Hazelcast_Data_t *Hazelcast_Map_putIfAbsentTTL(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    const Hazelcast_Data_t *value,
    long ttlInMillis,
    char** errPtr
);

#define Hazelcast_resetError(V) free(V); \
    V = NULL;

#ifdef __cplusplus
}  /* end extern "C" */
#endif

#endif // INCLUDE_HAZELCAST_C_CLIENT_H_
