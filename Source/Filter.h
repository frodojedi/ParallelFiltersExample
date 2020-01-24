#pragma once

class Filter
{
public:

    Filter()
    {
        
    }
    
   
    bool isEnabled() const noexcept
    {
        return _enabled;
    }

   
    void setEnabled (bool newValue) noexcept
    {
        _enabled = newValue;
    }


    void setFrequency (float newValue)
    {
        _frequency = newValue;
        setCoefficients();
    }
   
    void setPoleRadius (float newValue)
    {
        _poleRadius = (newValue < 0.99999f) ? newValue : 0.99999f;
        setCoefficients();
    }
    
    void setNumObjects (float newValue)
    {
        _numObjects = newValue;
    }
    
    void setSoundDecay (float newValue)
    {
        _soundDecay = (newValue < 0.99995f) ? newValue : 0.99995f;
    }
    
    void setSystemDecay (float newValue)
    {
        _systemDecay = (newValue < 0.99995f) ? newValue : 0.99995f;
    }
    
    void setGain(float newValue)
    {
        _currentGain = newValue;
    }
    
    void applyGain(AudioBuffer<float>& buffer)
    {
        if (_currentGain == _previousGain)
          {
              buffer.applyGain (_currentGain);
          }
          else
          {
              buffer.applyGainRamp (0, buffer.getNumSamples(), _previousGain, _currentGain);
              _previousGain = _currentGain;
          }
    }
    

    
    void prepareToPlay (double sampleRate)
    {
        _srate = float(sampleRate);
        _oneOverSrate = 1.f/_srate;
        _input = 0.0f;
        _systemEnergy = 0.0f;
        _soundLevel = 0.0f;
        _outputCurrentSample = 0.0f;
        _outputPreviousSample.fill(0.0f);
        _previousGain = _currentGain;
        
        
        setFrequency(6460.0f);
        setNumObjects(23);
        setPoleRadius(0.932f);
        setSoundDecay(0.98f);
        setSystemDecay(0.9965f);
    }

    
    void process (AudioBuffer<float>& buffer) noexcept
    {
        if (! _enabled)
        {
            return;
        }
                  
        initOutputPreviousSampleArray(buffer.getNumChannels());
        
        for (auto channel = 0; channel < buffer.getNumChannels(); ++channel){
            
            auto* channelData = buffer.getWritePointer(channel);
            
            for (auto sample = 0; sample < buffer.getNumSamples(); ++sample)
            {
                _inputSystemEnergy = buffer.getSample(channel, sample);
                _systemEnergy += _inputSystemEnergy;
                _systemEnergy *= _systemDecay;
                
                //rand() % 1025 //returns an integer between 0 and 1024
                if (rand() % _maxNumObjects < int(_numObjects))          // If collision add energy
                    _soundLevel += _systemEnergy;
                
                _noise = _random.nextFloat() * 2.0f - 1.0f;
                _input = _soundLevel * _noise;        // Actual Sound is Random
                _soundLevel *= _soundDecay;         // Exponential Sound decay
                
                _input -= _outputCurrentSample * _coeffs[0];      // Do gourd resonance filter calculations
                _input -= _outputPreviousSample.getReference(channel) * _coeffs[1]; // Do gourd resonance filter calculations
                _outputPreviousSample.set(channel, _outputCurrentSample);
                _outputCurrentSample = _input;
                channelData[sample] =  _outputCurrentSample - _outputPreviousSample.getReference(channel);
            }
        }
        
        applyGain(buffer);
    }

    
private:
    
    bool _enabled = true;
    float _input;
    float _outputCurrentSample;
    juce::Array<float> _outputPreviousSample;
    float _noise;
    float _coeffs[2] = {0.0, 0.0};
    float _frequency;
    float _poleRadius;
    float _numObjects;
    const int _maxNumObjects = 1025;
    float _soundLevel;
    float _soundDecay;
    float _systemDecay;
    float _systemEnergy;
    float _inputSystemEnergy;
    float _srate;
    float _oneOverSrate;
    float _previousGain;
    float _currentGain;
    
    Random _random;
    
    void setCoefficients ()
    {
        _coeffs[0] = -_poleRadius * 2.0 * cos(_frequency * MathConstants<float>::twoPi * _oneOverSrate);
        _coeffs[1] = _poleRadius * _poleRadius;
    }
    
    void initOutputPreviousSampleArray(const unsigned int numChannels)
    {
        if (_outputPreviousSample.size() != numChannels)
            _outputPreviousSample.resize(numChannels);
            _outputPreviousSample.fill(0.0f);
    }
};
