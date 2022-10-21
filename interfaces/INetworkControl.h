/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2022 Metrological
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

#pragma once
#include "Module.h"

// @stubgen:include <com/IIteratorType.h>

namespace WPEFramework {
namespace Exchange {

    /* @json */
    struct EXTERNAL INetworkControl : virtual public Core::IUnknown {
        enum { ID = ID_NETWORKCONTROL };

        enum ModeType : uint8_t {
            MANUAL,
            STATIC,
            DYNAMIC
        };

        enum StatusType : uint8_t {
            CREATED,
            UPDATED,
            REMOVED,
            CONNECTED,
            IPASSIGNED,
            CONNECTIONFAILED
        };

        struct ConnectionInfo {
            string name;
            string address;
            StatusType status;
        };

        struct NetworkInfo {
            string interface;
            string address;
            string gateway;
            string broadcast;
            string dns;
            uint8_t mask;
            ModeType mode;
        };

        using INetworkInfoIterator = RPC::IIteratorType<NetworkInfo, ID_NETWORKCONTROL_NETWORK_INFO_ITERATOR>;

        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_NETWORKCONTROL_NOTIFICATION };
            virtual void ConnectionChange(const ConnectionInfo& connectionInfo) = 0;
        };

        virtual uint32_t Register(INetworkControl::INotification* sink) = 0;
        virtual uint32_t Unregister(INetworkControl::INotification* sink) = 0;

        // @property
        virtual uint32_t Network(const string& index /* @index */, INetworkInfoIterator*& networkInfo /* @out */) const = 0;
        virtual uint32_t Network(const string& index /* @index */, INetworkInfoIterator* const& networkInfo /* @in */) = 0;

        // @property
        virtual uint32_t DNS(RPC::IStringIterator*& dns /* @out */) const;
        virtual uint32_t DNS(RPC::IStringIterator* const& dns /* @in */);

        // @property
        virtual uint32_t Up(const string& interface /* @index */, bool& up /* @out */) const; 
        virtual uint32_t Up(const string& interface /* @index */, const bool up /* @in */);

        virtual uint32_t Flush(const string& interface) = 0;
        virtual uint32_t Assign(const string& interface) = 0;
        virtual uint32_t Request(const string& interface) = 0;
        virtual uint32_t Reload(const string& interface) = 0;
    };
}
}
