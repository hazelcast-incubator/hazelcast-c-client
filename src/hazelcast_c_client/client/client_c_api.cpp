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
#include "hazelcast_c_client/util/errorhandling.hpp"

using hazelcast::client::HazelcastClient;
using hazelcast::client::ClientConfig;
using hazelcast::client::Address;
using hazelcast::client::LogLevel;
using hazelcast::client::spi::ClientContext;

using hazelcast_c_client::util::saveMessageInErrPtr;
using hazelcast_c_client::util::saveUnknownErrorOccurredMessageInErrPtr;

/* Configuration */
extern "C" Hazelcast_ClientConfig_t* Hazelcast_ClientConfig_create() {
    Hazelcast_ClientConfig_t *clientConfig = new Hazelcast_ClientConfig_t;
    clientConfig->config = new ClientConfig();

    return clientConfig;
}

extern "C" void Hazelcast_ClientConfig_destroy(Hazelcast_ClientConfig_t *clientConfig) {
    if (clientConfig != NULL && clientConfig->config != NULL) {
        delete clientConfig->config;
    }

    if (clientConfig != NULL) {
        delete clientConfig;
    }
}

extern "C" void Hazelcast_ClientConfig_addAddress(
    const Hazelcast_ClientConfig_t *clientConfig,
    const char *networkAddress,
    int port
) {
    assert(clientConfig != NULL);
    assert(clientConfig->config != NULL);

    assert(networkAddress != NULL);
    assert(port >= 0 && port <= 65535);

    Address address(networkAddress, port);
    clientConfig->config->addAddress(address);
}

extern "C" void Hazelcast_ClientConfig_setLogLevel(
    const Hazelcast_ClientConfig_t *clientConfig,
    HAZELCAST_LOG_LEVEL logLevel
) {
    assert(clientConfig != NULL);
    assert(clientConfig->config != NULL);

    switch (logLevel) {
        case HAZELCAST_LOG_LEVEL_SEVERE:
            clientConfig->config->setLogLevel(LogLevel::SEVERE);

            break;

        case HAZELCAST_LOG_LEVEL_WARNING:
            clientConfig->config->setLogLevel(LogLevel::WARNING);

            break;

        case HAZELCAST_LOG_LEVEL_INFO:
            clientConfig->config->setLogLevel(LogLevel::INFO);

            break;

        case HAZELCAST_LOG_LEVEL_FINEST:
            clientConfig->config->setLogLevel(LogLevel::FINEST);

            break;

        default:
            break;
    }
}

/* Client */
extern "C" Hazelcast_Client_t *Hazelcast_Client_create(
    Hazelcast_ClientConfig_t *clientConfig,
    char **errPtr
) {
    assert(clientConfig != NULL);
    assert(clientConfig->config != NULL);

    try {
        Hazelcast_Client_t *client = new Hazelcast_Client_t;
        client->client = new HazelcastClient(*(clientConfig->config));
        client->context = new ClientContext(*client->client);

        return client;
    } catch(const std::runtime_error& re) {
        saveMessageInErrPtr(errPtr, re.what());
    } catch(const std::exception& ex) {
        saveMessageInErrPtr(errPtr, ex.what());
    } catch(...) {
        saveUnknownErrorOccurredMessageInErrPtr(errPtr);
    }

    return NULL;
}

extern "C" void Hazelcast_Client_destroy(Hazelcast_Client_t *client) {
    if (client != NULL && client->client != NULL) {
        delete client->client;
    }

    if (client != NULL && client->context != NULL) {
        delete client->context;
    }

    if (client != NULL) {
        delete client;
    }
}
