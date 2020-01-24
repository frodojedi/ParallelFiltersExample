#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FilterExampleAudioProcessor::FilterExampleAudioProcessor()
     : AudioProcessor (BusesProperties().withOutput ("Output", AudioChannelSet::stereo(), true)),
       parametersPanelGeneralControls (*this, nullptr, Identifier ("ParametersPanelGeneralControls"), createParameterLayoutPanelGeneralControls()),
       parametersPanelFilter1 (*this, nullptr, Identifier ("ParametersPanelFilter1"), createParameterLayoutPanelFilter1()),
       parametersPanelFilter2 (*this, nullptr, Identifier ("ParametersPanelFilter2"), createParameterLayoutPanelFilter2()),
       parametersPanelFilter3 (*this, nullptr, Identifier ("ParametersPanelFilter3"), createParameterLayoutPanelFilter3())
{
    filterArray[numFilterInstances];
    
    globalGainParameterPanelGeneralControls = parametersPanelGeneralControls.getRawParameterValue ("global_gain_panel_general_controls");
    
    gainParameterPanelFilter1 = parametersPanelFilter1.getRawParameterValue ("gain_panel_Filter1");
    freqParameterPanelFilter1 = parametersPanelFilter1.getRawParameterValue ("freq_panel_Filter1");
    poleRadiusParameterPanelFilter1 = parametersPanelFilter1.getRawParameterValue ("pole_radius_panel_Filter1");
    numObjectsParameterPanelFilter1 = parametersPanelFilter1.getRawParameterValue ("num_objects_panel_Filter1");
    soundDecayParameterPanelFilter1 = parametersPanelFilter1.getRawParameterValue ("sound_decay_panel_Filter1");
    systemDecayParameterPanelFilter1 = parametersPanelFilter1.getRawParameterValue ("system_decay_panel_Filter1");
    
    gainParameterPanelFilter2 = parametersPanelFilter2.getRawParameterValue ("gain_panel_Filter2");
    freqParameterPanelFilter2 = parametersPanelFilter2.getRawParameterValue ("freq_panel_Filter2");
    poleRadiusParameterPanelFilter2 = parametersPanelFilter2.getRawParameterValue ("pole_radius_panel_Filter2");
    numObjectsParameterPanelFilter2 = parametersPanelFilter2.getRawParameterValue ("num_objects_panel_Filter2");
    soundDecayParameterPanelFilter2 = parametersPanelFilter2.getRawParameterValue ("sound_decay_panel_Filter2");
    systemDecayParameterPanelFilter2 = parametersPanelFilter2.getRawParameterValue ("system_decay_panel_Filter2");
    
    gainParameterPanelFilter3 = parametersPanelFilter3.getRawParameterValue ("gain_panel_Filter3");
    freqParameterPanelFilter3 = parametersPanelFilter3.getRawParameterValue ("freq_panel_Filter3");
    poleRadiusParameterPanelFilter3 = parametersPanelFilter3.getRawParameterValue ("pole_radius_panel_Filter3");
    numObjectsParameterPanelFilter3 = parametersPanelFilter3.getRawParameterValue ("num_objects_panel_Filter3");
    soundDecayParameterPanelFilter3 = parametersPanelFilter3.getRawParameterValue ("sound_decay_panel_Filter3");
    systemDecayParameterPanelFilter3 = parametersPanelFilter3.getRawParameterValue ("system_decay_panel_Filter3");
}

FilterExampleAudioProcessor::~FilterExampleAudioProcessor()
{
    transportSource.setSource(nullptr);
}



//==============================================================================
AudioProcessorValueTreeState::ParameterLayout FilterExampleAudioProcessor::createParameterLayoutPanelGeneralControls()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> params;
    
    auto globalGainParam =  std::make_unique<AudioParameterFloat>
                            ("global_gain_panel_general_controls", // parameterID
                            "Global Gain",                         // parameter name
                            0.0f,                                  // minimum value
                            1.0f,                                  // maximum value
                            0.15f);                                 // default value
    
    params.push_back(std::move(globalGainParam));
    return {params.begin(), params.end()};
}


//==============================================================================
AudioProcessorValueTreeState::ParameterLayout FilterExampleAudioProcessor::createParameterLayoutPanelFilter1()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> params;
    
    auto GainFilter1Param =  std::make_unique<AudioParameterFloat>
                            ("gain_panel_Filter1",              // parameterID
                            "Gain Filter1",                     // parameter name
                            0.0f,                              // minimum value
                            1.0f,                              // maximum value
                            0.1f);                             // default value
    
    auto FreqFilter1Param =  std::make_unique<AudioParameterFloat>
                            ("freq_panel_Filter1",              // parameterID
                            "Freq Filter1",                     // parameter name
                            30.0f,                             // minimum value
                            15000.0f,                          // maximum value
                            6460.0f);                          // default value

    
    auto PoleRadiusFilter1Param = std::make_unique<AudioParameterFloat>
                                 ("pole_radius_panel_Filter1",         // parameterID
                                  "Pole Radius Filter1",               // parameter name
                                  NormalisableRange<float>
                                                          (0.f,        // minimum
                                                          0.99999f,    // maximum
                                                          0.000001f),  // step size
                                                          0.932f,      // default value
                                                          String(),    // label
                                                          AudioProcessorParameter::genericParameter,
                                                          [](float value, int maximumStringLength)
                                                          {
                                                              return String (value);
                                                          },
                                                          [](const String &text)
                                                          {
                                                              return float (text.getDoubleValue());
                                                          }
                                  );
    
    auto NumObjectsFilter1Param = std::make_unique<AudioParameterFloat>
                                 ("num_objects_panel_Filter1",  // parameterID
                                 "Num Objects Filter1",         // parameter name
                                 1.0f,                         // minimum value
                                 1024.0f,                      // maximum value
                                 23.0f);                       // default value
      
    auto SoundDecayFilter1Param = std::make_unique<AudioParameterFloat>
                                 ("sound_decay_panel_Filter1",         // parameterID
                                  "Sound Decay Filter1",               // parameter name
                                  NormalisableRange<float>
                                                          (0.3f,        // minimum
                                                          0.99995f,    // maximum
                                                          0.000001f),  // step size
                                                          0.98f,       // default value
                                                          String(),    // label
                                                          AudioProcessorParameter::genericParameter,
                                                          [](float value, int maximumStringLength)
                                                          {
                                                              return String (value);
                                                          },
                                                          [](const String &text)
                                                          {
                                                              return float (text.getDoubleValue());
                                                          }
                                  );
    
    auto SystemDecayFilter1Param = std::make_unique<AudioParameterFloat>
                                 ("system_decay_panel_Filter1",         // parameterID
                                  "System Decay Filter1",               // parameter name
                                  NormalisableRange<float>
                                                          (0.85f,        // minimum
                                                          0.99995f,     // maximum
                                                          0.000001f),   // step size
                                                          0.9965f,      // default value
                                                          String(),     // label
                                                          AudioProcessorParameter::genericParameter,
                                                          [](float value, int maximumStringLength)
                                                          {
                                                              return String (value);
                                                          },
                                                          [](const String &text)
                                                          {
                                                              return float (text.getDoubleValue());
                                                          }
                                  );
    
    params.push_back(std::move(GainFilter1Param));
    params.push_back(std::move(FreqFilter1Param));
    params.push_back(std::move(PoleRadiusFilter1Param));
    params.push_back(std::move(NumObjectsFilter1Param));
    params.push_back(std::move(SoundDecayFilter1Param));
    params.push_back(std::move(SystemDecayFilter1Param));
    return {params.begin(), params.end()};
}

//==============================================================================
AudioProcessorValueTreeState::ParameterLayout FilterExampleAudioProcessor::createParameterLayoutPanelFilter2()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> params;
    
    auto GainFilter2Param =  std::make_unique<AudioParameterFloat>
                            ("gain_panel_Filter2",              // parameterID
                            "Gain Filter2",                     // parameter name
                            0.0f,                              // minimum value
                            1.0f,                              // maximum value
                            0.1f);                             // default value
    
    auto FreqFilter2Param =  std::make_unique<AudioParameterFloat>
                            ("freq_panel_Filter2",              // parameterID
                            "Freq Filter2",                     // parameter name
                            30.0f,                             // minimum value
                            15000.0f,                          // maximum value
                            6460.0f);                          // default value

    
    auto PoleRadiusFilter2Param = std::make_unique<AudioParameterFloat>
                                 ("pole_radius_panel_Filter2",         // parameterID
                                  "Pole Radius Filter2",               // parameter name
                                  NormalisableRange<float>
                                                          (0.f,        // minimum
                                                          0.99999f,    // maximum
                                                          0.000001f),  // step size
                                                          0.932f,      // default value
                                                          String(),    // label
                                                          AudioProcessorParameter::genericParameter,
                                                          [](float value, int maximumStringLength)
                                                          {
                                                              return String (value);
                                                          },
                                                          [](const String &text)
                                                          {
                                                              return float (text.getDoubleValue());
                                                          }
                                  );
    
    auto NumObjectsFilter2Param = std::make_unique<AudioParameterFloat>
                                 ("num_objects_panel_Filter2",  // parameterID
                                 "Num Objects Filter2",         // parameter name
                                 1.0f,                         // minimum value
                                 1024.0f,                      // maximum value
                                 23.0f);                       // default value
      
    auto SoundDecayFilter2Param = std::make_unique<AudioParameterFloat>
                                 ("sound_decay_panel_Filter2",         // parameterID
                                  "Sound Decay Filter2",               // parameter name
                                  NormalisableRange<float>
                                                          (0.3f,        // minimum
                                                          0.99995f,    // maximum
                                                          0.000001f),  // step size
                                                          0.98f,       // default value
                                                          String(),    // label
                                                          AudioProcessorParameter::genericParameter,
                                                          [](float value, int maximumStringLength)
                                                          {
                                                              return String (value);
                                                          },
                                                          [](const String &text)
                                                          {
                                                              return float (text.getDoubleValue());
                                                          }
                                  );
    
    auto SystemDecayFilter2Param = std::make_unique<AudioParameterFloat>
                                 ("system_decay_panel_Filter2",         // parameterID
                                  "System Decay Filter2",               // parameter name
                                  NormalisableRange<float>
                                                          (0.85f,        // minimum
                                                          0.99995f,     // maximum
                                                          0.000001f),   // step size
                                                          0.9965f,      // default value
                                                          String(),     // label
                                                          AudioProcessorParameter::genericParameter,
                                                          [](float value, int maximumStringLength)
                                                          {
                                                              return String (value);
                                                          },
                                                          [](const String &text)
                                                          {
                                                              return float (text.getDoubleValue());
                                                          }
                                  );
    
    params.push_back(std::move(GainFilter2Param));
    params.push_back(std::move(FreqFilter2Param));
    params.push_back(std::move(PoleRadiusFilter2Param));
    params.push_back(std::move(NumObjectsFilter2Param));
    params.push_back(std::move(SoundDecayFilter2Param));
    params.push_back(std::move(SystemDecayFilter2Param));
    return {params.begin(), params.end()};
}

//==============================================================================
AudioProcessorValueTreeState::ParameterLayout FilterExampleAudioProcessor::createParameterLayoutPanelFilter3()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> params;
    
    auto GainFilter3Param =  std::make_unique<AudioParameterFloat>
                            ("gain_panel_Filter3",              // parameterID
                            "Gain Filter3",                     // parameter name
                            0.0f,                              // minimum value
                            1.0f,                              // maximum value
                            0.1f);                             // default value
    
    auto FreqFilter3Param =  std::make_unique<AudioParameterFloat>
                            ("freq_panel_Filter3",              // parameterID
                            "Freq Filter3",                     // parameter name
                            30.0f,                             // minimum value
                            15000.0f,                          // maximum value
                            6460.0f);                          // default value

    
    auto PoleRadiusFilter3Param = std::make_unique<AudioParameterFloat>
                                 ("pole_radius_panel_Filter3",         // parameterID
                                  "Pole Radius Filter3",               // parameter name
                                  NormalisableRange<float>
                                                          (0.f,        // minimum
                                                          0.99999f,    // maximum
                                                          0.000001f),  // step size
                                                          0.932f,      // default value
                                                          String(),    // label
                                                          AudioProcessorParameter::genericParameter,
                                                          [](float value, int maximumStringLength)
                                                          {
                                                              return String (value);
                                                          },
                                                          [](const String &text)
                                                          {
                                                              return float (text.getDoubleValue());
                                                          }
                                  );
    
    auto NumObjectsFilter3Param = std::make_unique<AudioParameterFloat>
                                 ("num_objects_panel_Filter3",  // parameterID
                                 "Num Objects Filter3",         // parameter name
                                 1.0f,                         // minimum value
                                 1024.0f,                      // maximum value
                                 23.0f);                       // default value
      
    auto SoundDecayFilter3Param = std::make_unique<AudioParameterFloat>
                                 ("sound_decay_panel_Filter3",         // parameterID
                                  "Sound Decay Filter3",               // parameter name
                                  NormalisableRange<float>
                                                          (0.3f,        // minimum
                                                          0.99995f,    // maximum
                                                          0.000001f),  // step size
                                                          0.98f,       // default value
                                                          String(),    // label
                                                          AudioProcessorParameter::genericParameter,
                                                          [](float value, int maximumStringLength)
                                                          {
                                                              return String (value);
                                                          },
                                                          [](const String &text)
                                                          {
                                                              return float (text.getDoubleValue());
                                                          }
                                  );
    
    auto SystemDecayFilter3Param = std::make_unique<AudioParameterFloat>
                                 ("system_decay_panel_Filter3",         // parameterID
                                  "System Decay Filter3",               // parameter name
                                  NormalisableRange<float>
                                                          (0.85f,        // minimum
                                                          0.99995f,     // maximum
                                                          0.000001f),   // step size
                                                          0.9965f,      // default value
                                                          String(),     // label
                                                          AudioProcessorParameter::genericParameter,
                                                          [](float value, int maximumStringLength)
                                                          {
                                                              return String (value);
                                                          },
                                                          [](const String &text)
                                                          {
                                                              return float (text.getDoubleValue());
                                                          }
                                  );
    
    params.push_back(std::move(GainFilter3Param));
    params.push_back(std::move(FreqFilter3Param));
    params.push_back(std::move(PoleRadiusFilter3Param));
    params.push_back(std::move(NumObjectsFilter3Param));
    params.push_back(std::move(SoundDecayFilter3Param));
    params.push_back(std::move(SystemDecayFilter3Param));
    return {params.begin(), params.end()};
}





//==============================================================================
const String FilterExampleAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FilterExampleAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FilterExampleAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FilterExampleAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FilterExampleAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FilterExampleAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FilterExampleAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FilterExampleAudioProcessor::setCurrentProgram (int index)
{
}

const String FilterExampleAudioProcessor::getProgramName (int index)
{
    return {};
}

void FilterExampleAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void FilterExampleAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    transportSource.prepareToPlay (samplesPerBlock, sampleRate);
    
    //Maybe it is better to use the array
    filterArray[0].prepareToPlay(sampleRate);
    filterArray[1].prepareToPlay(sampleRate);
    filterArray[2].prepareToPlay(sampleRate);
    
    updateParameters();
}

void FilterExampleAudioProcessor::releaseResources()
{
    transportSource.releaseResources();
}


bool FilterExampleAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() == AudioChannelSet::disabled())
        return false;
    
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;
 
    return true;
}





void FilterExampleAudioProcessor::updateParameters()
{
    float gainFilter1 = *gainParameterPanelFilter1;
    float freqFilter1 = *freqParameterPanelFilter1;
    float poleRadiusFilter1 = *poleRadiusParameterPanelFilter1;
    float numObjectsFilter1 = *numObjectsParameterPanelFilter1;
    float soundDecayFilter1 = *soundDecayParameterPanelFilter1;
    float systemDecayFilter1 = *systemDecayParameterPanelFilter1;
    
    float gainFilter2 = *gainParameterPanelFilter2;
    float freqFilter2 = *freqParameterPanelFilter2;
    float poleRadiusFilter2 = *poleRadiusParameterPanelFilter2;
    float numObjectsFilter2 = *numObjectsParameterPanelFilter2;
    float soundDecayFilter2 = *soundDecayParameterPanelFilter2;
    float systemDecayFilter2 = *systemDecayParameterPanelFilter2;
    
    float gainFilter3 = *gainParameterPanelFilter3;
    float freqFilter3 = *freqParameterPanelFilter3;
    float poleRadiusFilter3 = *poleRadiusParameterPanelFilter3;
    float numObjectsFilter3 = *numObjectsParameterPanelFilter3;
    float soundDecayFilter3 = *soundDecayParameterPanelFilter3;
    float systemDecayFilter3 = *systemDecayParameterPanelFilter3;
    
    float globalGain = *globalGainParameterPanelGeneralControls;

    filterArray[0].setGain(gainFilter1);
    //filter1.setGain(0.5f);
    filterArray[0].setFrequency(freqFilter1);
    filterArray[0].setPoleRadius(poleRadiusFilter1);
    filterArray[0].setNumObjects(numObjectsFilter1);
    filterArray[0].setSoundDecay(soundDecayFilter1);
    filterArray[0].setSystemDecay(systemDecayFilter1);
    
    filterArray[1].setGain(gainFilter2);
    filterArray[1].setFrequency(freqFilter2);
    filterArray[1].setPoleRadius(poleRadiusFilter2);
    filterArray[1].setNumObjects(numObjectsFilter2);
    filterArray[1].setSoundDecay(soundDecayFilter2);
    filterArray[1].setSystemDecay(systemDecayFilter2);
    
    filterArray[2].setGain(gainFilter3);
    filterArray[2].setFrequency(freqFilter3);
    filterArray[2].setPoleRadius(poleRadiusFilter3);
    filterArray[2].setNumObjects(numObjectsFilter3);
    filterArray[2].setSoundDecay(soundDecayFilter3);
    filterArray[2].setSystemDecay(systemDecayFilter3);
    
    _globalGain = globalGain;
}




//this function merges the content of buffer2 into buffer1
void FilterExampleAudioProcessor::mixBuffers (AudioBuffer<float>& buffer1, AudioBuffer<float>& buffer2)
{
    // Here maybe use a jassert to check that the buffers have the same num samples?
    // jassert (buffer1.getNumSamples() ==  buffer2.getNumSamples());
    for (auto channel = 0; channel < buffer1.getNumChannels(); ++channel){
        
        auto* channelData = buffer1.getWritePointer(channel);
        
        for (auto sample = 0; sample < buffer1.getNumSamples(); ++sample)
        {
            channelData[sample] = buffer1.getSample(channel, sample) + buffer2.getSample(channel, sample) / 2.0f; //is it correct to make the average of the two buffers after having summed them?
        }
    }
}


void FilterExampleAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    updateParameters();
    
    AudioSourceChannelInfo info(buffer);
    
    if (readerSource.get() == nullptr)
    {
        info.clearActiveBufferRegion();
        return;
    }
    transportSource.getNextAudioBlock (info);

    
    
    AudioBuffer<float> cleanInput;
    cleanInput.makeCopyOf(buffer, true);
  
    for (int filterIndex = 0; filterIndex < numFilterInstances; ++filterIndex)
    {
        //Process each filter with a clean input
        AudioBuffer<float> singleFilterBuffer;
        singleFilterBuffer.makeCopyOf(cleanInput, true);
        //FilterArray[filterIndex].setGain(gainLevels[filterIndex]);
        filterArray[filterIndex].process(singleFilterBuffer);
        
        mixBuffers(buffer, singleFilterBuffer);
    }
    
    buffer.applyGain(_globalGain); // I should raather use the mechanism previousGain - currentGain
}


//==============================================================================
bool FilterExampleAudioProcessor::hasEditor() const
{
    return true; 
}

AudioProcessorEditor* FilterExampleAudioProcessor::createEditor()
{
    return new FilterExampleAudioProcessorEditor (*this, parametersPanelGeneralControls, parametersPanelFilter1, parametersPanelFilter2, parametersPanelFilter3);
}

//==============================================================================
void FilterExampleAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FilterExampleAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FilterExampleAudioProcessor();
}