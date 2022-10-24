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
    struct EXTERNAL IWifiControl : virtual public Core::IUnknown {
        enum { ID = ID_WIFICONTROL };

        enum class SecurityMethod : uint8_t {
            UNKNOWN,
            OPEN,
            WEP     /* @text: WEP */,
            WPA     /* @text: WPA */,
            WPA2    /* @text: WPA2 */,
            WPA_WPA2/* @text: WPA_WPA2 */,
            WPS     /* @text: WPS */,
            ENTERPRISE
        };

        enum SecurityKey : uint8_t {
            PSK = 0x01 /* @text: PSK */,
            EAP = 0x02 /* @text: EAP */,
            CCMP = 0x04 /* @text: CCMP */,
            TKIP = 0x08 /* @text: TKIP */,
            PREAUTH = 0x10,
            PBC = 0x20 /* @text: PBC */,
            PIN = 0x40 /* @text: PIN */,
            NONE = 0x00
        };

        struct PairInfo {
            SecurityMethod method;
            SecurityKey keys;
        };
        using IPairIterator = RPC::IIteratorType<PairInfo, ID_WIFICONTROL_PAIR_ITERATOR>;

        /* @json */
        struct EXTERNAL INetworkInfo : virtual public Core::IUnknown {
            enum { ID = ID_WIFICONTROL_NETWORK_INFO };
            struct EXTERNAL IIterator : virtual public Core::IUnknown {
                enum { ID = ID_WIFICONTROL_NETWORK_INFO_ITERATOR };

                virtual void Reset() = 0;
                virtual bool IsValid() const = 0;
                virtual bool Next() = 0;
                virtual INetworkInfo* Current() = 0;
            };
            virtual uint32_t SSID(string& ssid /* @out */) const = 0;
            virtual uint32_t BSSID(uint64_t& bssid /* @out */) const = 0;
            virtual uint32_t Frequency(uint32_t& frequency /* @out */) const = 0;
            virtual int32_t Signal(uint32_t& signal /* @out */) const = 0;
            virtual uint32_t Pairs(IPairIterator*& pairs /* @out */) const = 0;
        };

        struct ConfigInfo {
            bool hidden;
            bool accesspoint;
            string ssid;
            string psk;
            string hash;
            string identity;
            string password;
            SecurityMethod type;
        };
        using IConfigInfoIterator = RPC::IIteratorType<ConfigInfo, ID_WIFICONTROL_CONFIG_INFO_ITERATOR>;

        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_WIFICONTROL_NOTIFICATION };

            // @brief Notifies that Network were added, removed or modified.
            virtual void NetworkChange(INetworkInfo::IIterator* networkInfoList) = 0;
            // @brief Notifies that wifi connection changes
            virtual void ConnectionChange(const string& ssid) = 0;
        };

        virtual uint32_t Register(IWifiControl::INotification* sink) = 0;
        virtual uint32_t Unregister(IWifiControl::INotification* sink) = 0;

        // @property
        virtual uint32_t Networks(INetworkInfo::IIterator*& networkInfoList /* @out */) const = 0;

        // @property
        virtual uint32_t Pin(string& pin /* @out */) const = 0;

        // @property
        virtual uint32_t Configs(IConfigInfoIterator*& configInfoList /* @out */) const = 0;

        // @property
        virtual uint32_t Config(const string& ssid /* @index */, ConfigInfo& configInfo /* @out */) const = 0;
        virtual uint32_t Config(const string& ssid /* @index */, const ConfigInfo& configInfo) = 0;

        virtual uint32_t Debug(const uint32_t level) = 0;

        virtual uint32_t Store() = 0;
        virtual uint32_t Scan() = 0;
        virtual uint32_t Destroy(const string& ssid) = 0;
        virtual uint32_t Connect(const string& ssid, const SecurityKey key, const string& pin) = 0;
        virtual uint32_t Disconnect(const string& ssid) = 0;
        virtual uint32_t Status(string& connectedSsid /* @out */, bool& isScanning /* @out */) const = 0;
    };
}
}
