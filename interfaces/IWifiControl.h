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

	enum class AutoConnectType : uint8_t {
            NONE,
            PBC/* @text: PBC */,
            PIN/* @text: PIN */
        };

	enum class SecurityType : uint8_t {
            UNKNOWN,
            UNSECURE,
            WPA     /* @text: WPA */,
            WPA2    /* @text: WPA2 */,
            WPA_WPA2/* @text: WPA_WPA2 */,
            ENTERPRISE
        };

	struct NetworkInfo {
            string ssid;
            string bssid;
            uint32_t frequency;
            int32_t signal;
            string pairs; // TODO: expecting this as list of (method + list of keys), it has to be discussed
        };
	using INetworkInfoIterator = RPC::IIteratorType<NetworkInfo, ID_WIFICONTROL_NETWORK_INFO_ITERATOR>;

        struct ConfigInfo {
            bool hidden;
            bool accesspoint;
            string ssid;
            string psk;
            string hash;
            string identity;
            string password;
            SecurityType type;
	};
	using IConfigInfoIterator = RPC::IIteratorType<ConfigInfo, ID_WIFICONTROL_CONFIG_INFO_ITERATOR>;

	// @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_WIFICONTROL_NOTIFICATION };

            // @brief Notifies that Network were added, removed or modified.
            virtual void NetworkChange() = 0;
            // @brief Notifies that wifi connection changes
            virtual void ConnectionChange(const string& ssid) = 0;
            // @brief Notifies Scan results with network Info
	    virtual void ScanResults(INetworkInfoIterator* networkInfoList) = 0;
        };

        virtual uint32_t Register(IWifiControl::INotification* sink) = 0;
        virtual uint32_t Unregister(IWifiControl::INotification* sink) = 0;

        // @property
	virtual uint32_t Networks(INetworkInfoIterator*& networkInfoList /* @out */) const = 0;

	// @property
	virtual uint32_t Pin(string& pin /* @out */) const = 0;

	// @property
        virtual uint32_t Configs(IConfigInfoIterator*& configInfoList /* @out */) const = 0;

	// @property
        virtual uint32_t Config(const string& index /* @index */, ConfigInfo& configInfo /* @out */) const = 0;
        virtual uint32_t Config(const string& index /* @index */, const ConfigInfo& configInfo) = 0;

	virtual uint32_t Debug(const uint32_t level) = 0;

	virtual uint32_t Store() = 0;
        virtual uint32_t Scan() = 0;
        virtual uint32_t Destroy(const string& ssid) = 0;
	virtual uint32_t Connect(const string& ssid, const AutoConnectType type, const string& pin) = 0;
        virtual uint32_t Disconnect(const string& ssid) = 0;
	virtual uint32_t Status(string& connectedSsid /* @out */, bool& isScanning /* @out */) const = 0;
    };
}
}
