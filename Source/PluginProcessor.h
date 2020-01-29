#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"


//==============================================================================

class FilterExampleAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    FilterExampleAudioProcessor();
    ~FilterExampleAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void loadPresetFromID(int selectedID);

    
    //==============================================================================
    
    AudioProcessorValueTreeState parameters;
    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    void addGeneralControlsParams (AudioProcessorValueTreeState::ParameterLayout& layout);
    void addFilter1Params (AudioProcessorValueTreeState::ParameterLayout& layout);
    void addFilter2Params (AudioProcessorValueTreeState::ParameterLayout& layout);
    void addFilter3Params (AudioProcessorValueTreeState::ParameterLayout& layout);
    
    //==============================================================================
    void updateParameters();
    void mixBuffers(AudioBuffer<float>& buffer1, AudioBuffer<float>& buffer2);
    //==============================================================================

    AudioTransportSource transportSource;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    
    enum TransportState
       {
           Stopped,
           Starting,
           Playing,
           Stopping
       };
       
       TransportState state;
    
private:
    
    std::atomic<float>* globalGainParameterPanelGeneralControls  = nullptr;
    
    std::atomic<float>* gainParameterPanelFilter1  = nullptr;
    std::atomic<float>* freqParameterPanelFilter1  = nullptr;
    std::atomic<float>* poleRadiusParameterPanelFilter1  = nullptr;
    std::atomic<float>* numObjectsParameterPanelFilter1  = nullptr;
    std::atomic<float>* soundDecayParameterPanelFilter1  = nullptr;
    std::atomic<float>* systemDecayParameterPanelFilter1  = nullptr;
    
    std::atomic<float>* gainParameterPanelFilter2  = nullptr;
    std::atomic<float>* freqParameterPanelFilter2  = nullptr;
    std::atomic<float>* poleRadiusParameterPanelFilter2  = nullptr;
    std::atomic<float>* numObjectsParameterPanelFilter2  = nullptr;
    std::atomic<float>* soundDecayParameterPanelFilter2  = nullptr;
    std::atomic<float>* systemDecayParameterPanelFilter2  = nullptr;
    
    std::atomic<float>* gainParameterPanelFilter3  = nullptr;
    std::atomic<float>* freqParameterPanelFilter3  = nullptr;
    std::atomic<float>* poleRadiusParameterPanelFilter3  = nullptr;
    std::atomic<float>* numObjectsParameterPanelFilter3  = nullptr;
    std::atomic<float>* soundDecayParameterPanelFilter3  = nullptr;
    std::atomic<float>* systemDecayParameterPanelFilter3  = nullptr;
    
    
    float _globalGain;
    
    static const int numFilterInstances = 3;
    
    std::vector<Filter> filterArray;
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterExampleAudioProcessor)
};
