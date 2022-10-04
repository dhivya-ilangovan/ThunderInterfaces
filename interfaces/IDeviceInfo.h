/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2021 Metrological
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

    struct EXTERNAL IDeviceInfo : virtual public Core::IUnknown {
        enum { ID = ID_DEVICE_INFO };

        virtual ~IDeviceInfo() override = default;

        virtual uint32_t Configure(const PluginHost::IShell* service) = 0;

        virtual uint32_t SerialNumber(string& serialNumber /* @out */) const = 0;
        virtual uint32_t Sku(string& sku /* @out */) const = 0;
        virtual uint32_t Make(string& make /* @out */) const = 0;
        virtual uint32_t ModelName(string& value/*@out*/) const = 0;
        virtual uint32_t ModelYear(uint16_t& value/*@out*/) const = 0;
        virtual uint32_t FriendlyName(string& value/*@out*/) const = 0;
        virtual uint32_t DeviceType(string& deviceType /* @out */) const = 0;
        virtual uint32_t PlatformName(string& value/*@out*/) const = 0;
        virtual uint32_t DistributorId(string& distributorId /* @out */) const = 0;
    };

    struct EXTERNAL IDeviceAudioCapabilities : virtual public Core::IUnknown {
        enum { ID = ID_DEVICE_AUDIO_CAPABILITIES };

        virtual ~IDeviceAudioCapabilities() override = default;

        enum AudioCapability : uint8_t {
            AUDIOCAPABILITY_NONE,
            ATMOS,
            DD,
            DDPLUS,
            DAD,
            DAPV2,
            MS12
        };

        enum MS12Capability : uint8_t {
            MS12CAPABILITY_NONE,
            DOLBYVOLUME,
            INTELIGENTEQUALIZER,
            DIALOGUEENHANCER
        };

        typedef RPC::IIteratorType<AudioCapability, ID_DEVICE_AUDIO_CAPABILITIES_AUDIO_CAPABILITY> IAudioCapabilityIterator;
        typedef RPC::IIteratorType<MS12Capability, ID_DEVICE_AUDIO_CAPABILITIES_MS12_CAPABILITY> IMS12CapabilityIterator;

        virtual uint32_t SupportedAudioPorts(RPC::IStringIterator*& supportedAudioPorts /* @out */) const = 0;
        virtual uint32_t AudioCapabilities(const string& audioPort /* @in */, IAudioCapabilityIterator*& audioCapabilities /* @out */) const = 0;
        virtual uint32_t MS12Capabilities(const string& audioPort /* @in */, IMS12CapabilityIterator*& ms12Capabilities /* @out */) const = 0;
        virtual uint32_t SupportedMS12AudioProfiles(const string& audioPort /* @in */, RPC::IStringIterator*& supportedMS12AudioProfiles /* @out */) const = 0;
    };

    struct EXTERNAL IDeviceVideoCapabilities : virtual public Core::IUnknown {
        enum { ID = ID_DEVICE_VIDEO_CAPABILITIES };

        virtual ~IDeviceVideoCapabilities() override = default;

        enum CopyProtection : uint8_t {
            HDCP_UNAVAILABLE,
            HDCP_14,
            HDCP_20,
            HDCP_21,
            HDCP_22
        };

        virtual uint32_t SupportedVideoDisplays(RPC::IStringIterator*& supportedVideoDisplays /* @out */) const = 0;
        virtual uint32_t HostEDID(string& edid /* @out */) const = 0;
        virtual uint32_t DefaultResolution(const string& videoDisplay /* @in */, string& defaultResolution /* @out */) const = 0;
        virtual uint32_t SupportedResolutions(const string& videoDisplay /* @in */, RPC::IStringIterator*& supportedResolutions /* @out */) const = 0;
        virtual uint32_t SupportedHdcp(const string& videoDisplay /* @in */, CopyProtection& supportedHDCPVersion /* @out */) const = 0;
        virtual uint32_t HDR(bool& supportsHDR /*@out*/) const = 0;
        virtual uint32_t Atmos(bool& supportsAtmos /*@out*/) const = 0;
        virtual uint32_t CEC(bool& supportsCEC /*@out*/) const = 0;
    };
}
}
