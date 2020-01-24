
#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class PanelGeneralControls : public Component,
                             public ChangeListener
{
public:

    PanelGeneralControls (FilterExampleAudioProcessor& proc, AudioProcessorValueTreeState& valueTreeState) : m_proc(proc)
    {
        m_proc.state = FilterExampleAudioProcessor::TransportState::Stopped;
        
        addAndMakeVisible (&openButton);
        openButton.setButtonText ("Open...");
        openButton.onClick = [this] { openButtonClicked(); };

        addAndMakeVisible (&playButton);
        playButton.setButtonText ("Play");
        playButton.onClick = [this] { playButtonClicked(); };
        playButton.setColour (TextButton::buttonColourId, Colours::green);
        playButton.setEnabled (false);

        addAndMakeVisible (&stopButton);
        stopButton.setButtonText ("Stop");
        stopButton.onClick = [this] { stopButtonClicked(); };
        stopButton.setColour (TextButton::buttonColourId, Colours::red);
        stopButton.setEnabled (false);

        addAndMakeVisible (&loopingToggle);
        loopingToggle.setButtonText ("Loop");
        loopingToggle.onClick = [this] { loopButtonChanged(); };

        addAndMakeVisible (&currentPositionLabel);
        currentPositionLabel.setText ("Stopped", dontSendNotification);
        
        
        globalGainSlider.setColour (Slider::textBoxTextColourId, colourSliderTextBoxText);
        globalGainSlider.setColour (Slider::textBoxOutlineColourId, colourSlidertextBoxOutline);
        globalGainSlider.setColour (Slider::thumbColourId, colourSliderThumb);
        globalGainSlider.setColour (Slider::trackColourId, colourSliderTrack);
        
        globalGainLabel.setText ("Global Gain", dontSendNotification);
        globalGainLabel.attachToComponent (&globalGainSlider, true);
        addAndMakeVisible (globalGainLabel);
        addAndMakeVisible (globalGainSlider);
        
        globalGainAttachment.reset (new SliderAttachment (valueTreeState, "global_gain_panel_general_controls", globalGainSlider));
        
        formatManager.registerBasicFormats();
        m_proc.transportSource.addChangeListener (this);
    }
    
    
    
    ~PanelGeneralControls(){
        
        m_proc.transportSource.removeChangeListener (this);
        globalGainAttachment.reset();
    }
    
    
    void changeListenerCallback (ChangeBroadcaster* source) override
    {
        if (source == &m_proc.transportSource)
        {
            if (m_proc.transportSource.isPlaying())
                changeState (FilterExampleAudioProcessor::TransportState::Playing);
            else
                changeState (FilterExampleAudioProcessor::TransportState::Stopped);
        }
    }
    

    void updateLoopState (bool shouldLoop)
    {
        if (m_proc.readerSource.get() != nullptr)
            m_proc.readerSource->setLooping (shouldLoop);
    }

    void paint (Graphics& g) override
    {
        g.fillAll(colour_background);
        
        Rectangle<int> panelGeneralControlsArea (getLocalBounds());
        //g.setColour (Colours::whitesmoke);
        g.drawRect (panelGeneralControlsArea, 3.0f);
    }
    
    void resized() override
    {
        openButton          .setBounds (10, 10,  getWidth() - 20, 20);
        playButton          .setBounds (10, 40,  getWidth() - 20, 20);
        stopButton          .setBounds (10, 70,  getWidth() - 20, 20);
        loopingToggle       .setBounds (10, 100, getWidth() - 20, 20);
        currentPositionLabel.setBounds (10, 130, getWidth() - 20, 20);
        
        auto sliderLeft = paramLabelWidth + 10;
        globalGainSlider.setBounds (sliderLeft, 200, getWidth() - sliderLeft - 10, 20);
    }
    
private:
    //==============================================================================
    
    FilterExampleAudioProcessor& m_proc;

    TextButton openButton;
    TextButton playButton;
    TextButton stopButton;
    ToggleButton loopingToggle;
    Label currentPositionLabel;

    AudioFormatManager formatManager;
    
    
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    
    enum
    {
        paramControlHeight = 40,
        paramLabelWidth    = 80,
        paramSliderWidth   = 350
    };

    
    Label globalGainLabel;
    Slider globalGainSlider;
    
    std::unique_ptr<SliderAttachment> globalGainAttachment;
    
    
    Colour colour_background = Colours::lightsalmon;
    
    Colour colourText = Colours::black;
    Colour colourSliderThumb = Colours::darkred;
    Colour colourSliderTrack = Colours::whitesmoke;
    Colour colourSliderTextBoxText = colourText;
    Colour colourSlidertextBoxOutline = colourSliderThumb;
    
    
    
    
    //==============================================================================
    void changeState (FilterExampleAudioProcessor::TransportState newState)
    {
        if (m_proc.state != newState)
        {
            m_proc.state = newState;

            switch (m_proc.state)
            {
                case FilterExampleAudioProcessor::TransportState::Stopped:
                    stopButton.setEnabled (false);
                    playButton.setEnabled (true);
                    m_proc.transportSource.setPosition (0.0);
                    break;

                case FilterExampleAudioProcessor::TransportState::Starting:
                    playButton.setEnabled (false);
                    m_proc.transportSource.start();
                    break;

                case FilterExampleAudioProcessor::TransportState::Playing:
                    stopButton.setEnabled (true);
                    break;

                case FilterExampleAudioProcessor::TransportState::Stopping:
                    m_proc.transportSource.stop();
                    break;
            }
        }
    }

    void openButtonClicked()
    {
        FileChooser chooser ("Select a Wave file to play...",
                             {},
                             "*.wav");

        if (chooser.browseForFileToOpen())
        {
            auto file = chooser.getResult();
            auto* reader = formatManager.createReaderFor (file);

            if (reader != nullptr)
            {
                std::unique_ptr<AudioFormatReaderSource> newSource (new AudioFormatReaderSource (reader, true));
                m_proc.transportSource.setSource (newSource.get(), 0, nullptr, reader->sampleRate);
                playButton.setEnabled (true);
                m_proc.readerSource.reset (newSource.release());
            }
        }
    }

    void playButtonClicked()
    {
        updateLoopState (loopingToggle.getToggleState());
        changeState (FilterExampleAudioProcessor::Starting);
    }

    void stopButtonClicked()
    {
        changeState (FilterExampleAudioProcessor::Stopping);
    }

    void loopButtonChanged()
    {
        updateLoopState (loopingToggle.getToggleState());
    }

    //==========================================================================
    
};