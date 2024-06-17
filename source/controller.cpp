//------------------------------------------------------------------------
// Copyright(c) 2024 Toby Corp.
//------------------------------------------------------------------------

#include "controller.h"
#include "cids.h"
#include "vstgui/plugin-bindings/vst3editor.h"

using namespace Steinberg;

namespace tobyCorp {

//------------------------------------------------------------------------
// FFTPitchShiftController Implementation
//------------------------------------------------------------------------
tresult PLUGIN_API FFTPitchShiftController::initialize (FUnknown* context)
{
	// Here the Plug-in will be instantiated

	//---do not forget to call parent ------
	tresult result = EditControllerEx1::initialize (context);
	if (result != kResultOk)
	{
		return result;
	}

	// Here you could register some parameters
    parameters.addParameter(STR16("pitch"),nullptr, 0, 0.5, Vst::ParameterInfo::kCanAutomate,0);
    
	return result;
}

//------------------------------------------------------------------------
tresult PLUGIN_API FFTPitchShiftController::terminate ()
{
	// Here the Plug-in will be de-instantiated, last possibility to remove some memory!

	//---do not forget to call parent ------
	return EditControllerEx1::terminate ();
}

//------------------------------------------------------------------------
tresult PLUGIN_API FFTPitchShiftController::setComponentState (IBStream* state)
{
	// Here you get the state of the component (Processor part)
	if (!state)
		return kResultFalse;

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API FFTPitchShiftController::setState (IBStream* state)
{
	// Here you get the state of the controller

	return kResultTrue;
}

//------------------------------------------------------------------------
tresult PLUGIN_API FFTPitchShiftController::getState (IBStream* state)
{
	// Here you are asked to deliver the state of the controller (if needed)
	// Note: the real state of your plug-in is saved in the processor

	return kResultTrue;
}

//------------------------------------------------------------------------
IPlugView* PLUGIN_API FFTPitchShiftController::createView (FIDString name)
{
	// Here the Host wants to open your editor (if you have one)
	if (FIDStringsEqual (name, Vst::ViewType::kEditor))
	{
		// create your editor here and return a IPlugView ptr of it
		auto* view = new VSTGUI::VST3Editor (this, "view", "editor.uidesc");
		return view;
	}
	return nullptr;
}

//------------------------------------------------------------------------
} // namespace tobyCorp
