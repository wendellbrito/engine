#include "AudioManager.hpp"

AudioManager::AudioManager()
: accumulatedFrameTime(0)
{
    
}

AudioManager::~AudioManager()
{
    for(auto i = AudioManager::sourceList.begin(); i != AudioManager::sourceList.end(); i++)
    {
        delete (*i);
    }
}

AudioSource* AudioManager::addSound(FileInterface* file)
{
    AudioSource* tempInstance = new AudioSource(file);
    AudioManager::sourceList.push_back(tempInstance);
    return tempInstance;
}

bool AudioManager::removeSound(AudioSource* instance)
{
    bool deleted = false;
    for(auto i = AudioManager::sourceList.begin(); i != AudioManager::sourceList.end(); i++)
    {     
        if((*i) == instance)
        {
            AudioSource* temp = *i;
            temp->stop();
            AudioManager::sourceList.erase(i);
            deleted = true;
            break;
        }
    }
    return deleted;
}

void AudioManager::processSounds(double frameTime)
{
    AudioManager::accumulatedFrameTime += frameTime;
    if(AudioManager::accumulatedFrameTime >= 500)
    {
        for(auto i = AudioManager::sourceList.begin(); i != AudioManager::sourceList.end(); i++)
        {
            AudioSource* temp = *i;
            temp->updateBuffers();
        }
        AudioManager::accumulatedFrameTime = 0;
    }
}
