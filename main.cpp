/*
Project 5: Part 2 / 4
 video: Chapter 3 Part 1

Create a branch named Part2

 The 'this' keyword
 
 The purpose of this project part is to show you how accessing member variables of objects INSIDE member functions is very similar to accessing member variables of objects OUTSIDE of member functions, via the 'this' keyword and arrow (->) operator and via the '.' operator.
 This project part will break the D.R.Y. rule, but that is fine for the purpose of this project part.
 
 Instructions:
 1) if you don't have any std::cout statements in main() that access member variables of your U.D.Ts
         write some.
    You can copy some from your Project3's main() if needed.

 2) Do the following for EVERY std::cout statement in main() that uses the UDT member variables and functions:
    a) write a member function that prints the same thing out, but uses the proper techniques inside the member functions to access the same member variables/functions.
    b) be explicit with your use of 'this->' in those member functions so we see how you're accessing/calling those member variables and functions *inside*
    c) call that member function AFTER your std::cout statement in main.
    NOTE: if your member functions being called in main() use std::cout statements, you don't need to create duplicates of these functions.  you only need to create member functions for the std::cout statements that exist in main().
        
 3) you should see 2 (almost) identical messages in the program output for each member function you add:
    one for the std::cout line, and one for the member function's output
 
 4) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 */

/*
 example:
 */
#include <iostream>
namespace Example
{
    //a User-Defined Type
    struct MyFoo
    {
        MyFoo();
        ~MyFoo();
        
        void printDetailedMemberInfo();
        
        int returnValue() { return 3; }
        float memberVariable = 3.14f;
    };

    MyFoo::MyFoo() { std::cout << "creating MyFoo" << std::endl; }
    MyFoo::~MyFoo() { std::cout << "destroying MyFoo" << std::endl; }
        
	// 2a) the member function whose function body is almost identical to the std::cout statement in main.
    //Remember to NAME FUNCTIONS WHAT THEY DO.
    void MyFoo::printDetailedMemberInfo() //function name contains a verb!!!
    { 
        // 2b) explicitly using 'this' inside this member function.
        std::cout << "MyFoo returnValue(): " << this->returnValue() << " and MyFoo memberVariable: " << this->memberVariable << std::endl; 
    }  
    
    int main()
    {
        //an instance of the User-Defined Type named mf
        MyFoo mf;
        
        // 1) a std::cout statement that uses mf's member variables
        std::cout << "mf returnValue(): " << mf.returnValue() << " and mf memberVariable: " << mf.memberVariable << std::endl; 
        
        // 2c) calling mf's member function.  the member function's body is almost identical to the cout statement above.
        mf.printDetailedMemberInfo();
        return 0;
    }
}

/*

 Ignore the Atomic.h and LeakedObjectDetector.h files for now.
 You will use those in Part 3 of this project.
*/

#include <iostream>
#include <chrono>
#include <thread>
#include <random>
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
    void acceptControlVoltage(bool externalCV);
    void sweepFrequencies(double startFrequency, double stopFrequency, double timeInSeconds);
    void printThisOscillator();
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

void SimpleOscillator::acceptControlVoltage(bool externalCV)
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

void SimpleOscillator::printThisOscillator()
{
    std::cout << "\nSetting Oscillator Frequency to " + std::to_string(this->frequency) + " Hz\n" << std::endl;
}

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
        double getSampleRate();

        void setAudioDevice(int audioDeviceID);
        std::string getAudioProps(AudioInput audioInput);
        void setDefaultDeviceSettings();
        void printThisAudioInputProperties(); 
    };

    void setInputAmplitude(double amplitude);
    void processInputStream(bool process);
    void invertInputPolarity(bool polarity);
    void increaseSaturation();
    void printThisAudioInput();
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

void AudioInput::printThisAudioInput()
{
    std::cout << "\nSetting Input Amplitude to " + std::to_string(this->amplitude) + " \n" << std::endl;
}

double AudioInput::AudioInputProperties::getSampleRate()
{
    return sampleRate;
}

void AudioInput::AudioInputProperties::setAudioDevice(int devID)
{
    deviceID = devID;
}

std::string AudioInput::AudioInputProperties::getAudioProps(AudioInput inputAudio)
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

void AudioInput::AudioInputProperties::printThisAudioInputProperties()
{    
    std::cout << "Audio Device sample rate is set to " + std::to_string(this->sampleRate) + "\n" << std::endl;
}

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

        std::string printSampleInfo();
        void loadSample(std::string audioFile);
        void reduceBitDepth(int bitDepth, int bitDepthReduction = 2);
        void loadingFileProgress(double length);
        void printThisSample();
    };

    void modulateSampleRate(SimpleOscillator oscillator);    
    void playSample();
    void loopSample();
    void loopSampleNTimes(int numOfLoops);
    void printThisSamplePlayer();
};

SamplePlayer::SamplePlayer(): loopStart(127900), loopEnd(865000)
{
    std::cout << "\nSamplePlayer being constructed!\n" << std::endl;
}

SamplePlayer::~SamplePlayer()
{
    std::cout << "\nSamplePlayer being destructed!\n" << std::endl;
}

void SamplePlayer::Sample::loadSample(std::string audioFileToLoad)
{
    std::cout << "\nThe sample " + audioFileToLoad + " has been loaded \n" << std::endl;
}

void SamplePlayer::playSample()
{
    std::cout << "\nNow playing the loaded sample\n" << std::endl;
}

void SamplePlayer::loopSample()
{
    loop = true;
    std::cout << "\nLooping file from sample number" + std::to_string(loopStart) + " to sample number " + std::to_string(loopEnd) << std::endl;
}

void SamplePlayer::modulateSampleRate(SimpleOscillator oscillator)
{
    std::cout << "\nSample rate of " + std::to_string(sampleRate) + " is being modulated by the simple oscillator's frequency of " + std::to_string(oscillator.frequency) + "and the simple oscillator's frequency. Also, bananas are berries and strawberries are not!!\n" << std::endl;
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

void SamplePlayer::printThisSamplePlayer()
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

std::string SamplePlayer::Sample::printSampleInfo()
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

void SamplePlayer::Sample::printThisSample()
{
    std::cout << "\nBit depth reduced to " + std::to_string(this->bitDepth) + " bits\n" << std::endl;
}
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
int main()
{
    SimpleOscillator osc;
    osc.setOscillatorFrequency(9.0210);
    osc.acceptControlVoltage(true);
    osc.sendOutputToOtherDevices(107.3);
    osc.sweepFrequencies(45, 6000, 1);
    std::cout << "\nSetting Oscillator Frequency to " + std::to_string(osc.frequency) + " Hz\n" << std::endl;
    osc.printThisOscillator();
    
    

    AudioInput audioInput;
    audioInput.processInputStream(true);
    audioInput.invertInputPolarity(false);
    audioInput.setInputAmplitude(3.9);
    audioInput.increaseSaturation();
    std::cout << "\nSetting Input Amplitude to " + std::to_string(audioInput.amplitude) + " \n" << std::endl;
    audioInput.printThisAudioInput();

    SamplePlayer playa;
    playa.playSample();
    playa.loopSample();
    playa.modulateSampleRate(osc);
    playa.loopSampleNTimes(12);
    std::cout << "\nPlayback at a sample rate of " + std::to_string(playa.sampleRate) << std::endl;
    playa.printThisSamplePlayer();

    SamplePlayer::Sample sampl;
    sampl.loadSample("./samples/snare.wav");
    sampl.printSampleInfo();
    sampl.loadingFileProgress(5000);
    std::cout << "Bit depth reduced to " + std::to_string(sampl.bitDepth) + " bits\n" << std::endl;
    sampl.printThisSample();

    AudioInput::AudioInputProperties audioInputProps;
    audioInputProps.getAudioProps(audioInput);
    audioInputProps.getSampleRate();
    audioInputProps.setAudioDevice(1);
    audioInputProps.setDefaultDeviceSettings();
    audioInputProps.setAudioDevice(2);
    audioInputProps.setDefaultDeviceSettings();
    audioInputProps.setAudioDevice(0);
    audioInputProps.setDefaultDeviceSettings();
    std::cout << "Audio Device sample rate is set to " + std::to_string(audioInputProps.sampleRate) + "\n" << std::endl;
    audioInputProps.printThisAudioInputProperties();

    NoiseMaker noizy;
    noizy.makeNoise(9.0210, 12);
    noizy.loadAndPlaySample("./samples/snare.wav", 12);

    Sampler sampler;
    sampler.setInputForSampling(3.9, 1);
    sampler.crushSample("./samples/snare.wav", 8);
    
    std::cout << "good to go!" << std::endl;

    return 0;
}
