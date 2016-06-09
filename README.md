[![Build Status](https://travis-ci.org/maxbeutel/hazelcast-c-client.svg?branch=master)](https://travis-ci.org/maxbeutel/hazelcast-c-client)

# C Client bindings for Hazelcast

This is a C client for Hazelcast, which wraps the official Hazelcast C++ client, with the aim to provide an low-level but easy to use and safe C API.

C API is supposed to be somewhat similar to C bindings of [leveldb](https://github.com/google/leveldb/blob/master/include/leveldb/c.h).

> **WARNING: C client is still early stage and therefore super unstable and most likely buggy.**
> **WARNING: C client only builds against Hazelcast C++ client 3.6 for now.**

# Compiling

Currently the installation process is a mixture of `ant` and `CMake`. The most convenient installation method, which downloads all external dependencies and builds the client is via:

    ant -v build-c-client
    
This command should be executed in the root directory of the cloned repository.

# Implemented features

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

## Map

    Hazelcast_Map_set();
    Hazelcast_Map_get();
    Hazelcast_Map_containsKey();
    Hazelcast_Map_delete();
    Hazelcast_Map_size();
    
# API Design

## Contract

  - Just opaque structures are exposed to the client.
  - Errors are represented by a null-terminated c string. NULL means no error.
    All operations that can cause an error are passed a `char** errPtr` as the last argument.
    On success, `errPtr` is left unchanged.
    On failure, `errPtr` contains an `malloc()`ed  error message (usually the C++ exception message). This message must be freed by the caller!
  - Strings returned from the API are`malloc()`ed and must be freed by the caller!
  - All of the pointer arguments must be non-NULL

## Design and example of the API    

... TBD ...

## Limitations
    
... TBD ...

## Tests

... TBD ...
    
# Further development

Generally I want to implement a basic set of features for all data structures offered by Hazelcast, although probably not all features of the C++ client can be re-implemented for this C-bindings.

# License

Hazelcast C Client is available under the Apache 2 License.



