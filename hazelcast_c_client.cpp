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

#include <assert.h>
#include <iostream>

using namespace hazelcast::client;
using namespace std;

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
    delete clientConfig->config;
    delete clientConfig;
}

extern "C" void Hazelcast_ClientConfig_add_address(Hazelcast_ClientConfig_t *clientConfig, char *networkAddress, int port)
{
    Address address(networkAddress, port);
    clientConfig->config->addAddress(address);
}

/* Hazelcast_Client */
extern "C" Hazelcast_Client_t *Hazelcast_Client_create(Hazelcast_ClientConfig_t *clientConfig)
{
    Hazelcast_Client_t *client = new Hazelcast_Client_t;
    client->client = new HazelcastClient(*(clientConfig->config));

    return client;
}

extern "C" void Hazelcast_Client_destroy(Hazelcast_Client_t *client)
{
    delete client->client;
    delete client;
}

/** Hazelcast_Map */
extern "C" void Hazelcast_Map_put_int_int(Hazelcast_Client_t *hazelcastClient, const char *mapName, int key, int value)
{
    IMap<int, int> myMap = hazelcastClient->client->getMap<int, int>(mapName);
    myMap.put(key, value);
}

extern "C" int Hazelcast_Map_get_int_int(Hazelcast_Client_t *hazelcastClient, const char *mapName, int key)
{
    IMap<int, int> myMap = hazelcastClient->client->getMap<int, int>(mapName);
    boost::shared_ptr<int> value = myMap.get(key);

    return *(value.get());
}

extern "C" void Hazelcast_Map_put_int_string(Hazelcast_Client_t *hazelcastClient, const char *mapName, int key, const char *value)
{
    // @FIXME should it be string(mapName) and string(value) ?!
    IMap<int, string> myMap = hazelcastClient->client->getMap<int, string>(mapName);
    myMap.put(key, string(value));
}

extern "C" const char *Hazelcast_Map_get_int_string(Hazelcast_Client_t *hazelcastClient, const char *mapName, int key)
{
    // @FIXME should it be string(mapName) and string(value) ?!
    IMap<int, string> myMap = hazelcastClient->client->getMap<int, string>(mapName);
    boost::shared_ptr<string> value = myMap.get(key);

    string strValue = *(value.get());
    return strValue.c_str();
}
