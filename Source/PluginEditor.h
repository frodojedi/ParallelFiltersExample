#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "PanelGeneralControls.h"
#include "PanelFilter.h"

//==============================================================================

class FilterExampleAudioProcessorEditor : public AudioProcessorEditor
{
public:
    FilterExampleAudioProcessorEditor (FilterExampleAudioProcessor& parent, AudioProcessorValueTreeState& vts);
    ~FilterExampleAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FilterExampleAudioProcessor& processor;
    
    AudioProcessorValueTreeState& valueTreeState;
       
    PanelGeneralControls panelGeneralControls{processor, valueTreeState};
    PanelFilter1 panelFilter1{valueTreeState};
    PanelFilter2 panelFilter2{valueTreeState};
    PanelFilter3 panelFilter3{valueTreeState};
    
    
    Colour colourText = Colours::black;
    Colour colourSliderThumb = Colours::darkblue;
    Colour colourSliderTrack = Colours::whitesmoke;
    Colour colourSliderTextBoxText = colourText;
    Colour colourSlidertextBoxOutline = colourSliderThumb;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterExampleAudioProcessorEditor)
};
