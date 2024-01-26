/*
 Project 5: Part 3 / 4
 video: Chapter 3 Part 4: 

Create a branch named Part3

 the 'new' keyword

 1) add #include "LeakedObjectDetector.h" to main
 
 2) Add 'JUCE_LEAK_DETECTOR(OwnerClass)' at the end of your UDTs.
 
 3) write the name of your class where it says "OwnerClass"
 
 4) write wrapper classes for each type similar to how it was shown in the video
 
 5) update main() 
      replace your objects with your wrapper classes, which have your UDTs as pointer member variables.
      
    This means if you had something like the following in your main() previously: 
*/
#if false
 Axe axe;
 std::cout << "axe sharpness: " << axe.sharpness << "\n";
 #endif
 /*
    you would update that to use your wrappers:
    
 */

#if false
AxeWrapper axWrapper( new Axe() );
std::cout << "axe sharpness: " << axWrapper.axPtr->sharpness << "\n";
#endif
/*
notice that the object name has changed from 'axe' to 'axWrapper'
You don't have to do this, you can keep your current object name and just change its type to your Wrapper class

6) If you have a class that has a nested class in it, and an instantiation of that nested class as a member variable, 
    - you do not need to write a Wrapper for that nested class
    - you do not need to replace that nested instance with a wrapped instance.
    If you want an explanation, message me in Slack

7) If you were using any UDTs as function arguments like this:
*/
#if false
void someMemberFunction(Axe axe);
#endif
/*
  Pass those arguments by Reference now that you know what references are (Project 6 Part 2).
*/
#if false
void someMemberFunction(Axe& axe);
#endif
/*
If you aren't modifying the passed-in object inside the function, pass by 'const reference'.
Marking a function parameter as 'const' means that you are promising that the parameter will not be modified.
Additionally, you can mark class member functions as 'const'
If you do this, you are promising that the member function will not modify any member variables.

Mark every member function that is not modifying any member variables as 'const'
*/
#if false
//a function where the argument is passed by const-ref
void someMemberFunction(const Axe& axe);

//a member function that is marked const, meaning it will not modify any member variables of the 'Axe' class.
void Axe::aConstMemberFunction() const { }
#endif
/*
 8) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 
 see here for an example: https://repl.it/@matkatmusic/ch3p04example

 Clear any warnings about exit-time-destructors.
 Suppress them by adding -Wno-exit-time-destructors to the .replit file with the other warning suppression flags
 */




#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include "LeakedObjectDetector.h"
/*
 copied UDT 1:
 */
struct SimpleOscillator
{
    SimpleOscillator();
    ~SimpleOscillator();

    double frequency = 440.0;
    unsigned int waveform = 0;
    int octave = 0;
    double drift, output;

    void setOscillatorFrequency(double frequency);
    void sendOutputToOtherDevices(double output);
    void acceptControlVoltage(bool externalCV) const;
    void sweepFrequencies(double startFrequency, double stopFrequency, double timeInSeconds);
    void printThisOscillator() const;

    JUCE_LEAK_DETECTOR(SimpleOscillator)
};

SimpleOscillator::SimpleOscillator(): drift(0.213), output(0.707)
{
    std::cout << "\nSimpleOscillator being constructed!\n" << std::endl;
}

SimpleOscillator::~SimpleOscillator()
{
    std::cout << "\nSimpleOscillator being destructed!\n" << std::endl;
}

void SimpleOscillator::setOscillatorFrequency(double oscFrequency)
{
    frequency = oscFrequency;
}

void SimpleOscillator::sendOutputToOtherDevices(double extOutput)
{
    output = extOutput;
}

void SimpleOscillator::acceptControlVoltage(bool externalCV) const
{
    if (externalCV)
    {
        std::cout << "\nexternal CV enabled\n" << std::endl;
    }
    else
    {
        std::cout << "\nexternal CV not disabled\n" << std::endl;
    }
}

void SimpleOscillator::sweepFrequencies(double startFq, double stopFq, double numOfSeconds)
{
    double fqIncrement = 100;
    double totalSteps = (stopFq - startFq) / fqIncrement;
    double timeIncrement = numOfSeconds / totalSteps;
    double currentFq = startFq;

    while (currentFq <= stopFq)
    {
        std::cout << "\nCurrent Frequency: " << std::to_string(currentFq) + " Hz" << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(timeIncrement * 1000)));
        currentFq += fqIncrement;
    }
}

void SimpleOscillator::printThisOscillator() const
{
    std::cout << "\nSetting Oscillator Frequency to " + std::to_string(this->frequency) + " Hz\n" << std::endl;
}

struct SimpleOscillatorWrapper
{
    SimpleOscillator* oscPtr{nullptr};

    SimpleOscillatorWrapper(SimpleOscillator* ptr) : oscPtr(ptr) {}
    ~SimpleOscillatorWrapper()
    {
        delete oscPtr;
    }
    JUCE_LEAK_DETECTOR(SimpleOscillatorWrapper)
};

/*
 copied UDT 2:
 */
struct AudioInput
{
    AudioInput();
    ~AudioInput();

    double amplitude = 0.707;
    bool stereo = true;
    double hpfCutoff = 20.0;
    double saturation = 0.5;
    bool polarity;

    struct AudioInputProperties
    {
        AudioInputProperties();
        ~AudioInputProperties();

        double sampleRate = 44100.0;
        int channels, bitDepth, bufferSize, deviceID;
        
        double getSampleRate() const;
        void setAudioDevice(int audioDeviceID);
        std::string getAudioProps(AudioInput& audioInput) const;
        void setDefaultDeviceSettings();
        void printThisAudioInputProperties() const; 

        JUCE_LEAK_DETECTOR(AudioInputProperties)
    };

    void setInputAmplitude(double amplitude);
    void processInputStream(bool process);
    void invertInputPolarity(bool polarity);
    void increaseSaturation();
    void printThisAudioInput() const;

    JUCE_LEAK_DETECTOR(AudioInput)
};

AudioInput::AudioInput(): polarity(false)
{
    std::cout << "\nAudioInput being constructed!\n" << std::endl;
}

AudioInput::~AudioInput()
{
    std::cout << "\nAudioInput being destructed!\n" << std::endl;
}

AudioInput::AudioInputProperties::AudioInputProperties(): channels(2), bitDepth(16), bufferSize(128), deviceID(0)
{
    std::cout << "\nAudioInputProperties being constructed!\n" << std::endl;
}

AudioInput::AudioInputProperties::~AudioInputProperties()
{
    std::cout << "\nAudioInputProperties being destructed!\n" << std::endl;
}

void AudioInput::setInputAmplitude(double amplitudeAmt)
{
    amplitude = amplitudeAmt;
}

void AudioInput::processInputStream(bool shouldProcess)
{
    if (shouldProcess)
    {
        std::cout << "\nA Lichtenberg figure is a branching, tree-like pattern that is created by the passage of high-voltage electrical discharges along the surface or through insulating materials. These figures can also appear on the skin of lightning strike victims\n" << std::endl;
    }
}

void AudioInput::invertInputPolarity(bool invert)
{
    polarity = invert;
}

void AudioInput::printThisAudioInput() const
{
    std::cout << "\nSetting Input Amplitude to " + std::to_string(this->amplitude) + " \n" << std::endl;
}

double AudioInput::AudioInputProperties::getSampleRate() const
{
    return sampleRate;
}

void AudioInput::AudioInputProperties::setAudioDevice(int devID)
{
    deviceID = devID;
}

std::string AudioInput::AudioInputProperties::getAudioProps(AudioInput& inputAudio) const
{
    std::string audioProps = "\nSample Rate: " + std::to_string(inputAudio.amplitude) + " Number of Channels: " + std::to_string(inputAudio.stereo) +
                             std::to_string(inputAudio.hpfCutoff) + " Resonance: " + std::to_string(inputAudio.saturation) + "\nPolarity: " + std::to_string(inputAudio.polarity) + "\n";

    return audioProps;
}

void AudioInput::increaseSaturation()
{
    while (saturation < 1.0)
    {
        double increment = saturation/10;
        if (saturation + increment > 1.0)
        {
            saturation = 1.0;
            std::cout << "\nSaturation increased to " + std::to_string(saturation) << std::endl;
            return;
        }
        saturation += increment;
        std::cout << "\nSaturation increased to " + std::to_string(saturation) << std::endl;
    } 
}

void AudioInput::AudioInputProperties::setDefaultDeviceSettings()
{
    for (int i = 3; i >= 0; --i)
    {
        if (deviceID != 0)
        {
            std::cout << "\nPlease select a valid device ID\n" << std::endl;
        }
        else
        {
            sampleRate = 44100.0;
            channels = 2;
            bitDepth = 16;
            bufferSize = 128;
            std::cout << "\nDefault device connected, settings have been applied\n" << std::endl;
            return;
        }
    }
}

void AudioInput::AudioInputProperties::printThisAudioInputProperties() const
{    
    std::cout << "Audio Device sample rate is set to " + std::to_string(this->sampleRate) + "\n" << std::endl;
}

struct AudioInputWrapper
{
    AudioInput* inputPtr{nullptr};

    AudioInputWrapper(AudioInput* ptr) : inputPtr(ptr) {}
    ~AudioInputWrapper()
    {
        delete inputPtr;
    }
    JUCE_LEAK_DETECTOR(AudioInputWrapper)
};

/*
 copied UDT 3:
 */
struct SamplePlayer
{
    SamplePlayer();
    ~SamplePlayer();

    int transpose = 0;
    bool loop = false;
    double sampleRate = 44100.0;
    int loopStart, loopEnd;

    struct Sample
    {
        Sample();
        ~Sample();

        std::string audioFile = "./samples/sample.wav\n";
        int channels = 2;
        int bitDepth = 16;
        double length;
        int index;

        std::string printSampleInfo() const;
        void loadSample(std::string audioFile) const;
        void reduceBitDepth(int bitDepth, int bitDepthReduction = 2);
        void loadingFileProgress(double length);
        void printThisSample() const;

        JUCE_LEAK_DETECTOR(Sample)
    };

    void modulateSampleRate(double rate);    
    void playSample() const;
    void loopSample();
    void loopSampleNTimes(int numOfLoops);
    void printThisSamplePlayer() const;

    JUCE_LEAK_DETECTOR(SamplePlayer)
};

SamplePlayer::SamplePlayer(): loopStart(127900), loopEnd(865000)
{
    std::cout << "\nSamplePlayer being constructed!\n" << std::endl;
}

SamplePlayer::~SamplePlayer()
{
    std::cout << "\nSamplePlayer being destructed!\n" << std::endl;
}

void SamplePlayer::Sample::loadSample(std::string audioFileToLoad) const
{
    std::cout << "\nThe sample " + audioFileToLoad + " has been loaded \n" << std::endl;
}

void SamplePlayer::playSample() const
{
    std::cout << "\nNow playing the loaded sample\n" << std::endl;
}

void SamplePlayer::loopSample()
{
    loop = true;
    std::cout << "\nLooping file from sample number" + std::to_string(loopStart) + " to sample number " + std::to_string(loopEnd) << std::endl;
}

void SamplePlayer::modulateSampleRate(double rate)
{
    std::cout << "\nSample rate of " + std::to_string(sampleRate) + " is being modulated by the simple oscillator's frequency of " + std::to_string(rate) + "and the simple oscillator's frequency. Also, bananas are berries and strawberries are not!!\n" << std::endl;
}

void SamplePlayer::loopSampleNTimes(int numOfLoops)
{
    loop = true;
    int loopCount = 1;
    while (numOfLoops > 0)
    {
        std::cout << "\nLooping file. Loop number " + std::to_string(loopCount) << std::endl;
        --numOfLoops;
        ++loopCount;
    }
    loop = false;
}

void SamplePlayer::printThisSamplePlayer() const
{
    std::cout << "\nPlayback at a sample rate of " + std::to_string(this->sampleRate) << std::endl;
}

SamplePlayer::Sample::Sample(): length(2000.0), index(0)
{
    std::cout << "\nSample being constructed!\n" << std::endl;
}

SamplePlayer::Sample::~Sample()
{
    std::cout << "\nSample being destructed!\n" << std::endl;
}

std::string SamplePlayer::Sample::printSampleInfo() const
{
    std::string sampleInfo = "\nSample file: " + audioFile +" Number of Channels: " + std::to_string(channels) + " Number of Bits: " + std::to_string(bitDepth) + " Sample Length: " + std::to_string(length) + " Sample Index: " + std::to_string(index) + "\n";

    return sampleInfo;
}

void SamplePlayer::Sample::reduceBitDepth(int depthOfBits, int reductionAmount)
{
    bitDepth = depthOfBits / reductionAmount;
}

void SamplePlayer::Sample::loadingFileProgress(double lengthOfFile)
{
    double originalLength = lengthOfFile;
    double loadRate = 800.00; //arbitrary number of samples per second
    double dataChunk = 100;

    while (lengthOfFile > 0) 
    {
        lengthOfFile -= dataChunk;
        if (lengthOfFile < 0)
        {
            lengthOfFile = 0;
        }

        double loadedPercentage = 100.0 * (1 - (lengthOfFile / originalLength));
        std::cout << "\nLoading progress: " << loadedPercentage << "%\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(dataChunk / loadRate * 250)));
    }
    ++index;
    std::cout << "\nLoading complete. Sample available at index " + std::to_string(index) + "\n" << std::endl;
}

void SamplePlayer::Sample::printThisSample() const
{
    std::cout << "\nBit depth reduced to " + std::to_string(this->bitDepth) + " bits\n" << std::endl;
}

struct SamplePlayerWrapper
{
    SamplePlayer* playaPtr{nullptr};

    SamplePlayerWrapper(SamplePlayer* ptr) : playaPtr(ptr) {}
    ~SamplePlayerWrapper()
    {
        delete playaPtr;
    }
    JUCE_LEAK_DETECTOR(SamplePlayerWrapper)
};

/*
 new UDT 4:
 with 2 member functions
 */
struct NoiseMaker
{
    NoiseMaker();
    ~NoiseMaker();

    SimpleOscillator squareOscillator;
    SamplePlayer eightBitSampler;
    SamplePlayer::Sample file;

    void makeNoise(double frequency, int loopCount);
    void loadAndPlaySample(std::string fileName, int loopCount); 

    JUCE_LEAK_DETECTOR(NoiseMaker)
};

NoiseMaker::NoiseMaker()
{
    std::cout << "\nNoiseMaker being constructed!\n" << std::endl;
}

NoiseMaker::~NoiseMaker()
{
    std::cout << "\nNoiseMaker being destructed!\n" << std::endl;
}

void NoiseMaker::makeNoise(double frq, int numLoops)
{
    squareOscillator.setOscillatorFrequency(frq);
    eightBitSampler.loopSample();
    eightBitSampler.loopSampleNTimes(numLoops);

    std::cout << "\nMaking noise!" << std::endl;
}

void NoiseMaker::loadAndPlaySample(std::string sampleName, int loopCount)
{
    file.loadSample(sampleName);
    eightBitSampler.loopSample();
    eightBitSampler.loopSampleNTimes(loopCount);

    std::cout << "\nSample loaded and playing\n" << std::endl;
}

struct NoiseMakerWrapper
{
    NoiseMaker* noisePtr{nullptr};
    NoiseMakerWrapper(NoiseMaker* ptr) : noisePtr(ptr) {}
    ~NoiseMakerWrapper()
    {
        delete noisePtr;
    }
};
/*
 new UDT 5:
 with 2 member functions
 */
struct Sampler
{
    Sampler();
    ~Sampler();    

    AudioInput inputAudio;
    AudioInput::AudioInputProperties inputProps;
    SamplePlayer::Sample sample;

    void setInputForSampling(double amplitude, int deviceID);
    void crushSample(std::string fileName, int bitDepth);

    JUCE_LEAK_DETECTOR(Sampler)
};

Sampler::Sampler()
{
    std::cout << "\nSampler being constructed!\n" << std::endl;
}

Sampler::~Sampler()
{
    std::cout << "\nSampler being destructed!\n" << std::endl;
}

void Sampler::setInputForSampling(double amplitude, int deviceID)
{
    inputProps.setDefaultDeviceSettings(); 
    inputAudio.setInputAmplitude(amplitude);
    inputProps.setAudioDevice(deviceID);

    std::cout << "\nReady to Record!" << std::endl;
}

void Sampler::crushSample(std::string fileName, int bitDepth)
{
    sample.loadSample(fileName);
    sample.reduceBitDepth(bitDepth);
    std::cout << "\nSample file " + fileName + " has been reduced to " + std::to_string(bitDepth) << std::endl;
}

struct SamplerWrapper
{
    Sampler* samplerPtr{nullptr};

    SamplerWrapper(Sampler* ptr) : samplerPtr(ptr) {}
    ~SamplerWrapper()
    {
        delete samplerPtr;
    }
    JUCE_LEAK_DETECTOR(SamplerWrapper)
};

/*
 MAKE SURE YOU ARE NOT ON THE MASTER BRANCH

 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].

 If you didn't already: 
    Make a pull request after you make your first commit
    pin the pull request link and this repl.it link to our DM thread in a single message.

 send me a DM to review your pull request when the project is ready for review.

 Wait for my code review.
 */

#include <iostream>
#include "LeakedObjectDetector.h"
int main()
{
    SimpleOscillatorWrapper osc(new SimpleOscillator());
    osc.oscPtr->setOscillatorFrequency(9.0210);
    osc.oscPtr->acceptControlVoltage(true);
    osc.oscPtr->sendOutputToOtherDevices(107.3);
    osc.oscPtr->sweepFrequencies(45, 6000, 1);
    std::cout << "\nSetting Oscillator Frequency to " + std::to_string(osc.oscPtr->frequency) + " Hz\n" << std::endl;
    osc.oscPtr->printThisOscillator();



    AudioInputWrapper audioInput(new AudioInput());
    audioInput.inputPtr->processInputStream(true);
    audioInput.inputPtr->invertInputPolarity(false);
    audioInput.inputPtr->setInputAmplitude(3.9);
    audioInput.inputPtr->increaseSaturation();
    std::cout << "\nSetting Input Amplitude to " + std::to_string(audioInput.inputPtr->amplitude) + " \n" << std::endl;
    audioInput.inputPtr->printThisAudioInput();

    SamplePlayerWrapper playa(new SamplePlayer());
    playa.playaPtr->playSample();
    playa.playaPtr->loopSample();
    playa.playaPtr->modulateSampleRate(23.4);
    playa.playaPtr->loopSampleNTimes(12);
    std::cout << "\nPlayback at a sample rate of " + std::to_string(playa.playaPtr->sampleRate) << std::endl;
    playa.playaPtr->printThisSamplePlayer();

    SamplePlayer::Sample sampl;
    sampl.loadSample("./samples/snare.wav");
    sampl.printSampleInfo();
    sampl.loadingFileProgress(5000);
    std::cout << "Bit depth reduced to " + std::to_string(sampl.bitDepth) + " bits\n" << std::endl;
    sampl.printThisSample();

    AudioInput::AudioInputProperties audioInputProps;
    audioInputProps.getAudioProps(*audioInput.inputPtr);
    audioInputProps.getSampleRate();
    audioInputProps.setAudioDevice(1);
    audioInputProps.setDefaultDeviceSettings();
    audioInputProps.setAudioDevice(2);
    audioInputProps.setDefaultDeviceSettings();
    audioInputProps.setAudioDevice(0);
    audioInputProps.setDefaultDeviceSettings();
    std::cout << "Audio Device sample rate is set to " + std::to_string(audioInputProps.sampleRate) + "\n" << std::endl;
    audioInputProps.printThisAudioInputProperties();

    NoiseMakerWrapper noizy(new NoiseMaker());
    noizy.noisePtr->makeNoise(9.0210, 12);
    noizy.noisePtr->loadAndPlaySample("./samples/snare.wav", 12);

    SamplerWrapper sampler(new Sampler());
    sampler.samplerPtr->setInputForSampling(3.9, 1);
    sampler.samplerPtr->crushSample("./samples/snare.wav", 8);

    std::cout << "good to go!" << std::endl;

    return 0;
}
