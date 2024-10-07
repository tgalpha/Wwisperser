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

#include "WwisperserFX.h"
#include "../WwisperserConfig.h"

#include <AK/AkWwiseSDKVersion.h>

AK::IAkPlugin* CreateWwisperserFX(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, WwisperserFX());
}

AK::IAkPluginParam* CreateWwisperserFXParams(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, WwisperserFXParams());
}

AK_IMPLEMENT_PLUGIN_FACTORY(WwisperserFX, AkPluginTypeEffect, WwisperserConfig::CompanyID, WwisperserConfig::PluginID)

WwisperserFX::WwisperserFX()
    : m_pParams(nullptr)
    , m_pAllocator(nullptr)
    , m_pContext(nullptr)
{
}

WwisperserFX::~WwisperserFX()
{
}

AKRESULT WwisperserFX::Init(AK::IAkPluginMemAlloc* in_pAllocator, AK::IAkEffectPluginContext* in_pContext, AK::IAkPluginParam* in_pParams, AkAudioFormat& in_rFormat)
{
    m_pParams = (WwisperserFXParams*)in_pParams;
    m_pAllocator = in_pAllocator;
    m_pContext = in_pContext;

    m_uNumChannels = in_rFormat.GetNumChannels();
    m_filter.Init(in_rFormat.uSampleRate, m_pParams->RTPC.uAmount * m_uNumChannels);
    return AK_Success;
}

AKRESULT WwisperserFX::Term(AK::IAkPluginMemAlloc* in_pAllocator)
{
    m_filter.Term();
    AK_PLUGIN_DELETE(in_pAllocator, this);
    return AK_Success;
}

AKRESULT WwisperserFX::Reset()
{
    m_filter.Reset();
    return AK_Success;
}

AKRESULT WwisperserFX::GetPluginInfo(AkPluginInfo& out_rPluginInfo)
{
    out_rPluginInfo.eType = AkPluginTypeEffect;
    out_rPluginInfo.bIsInPlace = true;
	out_rPluginInfo.bCanProcessObjects = false;
    out_rPluginInfo.uBuildVersion = AK_WWISESDK_VERSION_COMBINED;
    return AK_Success;
}

void WwisperserFX::Execute(AkAudioBuffer* io_pBuffer)
{
    HandleParamsChanged();
    io_pBuffer->ZeroPadToMaxFrames();

    for (AkUInt32 uChannel = 0; uChannel < m_uNumChannels; ++uChannel)
    {
        for (AkUInt32 i = 0; i < m_pParams->RTPC.uAmount; ++i)
        {
            m_filter.ProcessChannel(io_pBuffer->GetChannel(uChannel),
                                    i * m_uNumChannels + uChannel,
                                    io_pBuffer->uValidFrames);
        }
    }
}

AKRESULT WwisperserFX::TimeSkip(AkUInt32 in_uFrames)
{
    return AK_DataReady;
}

void WwisperserFX::HandleParamsChanged()
{
    const auto pChangeHandler = m_pParams->GetParamChangeHandler();

    if (pChangeHandler->HasChanged(PARAM_AMOUNT_ID))
    {
        m_filter.Resize(m_pParams->RTPC.uAmount * m_uNumChannels);
    }
    if (pChangeHandler->HasChanged(PARAM_FREQUENCY_ID) || pChangeHandler->HasChanged(PARAM_PINCH_ID))
    {
        m_filter.Config(Wpe::AllPass,
                        m_pParams->RTPC.fFrequency,
                        m_pParams->RTPC.fPinch,
                        0.f);
    }
    pChangeHandler->ResetAllParamChanges();
}
