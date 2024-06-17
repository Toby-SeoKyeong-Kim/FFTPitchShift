//------------------------------------------------------------------------
// Copyright(c) 2024 Toby Corp.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace tobyCorp {
//------------------------------------------------------------------------
static const Steinberg::FUID kFFTPitchShiftProcessorUID (0x20EAD42C, 0x04DE5039, 0x8E7CD9A1, 0xF66C55E8);
static const Steinberg::FUID kFFTPitchShiftControllerUID (0x3E43BE61, 0x456A53F9, 0xAF30ACD9, 0xF1226BBA);

#define FFTPitchShiftVST3Category "Fx"

//------------------------------------------------------------------------
} // namespace tobyCorp
