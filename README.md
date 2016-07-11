[![Build Status](https://travis-ci.org/maxbeutel/hazelcast-c-client.svg?branch=master)](https://travis-ci.org/maxbeutel/hazelcast-c-client)

# C Client bindings for Hazelcast

This is a C client for Hazelcast, which wraps the official Hazelcast C++ client, with the aim to provide an low-level but easy to use and safe C API.

C API is supposed to be somewhat similar to C bindings of [leveldb](https://github.com/google/leveldb/blob/master/include/leveldb/c.h).

> **WARNING: C client is still early stage and therefore super unstable and most likely buggy. See also LIMITATIONS!**

# Compiling

Currently the installation process is a mixture of `ant` and `CMake`. The most convenient installation method, which downloads all external dependencies and builds the client is via:

    ant -v build-c-client

This command should be executed in the root directory of the cloned repository.

> **WARNING: Compilation only tested on OS X and Debian with gcc++ and clang**

# API overview

## Client

    Hazelcast_ClientConfig_create();
    Hazelcast_ClientConfig_destroy();

    Hazelcast_ClientConfig_addAddress();
    Hazelcast_ClientConfig_setLogLevel();

    Hazelcast_Client_create();
    Hazelcast_Client_destroy();

## Serialization

    Hazelcast_Serialization_stringToData();
    Hazelcast_Serialization_dataToString();

    Hazelcast_Serialization_intToData();
    Hazelcast_Serialization_dataToInt();

    Hazelcast_Serialization_floatToData();
    Hazelcast_Serialization_dataToFloat();

    Hazelcast_Serialization_doubleToData();
    Hazelcast_Serialization_dataToDouble();

## Map

    Hazelcast_Map_set();
    Hazelcast_Map_get();
    Hazelcast_Map_containsKey();
    Hazelcast_Map_deleteEntry();
    Hazelcast_Map_size();

# API design

## Contract

  - Just opaque structures are exposed to the client.
  - Errors are represented by a null-terminated C string. NULL means no error.
    All operations that can cause an error are passed a `char** errPtr` as the last argument.
    On success, `errPtr` is left unchanged.
    On failure, `errPtr` contains an `malloc()`ed  error message (usually the C++ exception message). This message must be freed by the caller!
  - Strings returned from the API are`malloc()`ed and must be freed by the caller!
  - All of the pointer arguments must be non-NULL

## Design and example of the API

Hazelcast C++ client API uses typed datastructure instances using templates, like `Map<string, int>`. In order to be still able to interact with Hazelcast data structures, C client applications must serialize their data before storing data in Hazelcast. Likewise, data must be deserialized when retrieving from Hazelcast.

Example of storing a string in Hazelcast via C API:

    ...

    const char *rawKey = "map_key";
    const char *rawValue = "map_value";

    Hazelcast_Data_t *keyData = Hazelcast_Serialization_stringToData(client, rawKey, strlen(rawKey));
    Hazelcast_Data_t *valueData = Hazelcast_Serialization_stringToData(client, rawValue, strlen(rawValue));

    Hazelcast_Map_set(client, TEST_MAP_NAME, keyData, valueData, &errPtr);
    assert(errPtr == NULL);

    // free serialized data!
    Hazelcast_Data_destroy(keyData);
    Hazelcast_Data_destroy(valueData);

    ...

`Hazelcast_Serialization` functions use the serialization functionality of the Hazelcast C++ client internally.

## Limitations

Only a subset of client options is implemented, you can:

  - Create a new client instance.
  - Register Hazelcast nodes with the client.
  - Set log level of Hazelcast client (by default, log level of C++ client is used)

Only `Map` data structures can be accessed for now.

Only `char *`, `int`, `float`, `double` values can be serialized.

Only Hazelcast 3.6 is supported for now.

## Tests/Coding Style

Hazelcast C Client uses Google Test as unit test framework. Tests can be found in `test` folder.

Before tests are run, a new Hazelcast server is started to listen on localhost, so that integration tests against a real running server can be executed.

This project adapts Google's C++ Coding Style guidelines, which are enforced via `cpplint`.

Run tests via `ant -v tests`, run code style analysis via `ant -v codestyle`.

# Further development

Generally I want to implement a basic set of features for all data structures offered by Hazelcast, although probably not all features of the C++ client can be re-implemented for this C-bindings.

# License

Hazelcast C Client is available under the Apache 2 License.
