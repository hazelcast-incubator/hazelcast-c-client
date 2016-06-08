[![Build Status](https://travis-ci.org/maxbeutel/hazelcast-c-client.svg?branch=master)](https://travis-ci.org/maxbeutel/hazelcast-c-client)

# C Client bindings for Hazelcast

This is a C client for Hazelcast, which wraps the official Hazelcast C++ client, with the aim to provide an low-level but easy to use and safe C API.

C API is supposed to be somewhat similar to C bindings of [leveldb](https://github.com/google/leveldb/blob/master/include/leveldb/c.h).

The contract is:

  - Just opaque structures are exposed to the client.
  - Errors are represented by a null-terminated c string. NULL means no error.
    All operations that can cause an error are passed a `char** errptr` as the last argument.
    On success, `errptr` is left unchanged.
    On failure, `errptr` contains an `malloc()`ed  error message (usually the C++ exception message). This message must be freed by the caller!
  - Strings returned from the API are`malloc()`ed and must be freed by the caller!
    Unlike leveldb, the function returns `1` on failure and `0` on success, which should be used for easy success/failure checking.
  - All of the pointer arguments must be non-NULL

WARNING: C client is still early stage and therefore super unstable and most likely buggy.

Current state of implementation:

# License

Hazelcast C Client is available under the Apache 2 License.



