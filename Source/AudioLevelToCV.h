/**
    bespoke synth, a software modular synthesizer
    Copyright (C) 2021 Ryan Challinor (contact: awwbees@gmail.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
/*
  ==============================================================================

    AudioLevelToCV.h
    Created: 9 Oct 2018 10:26:30pm
    Author:  Ryan Challinor

  ==============================================================================
*/

#pragma once
#include "IAudioProcessor.h"
#include "IDrawableModule.h"
#include "Slider.h"
#include "IModulator.h"

class PatchCableSource;

class AudioLevelToCV : public IAudioProcessor, public IDrawableModule, public IFloatSliderListener, public IModulator
{
public:
   AudioLevelToCV();
   virtual ~AudioLevelToCV();
   static IDrawableModule* Create() { return new AudioLevelToCV(); }


   void CreateUIControls() override;

   void SetEnabled(bool enabled) override { mEnabled = enabled; }

   void Process(double time) override;

   void PostRepatch(PatchCableSource* cableSource, bool fromUserClick) override;

   //IModulator
   float Value(int samplesIn = 0) override;
   bool Active() const override { return mEnabled; }

   //IFloatSliderListener
   void FloatSliderUpdated(FloatSlider* slider, float oldVal, double time) override;

   void SaveLayout(ofxJSONElement& moduleInfo) override;
   void LoadLayout(const ofxJSONElement& moduleInfo) override;
   void SetUpFromSaveData() override;

private:
   //IDrawableModule
   void DrawModule() override;
   void GetModuleDimensions(float& w, float& h) override
   {
      w = 106;
      h = 17 * 5 + 2;
   }
   bool Enabled() const override { return mEnabled; }

   float mGain{ 1 };
   float* mModulationBuffer;
   FloatSlider* mGainSlider{ nullptr };
   FloatSlider* mAttackSlider{ nullptr };
   FloatSlider* mReleaseSlider{ nullptr };
   float mVal{ 0 };
   float mAttack{ 10 };
   float mRelease{ 10 };
   float mAttackFactor{ .99 };
   float mReleaseFactor{ .99 };
};
