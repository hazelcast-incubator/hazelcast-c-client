//
// export hazelcast methods
//
// http://www.oracle.com/technetwork/articles/servers-storage-dev/mixingcandcpluspluscode-305840.html#cpp_from_c
// https://isocpp.org/wiki/faq/mixing-c-and-cpp
// https://github.com/emnl/leveldb-c-example/blob/master/leveldb_example.c
// https://github.com/google/leveldb/blob/7306ef856a91e462a73ff1832c1fa8771008ba36/db/c.cc
//

#include "hazelcast_c_client.h"

#include <hazelcast/client/HazelcastAll.h>

#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Debug
#include <iostream>

using namespace hazelcast::client;
using namespace std;

/* Internal */
static void saveMessageInErrPtr(char **errptr, const char *message)
{
    assert(errptr != NULL);

    if (message == NULL) {
        *errptr = strdup("(HAZELCAST ERROR occurred, but message was empty)");
    } else {
        if (*errptr == NULL) {
            *errptr = strdup(message);
        } else {
            free(*errptr);
            *errptr = strdup(message);
        }
    }
}

static void saveUnknownErrorOccurredMessageInErrPtr(char **errptr)
{
    assert(errptr != NULL);

    saveMessageInErrPtr(errptr, "Unknown failure occurred. Possible memory corruption.");
}

//template<typename T>
static int tryExecute(function<void()> f, char **errptr)
{
    try {
        f();

        return 0;
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errptr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errptr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errptr);
    }

    return 1;
}

/* Exported types */
extern "C" struct Hazelcast_ClientConfig_t { ClientConfig *config; };
extern "C" struct Hazelcast_Client_t { HazelcastClient *client; };

/* Hazelcast_ClientConfig */
extern "C" Hazelcast_ClientConfig_t* Hazelcast_ClientConfig_create()
{
     Hazelcast_ClientConfig_t *clientConfig = new Hazelcast_ClientConfig_t;
     clientConfig->config = new ClientConfig();

     return clientConfig;
}

extern "C" void Hazelcast_ClientConfig_destroy(Hazelcast_ClientConfig_t *clientConfig)
{
    if (clientConfig != NULL && clientConfig->config != NULL) {
        delete clientConfig->config;
    }

    if (clientConfig != NULL) {
        delete clientConfig;
    }
}

extern "C" void Hazelcast_ClientConfig_add_address(Hazelcast_ClientConfig_t *clientConfig, char *networkAddress, int port)
{
    assert(clientConfig != NULL);
    assert(clientConfig->config != NULL);

    assert(networkAddress != NULL);
    assert(port >= 0 && port <= 65535);

    Address address(networkAddress, port);
    clientConfig->config->addAddress(address);
}

/* Hazelcast_Client */
extern "C" Hazelcast_Client_t *Hazelcast_Client_create(
    Hazelcast_ClientConfig_t *clientConfig,
    char** errptr
) {
    assert(clientConfig != NULL);
    assert(clientConfig->config != NULL);

    try {
        Hazelcast_Client_t *client = new Hazelcast_Client_t;
        client->client = new HazelcastClient(*(clientConfig->config));

        return client;
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errptr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errptr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errptr);
    }

    return NULL;
}

extern "C" void Hazelcast_Client_destroy(Hazelcast_Client_t *client)
{
    if (client != NULL && client->client != NULL) {
        delete client->client;
    }

    if (client != NULL) {
        delete client;
    }
}

/** Hazelcast_Map */
extern "C" int Hazelcast_Map_put_int_int(
    Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    int key,
    int value,
    char** errptr
) {
    assert(hazelcastClient != NULL);
    assert(hazelcastClient->client != NULL);

    assert(mapName != NULL);

    function<void()> func = [&]() {
        IMap<int, int> map = hazelcastClient->client->getMap<int, int>(mapName);
        map.put(key, value);
    };

    return tryExecute(func, errptr);
}

extern "C" int Hazelcast_Map_get_int_int(
    Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    int key,
    int *value,
    char** errptr
) {
    assert(hazelcastClient != NULL);
    assert(hazelcastClient->client != NULL);

    assert(mapName != NULL);

    assert(value != NULL);

    try {
        IMap<int, int> map = hazelcastClient->client->getMap<int, int>(mapName);
        boost::shared_ptr<int> intSharedPtr = map.get(key);

        int *intPtr = intSharedPtr.get();

        if (intPtr == NULL) {
            return 0;
        }

        *value = *intPtr;

        return 0;
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errptr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errptr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errptr);
    }

    return 1;
}

extern "C" int Hazelcast_Map_put_int_string(
    Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    int key,
    const char *value,
    char** errptr
) {
    assert(hazelcastClient != NULL);
    assert(hazelcastClient->client != NULL);

    assert(mapName != NULL);

    function<void()> func = [&]() {
        IMap<int, string> map = hazelcastClient->client->getMap<int, string>(mapName);
        map.put(key, string(value));
    };

    return tryExecute(func, errptr);
}

extern "C" int Hazelcast_Map_get_int_string(
    Hazelcast_Client_t *hazelcastClient,
    const char *mapName,
    int key,
    char **value,
    char** errptr
) {
    assert(hazelcastClient != NULL);
    assert(hazelcastClient->client != NULL);

    assert(mapName != NULL);

    assert(value != NULL);

    try {
        IMap<int, string> map = hazelcastClient->client->getMap<int, string>(mapName);
        boost::shared_ptr<string> stringSharedPtr = map.get(key);

        string *stringPtr = stringSharedPtr.get();

        if (stringPtr == NULL) {
            return 0;
        }

        *value = strdup(stringPtr->c_str());
        return 0;
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errptr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errptr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errptr);
    }

    return 1;
}

/* General functions */
extern "C" void Hazelcast_free(void *ptr)
{
    free(ptr);
}
