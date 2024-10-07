/*******************************************************************************
The content of this file includes portions of the AUDIOKINETIC Wwise Technology
released in source code form as part of the SDK installer package.

Commercial License Usage

Licensees holding valid commercial licenses to the AUDIOKINETIC Wwise Technology
may use this file in accordance with the end user license agreement provided
with the software or, alternatively, in accordance with the terms contained in a
written agreement between you and Audiokinetic Inc.

Apache License Usage

Alternatively, this file may be used under the Apache License, Version 2.0 (the
"Apache License"); you may not use this file except in compliance with the
Apache License. You may obtain a copy of the Apache License at
http://www.apache.org/licenses/LICENSE-2.0.

Unless required by applicable law or agreed to in writing, software distributed
under the Apache License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES
OR CONDITIONS OF ANY KIND, either express or implied. See the Apache License for
the specific language governing permissions and limitations under the License.

  Copyright (c) 2021 Audiokinetic Inc.
*******************************************************************************/
// [wp-enhanced template] **Do not delete this line**

#include "WwisperserPlugin.h"
#include "../SoundEnginePlugin/WwisperserFXFactory.h"

// [PropertyNames]
const char* const szAmount = "Amount";
const char* const szFrequency = "Frequency";
const char* const szPinch = "Pinch";
// [/PropertyNames]

WwisperserPlugin::WwisperserPlugin()
{
}

WwisperserPlugin::~WwisperserPlugin()
{
}

bool WwisperserPlugin::GetBankParameters(const GUID & in_guidPlatform, AK::Wwise::Plugin::DataWriter& in_dataWriter) const
{
    // Write bank data here
    // [WriteBankData]
    in_dataWriter.WriteUInt32(m_propertySet.GetUInt32(in_guidPlatform, szAmount));
    in_dataWriter.WriteReal32(m_propertySet.GetReal32(in_guidPlatform, szFrequency));
    in_dataWriter.WriteReal32(m_propertySet.GetReal32(in_guidPlatform, szPinch));
    // [/WriteBankData]

    return true;
}

DEFINE_AUDIOPLUGIN_CONTAINER(Wwisperser);											// Create a PluginContainer structure that contains the info for our plugin
EXPORT_AUDIOPLUGIN_CONTAINER(Wwisperser);											// This is a DLL, we want to have a standardized name
ADD_AUDIOPLUGIN_CLASS_TO_CONTAINER(                                             // Add our CLI class to the PluginContainer
    Wwisperser,        // Name of the plug-in container for this shared library
    WwisperserPlugin,  // Authoring plug-in class to add to the plug-in container
    WwisperserFX       // Corresponding Sound Engine plug-in class
);
DEFINE_PLUGIN_REGISTER_HOOK

DEFINEDUMMYASSERTHOOK;							// Placeholder assert hook for Wwise plug-ins using AKASSERT (cassert used by default)
