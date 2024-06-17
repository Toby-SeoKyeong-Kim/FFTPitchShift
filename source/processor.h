//------------------------------------------------------------------------
// Copyright(c) 2024 Toby Corp.
//------------------------------------------------------------------------

#pragma once

#include "public.sdk/source/vst/vstaudioeffect.h"
#include <complex>
#include <valarray>

typedef std::complex<float> Complex;
typedef std::valarray<Complex> CArray;

using namespace Steinberg;
namespace tobyCorp {

//------------------------------------------------------------------------
//  FFTPitchShiftProcessor
//------------------------------------------------------------------------
class FFTPitchShiftProcessor : public Steinberg::Vst::AudioEffect
{
public:
	FFTPitchShiftProcessor ();
	~FFTPitchShiftProcessor () SMTG_OVERRIDE;

    // Create function
	static Steinberg::FUnknown* createInstance (void* /*context*/) 
	{ 
		return (Steinberg::Vst::IAudioProcessor*)new FFTPitchShiftProcessor; 
	}
    float getfPitchRatio(float& val);
    float wrapPhase(float phaseIn);
    Steinberg::int32 wrapIndex(Steinberg::int32& val, const Steinberg::int32 maxVal);
//  From https://rosettacode.org/wiki/Fast_Fourier_transform#C++
    void fft(CArray& x);
    void ifft(CArray& x);
    void processFFT(CArray& x);
    void processFFTR(CArray& x);
    void SetWindow(int32 winSize);

	//--- ---------------------------------------------------------------------
	// AudioEffect overrides:
	//--- ---------------------------------------------------------------------
	/** Called at first after constructor */
	Steinberg::tresult PLUGIN_API initialize (Steinberg::FUnknown* context) SMTG_OVERRIDE;
	
	/** Called at the end before destructor */
	Steinberg::tresult PLUGIN_API terminate () SMTG_OVERRIDE;
	
	/** Switch the Plug-in on/off */
	Steinberg::tresult PLUGIN_API setActive (Steinberg::TBool state) SMTG_OVERRIDE;

	/** Will be called before any process call */
	Steinberg::tresult PLUGIN_API setupProcessing (Steinberg::Vst::ProcessSetup& newSetup) SMTG_OVERRIDE;
	
	/** Asks if a given sample size is supported see SymbolicSampleSizes. */
	Steinberg::tresult PLUGIN_API canProcessSampleSize (Steinberg::int32 symbolicSampleSize) SMTG_OVERRIDE;

	/** Here we go...the process call */
	Steinberg::tresult PLUGIN_API process (Steinberg::Vst::ProcessData& data) SMTG_OVERRIDE;
		
	/** For persistence */
	Steinberg::tresult PLUGIN_API setState (Steinberg::IBStream* state) SMTG_OVERRIDE;
	Steinberg::tresult PLUGIN_API getState (Steinberg::IBStream* state) SMTG_OVERRIDE;

//------------------------------------------------------------------------
protected:
    float fPitch;
    float fPitchFollower = 0;
    float fPitchFollowerPrev = 0;
    float fPitchRatio = 1;
    
    Steinberg::int32 numSamples = 0;
    
    CArray CFFTBufferL1;
    CArray CFFTBufferL2;
    CArray CFFTBufferL3;
    CArray CFFTBufferL4;
     
    CArray CFFTBufferR1;
    CArray CFFTBufferR2;
    CArray CFFTBufferR3;
    CArray CFFTBufferR4;
    
    
    std::valarray<float> HWindow;

    std::valarray<Vst::Sample32> LastInputPhases;
    std::valarray<Vst::Sample32> LastOutputPhases;
    std::valarray<Vst::Sample32> LastInputPhasesR;
    std::valarray<Vst::Sample32> LastOutputPhasesR;
    std::valarray<Vst::Sample32> LastInputPhases2;
    std::valarray<Vst::Sample32> LastOutputPhases2;
    std::valarray<Vst::Sample32> LastInputPhasesR2;
    std::valarray<Vst::Sample32> LastOutputPhasesR2;
    std::valarray<Vst::Sample32> AnalysisMag;
    std::valarray<Vst::Sample32> AnalysisFreq;
    std::valarray<Vst::Sample32> AnalysisMagR;
    std::valarray<Vst::Sample32> AnalysisFreqR;
    std::valarray<Vst::Sample32> SynthMag;
    std::valarray<Vst::Sample32> SynthFreq;
    std::valarray<Vst::Sample32> SynthMagR;
    std::valarray<Vst::Sample32> SynthFreqR;
    
    int32 HopSize = 512;
    int32 FFTSize = 1024;
    
};

//------------------------------------------------------------------------
} // namespace tobyCorp
