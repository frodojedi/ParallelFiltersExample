/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "PanelGeneralControls.h"
#include "PanelFilter.h"

//==============================================================================
/**
*/
class FilterExampleAudioProcessorEditor : public AudioProcessorEditor
{
public:
    FilterExampleAudioProcessorEditor (FilterExampleAudioProcessor& parent, AudioProcessorValueTreeState& vtsPanelGeneralControls, AudioProcessorValueTreeState& vtsPanelFilter1, AudioProcessorValueTreeState& vtsPanelFilter2, AudioProcessorValueTreeState& vtsPanelFilter3);
    ~FilterExampleAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FilterExampleAudioProcessor& processor;
    
    AudioProcessorValueTreeState& valueTreeStatePanelGeneralControls;
    AudioProcessorValueTreeState& valueTreeStatePanelFilter1;
    AudioProcessorValueTreeState& valueTreeStatePanelFilter2;
    AudioProcessorValueTreeState& valueTreeStatePanelFilter3;
       
    PanelGeneralControls panelGeneralControls{processor, valueTreeStatePanelGeneralControls};
    PanelFilter1 panelFilter1{valueTreeStatePanelFilter1};
    PanelFilter2 panelFilter2{valueTreeStatePanelFilter2};
    PanelFilter3 panelFilter3{valueTreeStatePanelFilter3};
    
    
    Colour colourText = Colours::black;
    Colour colourSliderThumb = Colours::darkblue;
    Colour colourSliderTrack = Colours::whitesmoke;
    Colour colourSliderTextBoxText = colourText;
    Colour colourSlidertextBoxOutline = colourSliderThumb;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterExampleAudioProcessorEditor)
};
