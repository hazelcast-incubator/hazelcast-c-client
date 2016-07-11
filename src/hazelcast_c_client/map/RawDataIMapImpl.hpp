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

#ifndef INCLUDE_HAZELCAST_C_CLIENT_MAP_RAW_DATA_MAP_IMPL_HPP_
#define INCLUDE_HAZELCAST_C_CLIENT_MAP_RAW_DATA_MAP_IMPL_HPP_

#include <hazelcast/client/HazelcastAll.h>

#include <string>

namespace hazelcast_c_client {
    namespace map {
        class RawDataIMapImpl : protected hazelcast::client::proxy::IMapImpl {
         public:
            RawDataIMapImpl(
                const std::string &instanceName,
                hazelcast::client::spi::ClientContext *context): IMapImpl(instanceName, context) {}

            using hazelcast::client::proxy::IMapImpl::set;
            using hazelcast::client::proxy::IMapImpl::getData;
            using hazelcast::client::proxy::IMapImpl::containsKey;
            using hazelcast::client::proxy::IMapImpl::size;
            using hazelcast::client::proxy::IMapImpl::isEmpty;
            using hazelcast::client::proxy::IMapImpl::clear;
            using hazelcast::client::proxy::IMapImpl::containsValue;
            using hazelcast::client::proxy::IMapImpl::putData;
            using hazelcast::client::proxy::IMapImpl::removeData;
            using hazelcast::client::proxy::IMapImpl::remove;
            using hazelcast::client::proxy::IMapImpl::deleteEntry;
            using hazelcast::client::proxy::IMapImpl::flush;
            using hazelcast::client::proxy::IMapImpl::tryRemove;
            using hazelcast::client::proxy::IMapImpl::tryPut;
            using hazelcast::client::proxy::IMapImpl::putTransient;
            using hazelcast::client::proxy::IMapImpl::putIfAbsentData;
            using hazelcast::client::proxy::IMapImpl::replace;
            using hazelcast::client::proxy::IMapImpl::replaceData;
            using hazelcast::client::proxy::IMapImpl::lock;
            using hazelcast::client::proxy::IMapImpl::isLocked;
            using hazelcast::client::proxy::IMapImpl::tryLock;
            using hazelcast::client::proxy::IMapImpl::unlock;
            using hazelcast::client::proxy::IMapImpl::forceUnlock;
            using hazelcast::client::proxy::IMapImpl::evict;
            using hazelcast::client::proxy::IMapImpl::evictAll;
            using hazelcast::client::proxy::IMapImpl::addIndex;
        };
    }
}

#endif
