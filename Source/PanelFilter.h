#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class PanelFilter : public Component
{
public:
    
    PanelFilter (AudioProcessorValueTreeState& valueTreeState)
    {
        
    }
    
    void paint (Graphics& g) override
    {
        g.fillAll(colour_background);
    }
    
    void resized() override
    {
        
    }
 
protected:
    
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    
    enum
    {
        paramControlHeight = 40,
        paramLabelWidth    = 80,
        paramSliderWidth   = 350
    };

    int sliderLeft = paramLabelWidth + 10;
    
    Colour colour_background = Colours::lightblue;
    Colour colour_border = Colours::whitesmoke;
    
    Colour colourText = Colours::black;
    Colour colourSliderThumb = Colours::darkblue;
    Colour colourSliderTrack = Colours::whitesmoke;
    Colour colourSliderTextBoxText = colourText;
    Colour colourSlidertextBoxOutline = colourSliderThumb;
    
private:
    

};



//==============================================================================
class PanelFilter1 : public PanelFilter
{
public:
    
    PanelFilter1 (AudioProcessorValueTreeState& valueTreeState) : PanelFilter (valueTreeState)
    {
        Filter1GainSlider.setColour (Slider::textBoxTextColourId, colourSliderTextBoxText);
        Filter1GainSlider.setColour (Slider::textBoxOutlineColourId, colourSlidertextBoxOutline);
        Filter1GainSlider.setColour (Slider::thumbColourId, colourSliderThumb);
        Filter1GainSlider.setColour (Slider::trackColourId, colourSliderTrack);
        Filter1GainLabel.setText ("Gain", dontSendNotification);
        Filter1GainLabel.attachToComponent (&Filter1GainSlider, true);
        addAndMakeVisible (Filter1GainLabel);
        addAndMakeVisible (Filter1GainSlider);
        Filter1GainAttachment.reset (new SliderAttachment (valueTreeState, "gain_panel_Filter1", Filter1GainSlider));
        
        
        Filter1FreqSlider.setColour (Slider::textBoxTextColourId, colourSliderTextBoxText);
        Filter1FreqSlider.setColour (Slider::textBoxOutlineColourId, colourSlidertextBoxOutline);
        Filter1FreqSlider.setColour (Slider::thumbColourId, colourSliderThumb);
        Filter1FreqSlider.setColour (Slider::trackColourId, colourSliderTrack);
        Filter1FreqLabel.setText ("Freq", dontSendNotification);
        Filter1FreqLabel.attachToComponent (&Filter1FreqSlider, true);
        addAndMakeVisible (Filter1FreqLabel);
        Filter1FreqSlider.setTextValueSuffix (" Hz");
        addAndMakeVisible (Filter1FreqSlider);
        Filter1FreqAttachment.reset (new SliderAttachment (valueTreeState, "freq_panel_Filter1", Filter1FreqSlider));

        
        Filter1PoleRadiusSlider.setColour (Slider::textBoxTextColourId, colourSliderTextBoxText);
        Filter1PoleRadiusSlider.setColour (Slider::textBoxOutlineColourId, colourSlidertextBoxOutline);
        Filter1PoleRadiusSlider.setColour (Slider::thumbColourId, colourSliderThumb);
        Filter1PoleRadiusSlider.setColour (Slider::trackColourId, colourSliderTrack);
        Filter1PoleRadiusLabel.setText ("Pole Radius", dontSendNotification);
        Filter1PoleRadiusLabel.attachToComponent (&Filter1PoleRadiusSlider, true);
        addAndMakeVisible (Filter1PoleRadiusLabel);
        addAndMakeVisible (Filter1PoleRadiusSlider);
        Filter1PoleRadiusAttachment.reset (new SliderAttachment (valueTreeState, "pole_radius_panel_Filter1", Filter1PoleRadiusSlider));
        
        
        Filter1NumObjectsSlider.setColour (Slider::textBoxTextColourId, colourSliderTextBoxText);
        Filter1NumObjectsSlider.setColour (Slider::textBoxOutlineColourId, colourSlidertextBoxOutline);
        Filter1NumObjectsSlider.setColour (Slider::thumbColourId, colourSliderThumb);
        Filter1NumObjectsSlider.setColour (Slider::trackColourId, colourSliderTrack);
        Filter1NumObjectsLabel.setText ("Num Objects", dontSendNotification);
        Filter1NumObjectsLabel.attachToComponent (&Filter1NumObjectsSlider, true);
        addAndMakeVisible (Filter1NumObjectsLabel);
        addAndMakeVisible (Filter1NumObjectsSlider);
        Filter1NumObjectsAttachment.reset (new SliderAttachment (valueTreeState, "num_objects_panel_Filter1", Filter1NumObjectsSlider));
        
        
        Filter1SoundDecaySlider.setColour (Slider::textBoxTextColourId, colourSliderTextBoxText);
        Filter1SoundDecaySlider.setColour (Slider::textBoxOutlineColourId, colourSlidertextBoxOutline);
        Filter1SoundDecaySlider.setColour (Slider::thumbColourId, colourSliderThumb);
        Filter1SoundDecaySlider.setColour (Slider::trackColourId, colourSliderTrack);
        Filter1SoundDecayLabel.setText ("Sound Decay", dontSendNotification);
        Filter1SoundDecayLabel.attachToComponent (&Filter1SoundDecaySlider, true);
        addAndMakeVisible (Filter1SoundDecayLabel);
        addAndMakeVisible (Filter1SoundDecaySlider);
        Filter1SoundDecayAttachment.reset (new SliderAttachment (valueTreeState, "sound_decay_panel_Filter1", Filter1SoundDecaySlider));
        
        
        Filter1SystemDecaySlider.setColour (Slider::textBoxTextColourId, colourSliderTextBoxText);
        Filter1SystemDecaySlider.setColour (Slider::textBoxOutlineColourId, colourSlidertextBoxOutline);
        Filter1SystemDecaySlider.setColour (Slider::thumbColourId, colourSliderThumb);
        Filter1SystemDecaySlider.setColour (Slider::trackColourId, colourSliderTrack);
        Filter1SystemDecayLabel.setText ("System Decay", dontSendNotification);
        Filter1SystemDecayLabel.attachToComponent (&Filter1SystemDecaySlider, true);
        addAndMakeVisible (Filter1SystemDecayLabel);
        addAndMakeVisible (Filter1SystemDecaySlider);
        Filter1SystemDecayAttachment.reset (new SliderAttachment (valueTreeState, "system_decay_panel_Filter1", Filter1SystemDecaySlider));
    }

    
    ~PanelFilter1(){
        Filter1GainAttachment.reset();
        Filter1FreqAttachment.reset();
        Filter1PoleRadiusAttachment.reset();
        Filter1NumObjectsAttachment.reset();
        Filter1SoundDecayAttachment.reset();
        Filter1SystemDecayAttachment.reset();
    }
    
    
    void paint (Graphics& g) override
    {
        g.fillAll(Colours::lightblue);
        
        Rectangle<int> panelFilter1Area (getLocalBounds());
        //g.setColour (colour_border);
        g.drawRect (panelFilter1Area, 3.0f);
    }
    
    void resized() override
    {
        Filter1GainSlider.setBounds (sliderLeft, paramControlHeight, getWidth() - sliderLeft - 10, 20);
        Filter1FreqSlider.setBounds (sliderLeft, paramControlHeight*2, getWidth() - sliderLeft - 10, 20);
        Filter1PoleRadiusSlider.setBounds (sliderLeft, paramControlHeight*3, getWidth() - sliderLeft - 10, 20);
        Filter1NumObjectsSlider.setBounds (sliderLeft, paramControlHeight*4, getWidth() - sliderLeft - 10, 20);
        Filter1SoundDecaySlider.setBounds (sliderLeft, paramControlHeight*5, getWidth() - sliderLeft - 10, 20);
        Filter1SystemDecaySlider.setBounds (sliderLeft, paramControlHeight*6, getWidth() - sliderLeft - 10, 20);
    }
 private:
    
    Label Filter1GainLabel;
    Slider Filter1GainSlider;
    
    Label Filter1FreqLabel;
    Slider Filter1FreqSlider;
   
    Label Filter1PoleRadiusLabel;
    Slider Filter1PoleRadiusSlider;
    
    Label Filter1NumObjectsLabel;
    Slider Filter1NumObjectsSlider;
    
    Label Filter1SoundDecayLabel;
    Slider Filter1SoundDecaySlider;
    
    Label Filter1SystemDecayLabel;
    Slider Filter1SystemDecaySlider;
    
    std::unique_ptr<SliderAttachment> Filter1GainAttachment;
    std::unique_ptr<SliderAttachment> Filter1FreqAttachment;
    std::unique_ptr<SliderAttachment> Filter1PoleRadiusAttachment;
    std::unique_ptr<SliderAttachment> Filter1NumObjectsAttachment;
    std::unique_ptr<SliderAttachment> Filter1SoundDecayAttachment;
    std::unique_ptr<SliderAttachment> Filter1SystemDecayAttachment;
};





//==============================================================================
class PanelFilter2 : public PanelFilter
{
public:
    
    PanelFilter2 (AudioProcessorValueTreeState& valueTreeState) : PanelFilter (valueTreeState)
    {
        Filter2GainSlider.setColour (Slider::textBoxTextColourId, colourSliderTextBoxText);
        Filter2GainSlider.setColour (Slider::textBoxOutlineColourId, colourSlidertextBoxOutline);
        Filter2GainSlider.setColour (Slider::thumbColourId, colourSliderThumb);
        Filter2GainSlider.setColour (Slider::trackColourId, colourSliderTrack);
        Filter2GainLabel.setText ("Gain", dontSendNotification);
        Filter2GainLabel.attachToComponent (&Filter2GainSlider, true);
        addAndMakeVisible (Filter2GainLabel);
        addAndMakeVisible (Filter2GainSlider);
        Filter2GainAttachment.reset (new SliderAttachment (valueTreeState, "gain_panel_Filter2", Filter2GainSlider));
        
        
        Filter2FreqSlider.setColour (Slider::textBoxTextColourId, colourSliderTextBoxText);
        Filter2FreqSlider.setColour (Slider::textBoxOutlineColourId, colourSlidertextBoxOutline);
        Filter2FreqSlider.setColour (Slider::thumbColourId, colourSliderThumb);
        Filter2FreqSlider.setColour (Slider::trackColourId, colourSliderTrack);
        Filter2FreqLabel.setText ("Freq", dontSendNotification);
        Filter2FreqLabel.attachToComponent (&Filter2FreqSlider, true);
        addAndMakeVisible (Filter2FreqLabel);
        Filter2FreqSlider.setTextValueSuffix (" Hz");
        addAndMakeVisible (Filter2FreqSlider);
        Filter2FreqAttachment.reset (new SliderAttachment (valueTreeState, "freq_panel_Filter2", Filter2FreqSlider));

        
        Filter2PoleRadiusSlider.setColour (Slider::textBoxTextColourId, colourSliderTextBoxText);
        Filter2PoleRadiusSlider.setColour (Slider::textBoxOutlineColourId, colourSlidertextBoxOutline);
        Filter2PoleRadiusSlider.setColour (Slider::thumbColourId, colourSliderThumb);
        Filter2PoleRadiusSlider.setColour (Slider::trackColourId, colourSliderTrack);
        Filter2PoleRadiusLabel.setText ("Pole Radius", dontSendNotification);
        Filter2PoleRadiusLabel.attachToComponent (&Filter2PoleRadiusSlider, true);
        addAndMakeVisible (Filter2PoleRadiusLabel);
        addAndMakeVisible (Filter2PoleRadiusSlider);
        Filter2PoleRadiusAttachment.reset (new SliderAttachment (valueTreeState, "pole_radius_panel_Filter2", Filter2PoleRadiusSlider));
        
        
        Filter2NumObjectsSlider.setColour (Slider::textBoxTextColourId, colourSliderTextBoxText);
        Filter2NumObjectsSlider.setColour (Slider::textBoxOutlineColourId, colourSlidertextBoxOutline);
        Filter2NumObjectsSlider.setColour (Slider::thumbColourId, colourSliderThumb);
        Filter2NumObjectsSlider.setColour (Slider::trackColourId, colourSliderTrack);
        Filter2NumObjectsLabel.setText ("Num Objects", dontSendNotification);
        Filter2NumObjectsLabel.attachToComponent (&Filter2NumObjectsSlider, true);
        addAndMakeVisible (Filter2NumObjectsLabel);
        addAndMakeVisible (Filter2NumObjectsSlider);
        Filter2NumObjectsAttachment.reset (new SliderAttachment (valueTreeState, "num_objects_panel_Filter2", Filter2NumObjectsSlider));
        
        
        Filter2SoundDecaySlider.setColour (Slider::textBoxTextColourId, colourSliderTextBoxText);
        Filter2SoundDecaySlider.setColour (Slider::textBoxOutlineColourId, colourSlidertextBoxOutline);
        Filter2SoundDecaySlider.setColour (Slider::thumbColourId, colourSliderThumb);
        Filter2SoundDecaySlider.setColour (Slider::trackColourId, colourSliderTrack);
        Filter2SoundDecayLabel.setText ("Sound Decay", dontSendNotification);
        Filter2SoundDecayLabel.attachToComponent (&Filter2SoundDecaySlider, true);
        addAndMakeVisible (Filter2SoundDecayLabel);
        addAndMakeVisible (Filter2SoundDecaySlider);
        Filter2SoundDecayAttachment.reset (new SliderAttachment (valueTreeState, "sound_decay_panel_Filter2", Filter2SoundDecaySlider));
        
        
        Filter2SystemDecaySlider.setColour (Slider::textBoxTextColourId, colourSliderTextBoxText);
        Filter2SystemDecaySlider.setColour (Slider::textBoxOutlineColourId, colourSlidertextBoxOutline);
        Filter2SystemDecaySlider.setColour (Slider::thumbColourId, colourSliderThumb);
        Filter2SystemDecaySlider.setColour (Slider::trackColourId, colourSliderTrack);
        Filter2SystemDecayLabel.setText ("System Decay", dontSendNotification);
        Filter2SystemDecayLabel.attachToComponent (&Filter2SystemDecaySlider, true);
        addAndMakeVisible (Filter2SystemDecayLabel);
        addAndMakeVisible (Filter2SystemDecaySlider);
        Filter2SystemDecayAttachment.reset (new SliderAttachment (valueTreeState, "system_decay_panel_Filter2", Filter2SystemDecaySlider));
    }

    
    ~PanelFilter2(){
        Filter2GainAttachment.reset();
        Filter2FreqAttachment.reset();
        Filter2PoleRadiusAttachment.reset();
        Filter2NumObjectsAttachment.reset();
        Filter2SoundDecayAttachment.reset();
        Filter2SystemDecayAttachment.reset();
    }
    
    
    void paint (Graphics& g) override
    {
        g.fillAll(Colours::lightblue);
        
        Rectangle<int> panelFilter2Area (getLocalBounds());
        //g.setColour (colour_border);
        g.drawRect (panelFilter2Area, 3.0f);
    }
    
    void resized() override
    {
        Filter2GainSlider.setBounds (sliderLeft, paramControlHeight, getWidth() - sliderLeft - 10, 20);
        Filter2FreqSlider.setBounds (sliderLeft, paramControlHeight*2, getWidth() - sliderLeft - 10, 20);
        Filter2PoleRadiusSlider.setBounds (sliderLeft, paramControlHeight*3, getWidth() - sliderLeft - 10, 20);
        Filter2NumObjectsSlider.setBounds (sliderLeft, paramControlHeight*4, getWidth() - sliderLeft - 10, 20);
        Filter2SoundDecaySlider.setBounds (sliderLeft, paramControlHeight*5, getWidth() - sliderLeft - 10, 20);
        Filter2SystemDecaySlider.setBounds (sliderLeft, paramControlHeight*6, getWidth() - sliderLeft - 10, 20);
    }
 private:
    
    Label Filter2GainLabel;
    Slider Filter2GainSlider;
    
    Label Filter2FreqLabel;
    Slider Filter2FreqSlider;
   
    Label Filter2PoleRadiusLabel;
    Slider Filter2PoleRadiusSlider;
    
    Label Filter2NumObjectsLabel;
    Slider Filter2NumObjectsSlider;
    
    Label Filter2SoundDecayLabel;
    Slider Filter2SoundDecaySlider;
    
    Label Filter2SystemDecayLabel;
    Slider Filter2SystemDecaySlider;
    
    std::unique_ptr<SliderAttachment> Filter2GainAttachment;
    std::unique_ptr<SliderAttachment> Filter2FreqAttachment;
    std::unique_ptr<SliderAttachment> Filter2PoleRadiusAttachment;
    std::unique_ptr<SliderAttachment> Filter2NumObjectsAttachment;
    std::unique_ptr<SliderAttachment> Filter2SoundDecayAttachment;
    std::unique_ptr<SliderAttachment> Filter2SystemDecayAttachment;
};




//==============================================================================
class PanelFilter3 : public PanelFilter
{
public:
    
    PanelFilter3 (AudioProcessorValueTreeState& valueTreeState) : PanelFilter (valueTreeState)
    {
        Filter3GainSlider.setColour (Slider::textBoxTextColourId, colourSliderTextBoxText);
        Filter3GainSlider.setColour (Slider::textBoxOutlineColourId, colourSlidertextBoxOutline);
        Filter3GainSlider.setColour (Slider::thumbColourId, colourSliderThumb);
        Filter3GainSlider.setColour (Slider::trackColourId, colourSliderTrack);
        Filter3GainLabel.setText ("Gain", dontSendNotification);
        Filter3GainLabel.attachToComponent (&Filter3GainSlider, true);
        addAndMakeVisible (Filter3GainLabel);
        addAndMakeVisible (Filter3GainSlider);
        Filter3GainAttachment.reset (new SliderAttachment (valueTreeState, "gain_panel_Filter3", Filter3GainSlider));
        
        
        Filter3FreqSlider.setColour (Slider::textBoxTextColourId, colourSliderTextBoxText);
        Filter3FreqSlider.setColour (Slider::textBoxOutlineColourId, colourSlidertextBoxOutline);
        Filter3FreqSlider.setColour (Slider::thumbColourId, colourSliderThumb);
        Filter3FreqSlider.setColour (Slider::trackColourId, colourSliderTrack);
        Filter3FreqLabel.setText ("Freq", dontSendNotification);
        Filter3FreqLabel.attachToComponent (&Filter3FreqSlider, true);
        addAndMakeVisible (Filter3FreqLabel);
        Filter3FreqSlider.setTextValueSuffix (" Hz");
        addAndMakeVisible (Filter3FreqSlider);
        Filter3FreqAttachment.reset (new SliderAttachment (valueTreeState, "freq_panel_Filter3", Filter3FreqSlider));

        
        Filter3PoleRadiusSlider.setColour (Slider::textBoxTextColourId, colourSliderTextBoxText);
        Filter3PoleRadiusSlider.setColour (Slider::textBoxOutlineColourId, colourSlidertextBoxOutline);
        Filter3PoleRadiusSlider.setColour (Slider::thumbColourId, colourSliderThumb);
        Filter3PoleRadiusSlider.setColour (Slider::trackColourId, colourSliderTrack);
        Filter3PoleRadiusLabel.setText ("Pole Radius", dontSendNotification);
        Filter3PoleRadiusLabel.attachToComponent (&Filter3PoleRadiusSlider, true);
        addAndMakeVisible (Filter3PoleRadiusLabel);
        addAndMakeVisible (Filter3PoleRadiusSlider);
        Filter3PoleRadiusAttachment.reset (new SliderAttachment (valueTreeState, "pole_radius_panel_Filter3", Filter3PoleRadiusSlider));
        
        
        Filter3NumObjectsSlider.setColour (Slider::textBoxTextColourId, colourSliderTextBoxText);
        Filter3NumObjectsSlider.setColour (Slider::textBoxOutlineColourId, colourSlidertextBoxOutline);
        Filter3NumObjectsSlider.setColour (Slider::thumbColourId, colourSliderThumb);
        Filter3NumObjectsSlider.setColour (Slider::trackColourId, colourSliderTrack);
        Filter3NumObjectsLabel.setText ("Num Objects", dontSendNotification);
        Filter3NumObjectsLabel.attachToComponent (&Filter3NumObjectsSlider, true);
        addAndMakeVisible (Filter3NumObjectsLabel);
        addAndMakeVisible (Filter3NumObjectsSlider);
        Filter3NumObjectsAttachment.reset (new SliderAttachment (valueTreeState, "num_objects_panel_Filter3", Filter3NumObjectsSlider));
        
        
        Filter3SoundDecaySlider.setColour (Slider::textBoxTextColourId, colourSliderTextBoxText);
        Filter3SoundDecaySlider.setColour (Slider::textBoxOutlineColourId, colourSlidertextBoxOutline);
        Filter3SoundDecaySlider.setColour (Slider::thumbColourId, colourSliderThumb);
        Filter3SoundDecaySlider.setColour (Slider::trackColourId, colourSliderTrack);
        Filter3SoundDecayLabel.setText ("Sound Decay", dontSendNotification);
        Filter3SoundDecayLabel.attachToComponent (&Filter3SoundDecaySlider, true);
        addAndMakeVisible (Filter3SoundDecayLabel);
        addAndMakeVisible (Filter3SoundDecaySlider);
        Filter3SoundDecayAttachment.reset (new SliderAttachment (valueTreeState, "sound_decay_panel_Filter3", Filter3SoundDecaySlider));
        
        
        Filter3SystemDecaySlider.setColour (Slider::textBoxTextColourId, colourSliderTextBoxText);
        Filter3SystemDecaySlider.setColour (Slider::textBoxOutlineColourId, colourSlidertextBoxOutline);
        Filter3SystemDecaySlider.setColour (Slider::thumbColourId, colourSliderThumb);
        Filter3SystemDecaySlider.setColour (Slider::trackColourId, colourSliderTrack);
        Filter3SystemDecayLabel.setText ("System Decay", dontSendNotification);
        Filter3SystemDecayLabel.attachToComponent (&Filter3SystemDecaySlider, true);
        addAndMakeVisible (Filter3SystemDecayLabel);
        addAndMakeVisible (Filter3SystemDecaySlider);
        Filter3SystemDecayAttachment.reset (new SliderAttachment (valueTreeState, "system_decay_panel_Filter3", Filter3SystemDecaySlider));
    }

    
    ~PanelFilter3(){
        Filter3GainAttachment.reset();
        Filter3FreqAttachment.reset();
        Filter3PoleRadiusAttachment.reset();
        Filter3NumObjectsAttachment.reset();
        Filter3SoundDecayAttachment.reset();
        Filter3SystemDecayAttachment.reset();
    }
    
    
    void paint (Graphics& g) override
    {
        g.fillAll(Colours::lightblue);
        
        Rectangle<int> panelFilter3Area (getLocalBounds());
        //g.setColour (colour_border);
        g.drawRect (panelFilter3Area, 3.0f);
    }
    
    void resized() override
    {
        Filter3GainSlider.setBounds (sliderLeft, paramControlHeight, getWidth() - sliderLeft - 10, 20);
        Filter3FreqSlider.setBounds (sliderLeft, paramControlHeight*2, getWidth() - sliderLeft - 10, 20);
        Filter3PoleRadiusSlider.setBounds (sliderLeft, paramControlHeight*3, getWidth() - sliderLeft - 10, 20);
        Filter3NumObjectsSlider.setBounds (sliderLeft, paramControlHeight*4, getWidth() - sliderLeft - 10, 20);
        Filter3SoundDecaySlider.setBounds (sliderLeft, paramControlHeight*5, getWidth() - sliderLeft - 10, 20);
        Filter3SystemDecaySlider.setBounds (sliderLeft, paramControlHeight*6, getWidth() - sliderLeft - 10, 20);
    }
 private:
    
    Label Filter3GainLabel;
    Slider Filter3GainSlider;
    
    Label Filter3FreqLabel;
    Slider Filter3FreqSlider;
   
    Label Filter3PoleRadiusLabel;
    Slider Filter3PoleRadiusSlider;
    
    Label Filter3NumObjectsLabel;
    Slider Filter3NumObjectsSlider;
    
    Label Filter3SoundDecayLabel;
    Slider Filter3SoundDecaySlider;
    
    Label Filter3SystemDecayLabel;
    Slider Filter3SystemDecaySlider;
    
    std::unique_ptr<SliderAttachment> Filter3GainAttachment;
    std::unique_ptr<SliderAttachment> Filter3FreqAttachment;
    std::unique_ptr<SliderAttachment> Filter3PoleRadiusAttachment;
    std::unique_ptr<SliderAttachment> Filter3NumObjectsAttachment;
    std::unique_ptr<SliderAttachment> Filter3SoundDecayAttachment;
    std::unique_ptr<SliderAttachment> Filter3SystemDecayAttachment;
};
