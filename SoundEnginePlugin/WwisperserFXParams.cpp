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

#include "WwisperserFXParams.h"

#include <AK/Tools/Common/AkBankReadHelpers.h>

WwisperserFXParams::WwisperserFXParams()
{
}

WwisperserFXParams::~WwisperserFXParams()
{
}

WwisperserFXParams::WwisperserFXParams(const WwisperserFXParams& in_rParams)
{
    InnerType = in_rParams.InnerType;
    RTPC = in_rParams.RTPC;
    NonRTPC = in_rParams.NonRTPC;
    m_paramChangeHandler.SetAllParamChanges();
}

AK::IAkPluginParam* WwisperserFXParams::Clone(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, WwisperserFXParams(*this));
}

AKRESULT WwisperserFXParams::Init(AK::IAkPluginMemAlloc* in_pAllocator, const void* in_pParamsBlock, AkUInt32 in_ulBlockSize)
{
    if (in_ulBlockSize == 0)
    {
        // Initialize default parameters here
        // [ParameterInitialization]
        RTPC.uAmount = 0;
        RTPC.fFrequency = 600;
        RTPC.fPinch = 0.3;
        // [/ParameterInitialization]
        m_paramChangeHandler.SetAllParamChanges();
        return AK_Success;
    }

    return SetParamsBlock(in_pParamsBlock, in_ulBlockSize);
}

AKRESULT WwisperserFXParams::Term(AK::IAkPluginMemAlloc* in_pAllocator)
{
    AK_PLUGIN_DELETE(in_pAllocator, this);
    return AK_Success;
}

AKRESULT WwisperserFXParams::SetParamsBlock(const void* in_pParamsBlock, AkUInt32 in_ulBlockSize)
{
    AKRESULT eResult = AK_Success;
    AkUInt8* pParamsBlock = (AkUInt8*)in_pParamsBlock;

    // Read bank data here
    // [ReadBankData]
    RTPC.uAmount = READBANKDATA(AkUInt32, pParamsBlock, in_ulBlockSize);
    RTPC.fFrequency = READBANKDATA(AkReal32, pParamsBlock, in_ulBlockSize);
    RTPC.fPinch = READBANKDATA(AkReal32, pParamsBlock, in_ulBlockSize);
    // [/ReadBankData]
    CHECKBANKDATASIZE(in_ulBlockSize, eResult);
    m_paramChangeHandler.SetAllParamChanges();

    return eResult;
}

AKRESULT WwisperserFXParams::SetParam(AkPluginParamID in_paramID, const void* in_pValue, AkUInt32 in_ulParamSize)
{
    AKRESULT eResult = AK_Success;

    // Handle parameter change here
    switch (in_paramID)
    {
    // [SetParameters]
    case PARAM_AMOUNT_ID:
        RTPC.uAmount = static_cast<AkUInt32>(*(AkReal32*)in_pValue);
        m_paramChangeHandler.SetParamChange(PARAM_AMOUNT_ID);
        break;
    case PARAM_FREQUENCY_ID:
        RTPC.fFrequency = *((AkReal32*)in_pValue);
        m_paramChangeHandler.SetParamChange(PARAM_FREQUENCY_ID);
        break;
    case PARAM_PINCH_ID:
        RTPC.fPinch = *((AkReal32*)in_pValue);
        m_paramChangeHandler.SetParamChange(PARAM_PINCH_ID);
        break;
    // [/SetParameters]
    default:
        eResult = AK_InvalidParameter;
        break;
    }

    return eResult;
}
