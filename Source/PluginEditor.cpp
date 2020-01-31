#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FilterExampleAudioProcessorEditor::FilterExampleAudioProcessorEditor (FilterExampleAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState (vts)
{
    auto& lnf = getLookAndFeel();
    lnf.setColour (Slider::thumbColourId, colourSliderThumb);
    lnf.setColour (Slider::trackColourId, colourSliderTrack);
    lnf.setColour (Slider::textBoxTextColourId, colourSliderTextBoxText);
    lnf.setColour (Slider::textBoxOutlineColourId, colourSlidertextBoxOutline);
    lnf.setColour (Label::textColourId, colourText);
    sendLookAndFeelChange();
    
    addAndMakeVisible (panelGeneralControls);
    addAndMakeVisible (panelFilter1);
    addAndMakeVisible (panelFilter2);
    addAndMakeVisible (panelFilter3);
    setSize (1200, 400);
}

FilterExampleAudioProcessorEditor::~FilterExampleAudioProcessorEditor()
{
}

//==============================================================================
void FilterExampleAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void FilterExampleAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();
    auto PanelGeneralControlsWidth = 300;
    panelGeneralControls.setBounds(area.removeFromLeft(PanelGeneralControlsWidth));
    
    auto panelFilterWidth = 300;
    panelFilter1.setBounds(area.removeFromLeft(panelFilterWidth));
    panelFilter2.setBounds(area.removeFromLeft(panelFilterWidth));
    panelFilter3.setBounds(area.removeFromLeft(panelFilterWidth));
}
