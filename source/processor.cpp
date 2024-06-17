//------------------------------------------------------------------------
// Copyright(c) 2024 Toby Corp.
//------------------------------------------------------------------------

#include "processor.h"
#include "cids.h"
#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include <math.h>

using namespace Steinberg;

namespace tobyCorp {
//------------------------------------------------------------------------
// FFTPitchShiftProcessor
//------------------------------------------------------------------------
FFTPitchShiftProcessor::FFTPitchShiftProcessor ()
{
	//--- set the wanted controller for our processor
	setControllerClass (kFFTPitchShiftControllerUID);
}

//------------------------------------------------------------------------
FFTPitchShiftProcessor::~FFTPitchShiftProcessor ()
{}

//------------------------------------------------------------------------
tresult PLUGIN_API FFTPitchShiftProcessor::initialize (FUnknown* context)
{
	// Here the Plug-in will be instantiated
	
	//---always initialize the parent-------
	tresult result = AudioEffect::initialize (context);
	// if everything Ok, continue
	if (result != kResultOk)
	{
		return result;
	}

	//--- create Audio IO ------
	addAudioInput (STR16 ("Stereo In"), Steinberg::Vst::SpeakerArr::kStereo);
	addAudioOutput (STR16 ("Stereo Out"), Steinberg::Vst::SpeakerArr::kStereo);

	/* If you don't need an event bus, you can remove the next line */
	addEventInput (STR16 ("Event In"), 1);

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API FFTPitchShiftProcessor::terminate ()
{
	// Here the Plug-in will be de-instantiated, last possibility to remove some memory!
	
	//---do not forget to call parent ------
	return AudioEffect::terminate ();
}

//------------------------------------------------------------------------
tresult PLUGIN_API FFTPitchShiftProcessor::setActive (TBool state)
{
	//--- called when the Plug-in is enable/disable (On/Off) -----
	return AudioEffect::setActive (state);
}
float FFTPitchShiftProcessor::getfPitchRatio(float& val)
{
    return powf(2.0f, val);
}
float FFTPitchShiftProcessor::wrapPhase(float phaseIn)
{
    if (phaseIn >= 0)
        return fmodf(phaseIn + M_PI, 2.0 * M_PI) - M_PI;
    else
        return fmodf(phaseIn - M_PI, -2.0 * M_PI) + M_PI;
}


void FFTPitchShiftProcessor::processFFT(CArray &x)
{
    for (size_t i = 0; i < FFTSize / 2; i++)
        {
            float amplitude = std::abs(x[i]);
            float phase = std::arg(x[i]);

            float phaseDiff = phase - LastInputPhases[i];

            float binCentreFrequency = 2.f * M_PI * (float)i / (float)FFTSize;
            phaseDiff = wrapPhase(phaseDiff - binCentreFrequency * (float)HopSize);

            float binDeviation = phaseDiff * (float)FFTSize / (float)HopSize / (2.f * M_PI);
            AnalysisFreq[i] = (float)i + binDeviation;
            AnalysisMag[i] = amplitude;

            LastInputPhases[i] = phase;
        }

    for (size_t i = 0; i < FFTSize / 2; i++)
        {
            SynthMag[i] = SynthFreq[i] = 0;
        }

        for (size_t i = 0; i < FFTSize / 2; i++)
        {
            int newBin = floorf(i * fPitchRatio + .5);

            if (newBin <= FFTSize / 2)
            {
                SynthMag[newBin] += AnalysisMag[i];
                SynthFreq[newBin] = AnalysisFreq[i] * fPitchRatio;
            }
        }

        for (size_t i = 0; i < FFTSize / 2; i++)
        {
            float amplitude = SynthMag[i];

            float binDeviation = SynthFreq[i] - i;

            float phaseDiff = binDeviation * 2.f * M_PI * (float)HopSize / (float)FFTSize;

            float binCentreFrequency = 2.f * M_PI * (float)i / (float)FFTSize;
            phaseDiff += binCentreFrequency * (float)HopSize;

            float outPhase = wrapPhase(LastOutputPhases[i] + phaseDiff);

            x[i].real(amplitude * cosf(outPhase));
            x[i].imag(amplitude * sinf(outPhase));

            if (i > 0 && i < FFTSize / 2)
            {
                x[FFTSize - i].real(x[i].real());
                x[FFTSize - i].imag(-1.f * x[i].imag());
            }
            LastOutputPhases[i] = outPhase;
        }
}


void FFTPitchShiftProcessor::processFFTR(CArray &x)
{
    for (size_t i = 0; i < FFTSize / 2; i++)
        {
            float amplitude = std::abs(x[i]);
            float phase = std::arg(x[i]);

            float phaseDiff = phase - LastInputPhasesR[i];

            float binCentreFrequency = 2.f * M_PI * (float)i / (float)FFTSize;
            phaseDiff = wrapPhase(phaseDiff - binCentreFrequency * (float)HopSize);

            float binDeviation = phaseDiff * (float)FFTSize / (float)HopSize / (2.f * M_PI);
            AnalysisFreqR[i] = (float)i + binDeviation;
            AnalysisMagR[i] = amplitude;

            LastInputPhasesR[i] = phase;
        }

    for (size_t i = 0; i < FFTSize / 2; i++)
        {
            SynthMagR[i] = SynthFreqR[i] = 0;
        }

        for (size_t i = 0; i < FFTSize / 2; i++)
        {
            int newBin = floorf(i * fPitchRatio + .5);

            if (newBin <= FFTSize / 2)
            {
                SynthMagR[newBin] += AnalysisMagR[i];
                SynthFreqR[newBin] = AnalysisFreqR[i] * fPitchRatio;
            }
        }

        for (size_t i = 0; i < FFTSize / 2; i++)
        {
            float amplitude = SynthMagR[i];

            float binDeviation = SynthFreqR[i] - i;

            float phaseDiff = binDeviation * 2.f * M_PI * (float)HopSize / (float)FFTSize;

            float binCentreFrequency = 2.f * M_PI * (float)i / (float)FFTSize;
            phaseDiff += binCentreFrequency * (float)HopSize;

            float outPhase = wrapPhase(LastOutputPhasesR[i] + phaseDiff);

            x[i].real(amplitude * cosf(outPhase));
            x[i].imag(amplitude * sinf(outPhase));

            if (i > 0 && i < FFTSize / 2)
            {
                x[FFTSize - i].real(x[i].real());
                x[FFTSize - i].imag(-1.f * x[i].imag());
            }
            LastOutputPhasesR[i] = outPhase;
        }
}

void FFTPitchShiftProcessor::SetWindow(int32 winSize)
{
    for (size_t i = 0; i < winSize; i++)
    {
        HWindow[i] = .5f * (1.f - cosf(2.f * M_PI * i / (float)(winSize - 1)));
    }
}
void FFTPitchShiftProcessor::fft(CArray &x)
{
        // DFT
        unsigned int N = (unsigned int)x.size(), k = N, n;
        double thetaT = M_PI / N;
        Complex phiT = Complex(cos(thetaT), -sin(thetaT)), T;
        while (k > 1)
        {
            n = k;
            k >>= 1;
            phiT = phiT * phiT;
            T = 1.0L;
            for (unsigned int l = 0; l < k; l++)
            {
                for (unsigned int a = l; a < N; a += n)
                {
                    unsigned int b = a + k;
                    Complex t = x[a] - x[b];
                    x[a] += x[b];
                    x[b] = t * T;
                }
                T *= phiT;
            }
        }
    
        // Decimate
        unsigned int m = (unsigned int)log2(N);
        for (unsigned int a = 0; a < N; a++)
        {
            unsigned int b = a;
            // Reverse bits
            b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
            b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
            b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
            b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
            b = ((b >> 16) | (b << 16)) >> (32 - m);
            if (b > a)
            {
                Complex t = x[a];
                x[a] = x[b];
                x[b] = t;
            }
        }
}

void FFTPitchShiftProcessor::ifft(CArray &x)
{
    // conjugate the complex numbers
        x = x.apply(std::conj);

        // forward fft
        fft(x);

        // conjugate the complex numbers again
        x = x.apply(std::conj);

        // scale the numbers
        x /= x.size();
}
//------------------------------------------------------------------------
tresult PLUGIN_API FFTPitchShiftProcessor::process (Vst::ProcessData& data)
{
	//--- First : Read inputs parameter changes-----------

	if (data.inputParameterChanges)
	{
		int32 numParamsChanged = data.inputParameterChanges->getParameterCount ();
		for (int32 index = 0; index < numParamsChanged; index++)
		{
			if (auto* paramQueue = data.inputParameterChanges->getParameterData (index))
			{
				Vst::ParamValue value;
				int32 sampleOffset;
				int32 numPoints = paramQueue->getPointCount ();
                if(paramQueue->getPoint(numPoints-1, sampleOffset, value)== kResultTrue)
                {
                    switch (paramQueue->getParameterId ())
                    {
                        case 0:
                            fPitch = (float)value;
                            
                            break;
                    }
                }
			}
		}
	}
    fPitchFollower = fPitchFollowerPrev + 0.1 * (fPitch-fPitchFollowerPrev);
    fPitchRatio = getfPitchRatio(fPitchFollower);
    fPitchFollowerPrev = fPitchFollower;
	//--- Here you have to implement your processing

    if(data.numInputs==0 || data.numOutputs==0){
        return kResultOk;
    }
    
    int32 numChannels = data.inputs[0].numChannels;
    Vst::Sample32** in = data.inputs[0].channelBuffers32;
    Vst::Sample32** out = data.outputs[0].channelBuffers32;
    if (numSamples ==0)
    {
        numSamples = data.numSamples;
        HopSize = numSamples/4;
        FFTSize = numSamples;
        
        CFFTBufferL1.resize(FFTSize);
        CFFTBufferL2.resize(FFTSize);
        CFFTBufferL3.resize(FFTSize);
        CFFTBufferL4.resize(FFTSize);
        
        CFFTBufferR1.resize(FFTSize);
        CFFTBufferR2.resize(FFTSize);
        CFFTBufferR3.resize(FFTSize);
        CFFTBufferR4.resize(FFTSize);
        
        CFFTBufferL1 = 0.0;
        CFFTBufferL2 = 0.0;
        CFFTBufferL3 = 0.0;
        CFFTBufferL4 = 0.0;
        
        CFFTBufferR1 = 0.0;
        CFFTBufferR2 = 0.0;
        CFFTBufferR3 = 0.0;
        CFFTBufferR4 = 0.0;
        HWindow.resize(FFTSize);
        
        
        LastInputPhases.resize(FFTSize);
        LastOutputPhases.resize(FFTSize);
        
        LastInputPhasesR.resize(FFTSize);
        LastOutputPhasesR.resize(FFTSize);
        
        AnalysisMag.resize(FFTSize);
        AnalysisFreq.resize(FFTSize);
        
        AnalysisMagR.resize(FFTSize);
        AnalysisFreqR.resize(FFTSize);
        
        
        SynthMag.resize(FFTSize);
        SynthFreq.resize(FFTSize);
        
        SynthMagR.resize(FFTSize);
        SynthFreqR.resize(FFTSize);
        
        SetWindow(FFTSize);
    }
    
    for (int32 ch =0; ch < numChannels; ch++) {
        Vst::Sample32* pIn = in[ch];
        Vst::Sample32* pOut = out[ch];
        float tmp;
        
        for (int32 i = 0; i < data.numSamples; i++) {
            *(pOut+i) =0;
        }
        for (int32 i = 0; i < data.numSamples; i++) {
            
            if(ch==0)
            {
                if(i<HopSize) 
                {
                    *(pOut+i) += CFFTBufferL2[HopSize*3+i].real() * HWindow[HopSize*3+i];
                    CFFTBufferL2[HopSize*3+i] = *(pIn+i) * HWindow[HopSize*3+i];
                }
                if(i<HopSize*2)
                {
                    *(pOut+i) += CFFTBufferL3[HopSize*2+i].real() * HWindow[HopSize*2+i];
                    CFFTBufferL3[HopSize*2+i] = *(pIn+i) * HWindow[HopSize*2+i];
                }
                if(i<HopSize*3)
                {
                    *(pOut+i) += CFFTBufferL4[HopSize+i].real() * HWindow[HopSize+i];
                    CFFTBufferL4[HopSize+i] = *(pIn+i) * HWindow[HopSize+i];
                }
            }
            else
            {
                if(i<HopSize)
                {
                    *(pOut+i) += CFFTBufferR2[HopSize*3+i].real() * HWindow[HopSize*3+i];
                    CFFTBufferR2[HopSize*3+i] = *(pIn+i) * HWindow[HopSize*3+i];
                }
                if(i<HopSize*2)
                {
                    *(pOut+i) += CFFTBufferR3[HopSize*2+i].real() * HWindow[HopSize*2+i];
                    CFFTBufferR3[HopSize*2+i] = *(pIn+i) * HWindow[HopSize*2+i];
                }
                if(i<HopSize*3)
                {
                    *(pOut+i) += CFFTBufferR4[HopSize+i].real() * HWindow[HopSize+i];
                    CFFTBufferR4[HopSize+i] = *(pIn+i) * HWindow[HopSize+i];
                }
            }
        }
        
        if(ch ==0)
        {
            fft(CFFTBufferL1);
            fft(CFFTBufferL2);
            fft(CFFTBufferL3);
            fft(CFFTBufferL4);
            
            processFFT(CFFTBufferL1);
            processFFT(CFFTBufferL2);
            processFFT(CFFTBufferL3);
            processFFT(CFFTBufferL4);
            
            ifft(CFFTBufferL1);
            ifft(CFFTBufferL2);
            ifft(CFFTBufferL3);
            ifft(CFFTBufferL4);
        }
        else
        {
            fft(CFFTBufferR1);
            fft(CFFTBufferR2);
            fft(CFFTBufferR3);
            fft(CFFTBufferR4);
            
            processFFTR(CFFTBufferR1);
            processFFTR(CFFTBufferR2);
            processFFTR(CFFTBufferR3);
            processFFTR(CFFTBufferR4);
            
            ifft(CFFTBufferR1);
            ifft(CFFTBufferR2);
            ifft(CFFTBufferR3);
            ifft(CFFTBufferR4);
        }

        
        for (int32 i = 0; i < data.numSamples; i++) {
            if(ch==0)
            {
                tmp = CFFTBufferL1[i].real() * HWindow[i];
                if(i>=HopSize) tmp += CFFTBufferL2[i-HopSize].real() * HWindow[i-HopSize];
                if(i>=HopSize*2) tmp += CFFTBufferL3[i-HopSize*2].real() * HWindow[i-HopSize*2];
                if(i>=HopSize*3) tmp += CFFTBufferL4[i-HopSize*3].real() * HWindow[i-HopSize*3];
            }
            else
            {
                tmp = CFFTBufferR1[i].real() * HWindow[i];
                if(i>=HopSize) tmp += CFFTBufferR2[i-HopSize].real() * HWindow[i-HopSize];
                if(i>=HopSize*2) tmp += CFFTBufferR3[i-HopSize*2].real() * HWindow[i-HopSize*2];
                if(i>=HopSize*3) tmp += CFFTBufferR4[i-HopSize*3].real() * HWindow[i-HopSize*3];
            }
            *(pOut+i) += tmp;
            //*(pOut+i) *= 0.25;
        }
        
        for (int32 i = 0; i < data.numSamples; i++) {
            if(ch==0)
            {
                CFFTBufferL1[i] = *(pIn + i) * HWindow[i];
                if(i>=HopSize) CFFTBufferL2[i-HopSize] = *(pIn + i) * HWindow[i-HopSize];
                if(i>=HopSize*2) CFFTBufferL3[i-HopSize*2] = *(pIn + i) * HWindow[i-HopSize*2];
                if(i>=HopSize*3) CFFTBufferL4[i-HopSize*3] = *(pIn + i) * HWindow[i-HopSize*3];
            }
            else
            {
                CFFTBufferR1[i] = *(pIn + i) * HWindow[i];
                if(i>=HopSize) CFFTBufferR2[i-HopSize] = *(pIn + i) * HWindow[i-HopSize];
                if(i>=HopSize*2) CFFTBufferR3[i-HopSize*2] = *(pIn + i) * HWindow[i-HopSize*2];
                if(i>=HopSize*3) CFFTBufferR4[i-HopSize*3] = *(pIn + i) * HWindow[i-HopSize*3];
            }
        }
    }

    
	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API FFTPitchShiftProcessor::setupProcessing (Vst::ProcessSetup& newSetup)
{
	//--- called before any processing ----
	return AudioEffect::setupProcessing (newSetup);
}

//------------------------------------------------------------------------
tresult PLUGIN_API FFTPitchShiftProcessor::canProcessSampleSize (int32 symbolicSampleSize)
{
	// by default kSample32 is supported
	if (symbolicSampleSize == Vst::kSample32)
		return kResultTrue;

	// disable the following comment if your processing support kSample64
	/* if (symbolicSampleSize == Vst::kSample64)
		return kResultTrue; */

	return kResultFalse;
}

//------------------------------------------------------------------------
tresult PLUGIN_API FFTPitchShiftProcessor::setState (IBStream* state)
{
	// called when we load a preset, the model has to be reloaded
	IBStreamer streamer (state, kLittleEndian);
	
	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API FFTPitchShiftProcessor::getState (IBStream* state)
{
	// here we need to save the model
	IBStreamer streamer (state, kLittleEndian);

	return kResultOk;
}

//------------------------------------------------------------------------
} // namespace tobyCorp
