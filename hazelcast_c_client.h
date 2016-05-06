#ifndef _hazelcast_c_client_h
#define _hazelcast_c_client_h

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types */
typedef struct Hazelcast_ClientConfig_t Hazelcast_ClientConfig_t;
typedef struct Hazelcast_Client_t Hazelcast_Client_t;

/* Configuration */
extern Hazelcast_ClientConfig_t* Hazelcast_ClientConfig_create();
extern void Hazelcast_ClientConfig_destroy(Hazelcast_ClientConfig_t *clientConfig);
extern void Hazelcast_ClientConfig_add_address(
    Hazelcast_ClientConfig_t *clientConfig,
    char *networkAddress,
    int port
);

/* Client operations */
extern int Hazelcast_Client_create(
    Hazelcast_ClientConfig_t *clientConfig,
    Hazelcast_Client_t **client,
    char** errptr
);

extern void Hazelcast_Client_destroy(Hazelcast_Client_t *client);

/* Map */
extern int Hazelcast_Map_put_int_int(
    Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    int key,
    int value,
    char** errptr
);

extern int Hazelcast_Map_get_int_int(
    Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    int key,
    int *value,
    char** errptr
);

extern int Hazelcast_Map_put_int_string(
    Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    int key,
    const char *value,
    char** errptr
);

extern int Hazelcast_Map_get_int_string(
    Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    int key,
    char **value,
    char** errptr
);

/* General functions */
extern void Hazelcast_free(void *ptr);

#ifdef __cplusplus
}  /* end extern "C" */
#endif

#endif
