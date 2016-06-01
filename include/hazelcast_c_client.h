#include <stdlib.h>

#ifndef _hazelcast_c_client_h
#define _hazelcast_c_client_h

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types */
typedef unsigned char Hazelcast_byte_t;
typedef struct Hazelcast_ClientConfig_t Hazelcast_ClientConfig_t;
typedef struct Hazelcast_Client_t Hazelcast_Client_t;
typedef struct Hazelcast_Data_t Hazelcast_Data_t;

/* Serialization */
// string
extern Hazelcast_Data_t *Hazelcast_Serialization_stringToData(
    const Hazelcast_Client_t *client,
    const char *stringValue,
    size_t len
);

extern const char *Hazelcast_Serialization_dataToString(
    const Hazelcast_Client_t *client,
    const Hazelcast_Data_t *data
);

// integer
extern Hazelcast_Data_t *Hazelcast_Serialization_intToData(
    const Hazelcast_Client_t *client,
    int intValue
);

extern int Hazelcast_Serialization_dataToInt(
    const Hazelcast_Client_t *client,
    const Hazelcast_Data_t *data
);

extern void Hazelcast_Data_destroy(Hazelcast_Data_t *data);

/* Configuration */
extern Hazelcast_ClientConfig_t* Hazelcast_ClientConfig_create();
extern void Hazelcast_ClientConfig_destroy(Hazelcast_ClientConfig_t *clientConfig);
extern void Hazelcast_ClientConfig_add_address(
    const Hazelcast_ClientConfig_t *clientConfig,
    const char *networkAddress,
    int port
);

/* Client */
extern Hazelcast_Client_t *Hazelcast_Client_create(
    Hazelcast_ClientConfig_t *clientConfig,
    char **out_errptr
);

extern void Hazelcast_Client_destroy(Hazelcast_Client_t *client);

/*
   Map operations
   see https://github.com/hazelcast/hazelcast-cpp-client/blob/v3.6.2/hazelcast/include/hazelcast/client/IMap.h
*/
extern void Hazelcast_Map_set(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    const Hazelcast_Data_t *value,
    long ttl,
    char** out_errptr
);

extern const Hazelcast_Data_t *Hazelcast_Map_get(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    char **out_errptr
);

extern int Hazelcast_Map_containsKey(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    char **out_errptr
);

extern void Hazelcast_Map_delete(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    const Hazelcast_Data_t *key,
    char **out_errptr
);

extern int Hazelcast_Map_size(
    const Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    char **out_errptr
);

/* API functions/Helper */
extern void Hazelcast_free(void *ptr);

#define Hazelcast_resetError(V) Hazelcast_free(V); V = NULL;

/* Debug */
//extern void Hazelcast_test();

#ifdef __cplusplus
}  /* end extern "C" */
#endif

#endif
