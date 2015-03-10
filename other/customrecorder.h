#ifndef CUSTOMRECORDER
#define CUSTOMRECORDER


#include <SFML/Audio.hpp>

class CustomRecorder : public sf::SoundBufferRecorder
{
private:

    std::vector<short int> m_samples; ///< Temporary sample buffer to hold the recorded data
    sf::SoundBuffer m_buffer;  ///< Sound buffer that will contain the recorded data

    virtual bool onStart()
    {
        m_samples.clear();
        m_buffer = sf::SoundBuffer();

        return true;
    }

    virtual bool onProcessSamples(const short int * samples, std::size_t sampleCount)
    {
        std::copy(samples, samples + sampleCount, std::back_inserter(m_samples));

        return true;
    }

    virtual void onStop() // optional
    {
        if (!m_samples.empty())
            m_buffer.loadFromSamples(&m_samples[0], m_samples.size(), 1, getSampleRate());
    }

public:

    const sf::SoundBuffer& getBuffer() const
    {
        return m_buffer;
    }

    std::vector<short int> * getSamples(){
        return &m_samples;
    }
};

#endif // CUSTOMRECORDER

