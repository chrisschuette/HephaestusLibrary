/* 
 * File:   OpenALSoundLoader.cpp
 * Author: chris
 * 
 * Created on March 10, 2014, 6:39 PM
 */

#include "OpenALSoundLoader.h"
#include "../../DMGD/Resource.h"
#include "OpenALSound.h"
#include "OpenALStream.h"
#include "../../ERR/ERR.h"
#include "../../FSVR/ResourceMetaData.h"
#include "../Formats/WaveFile.h"
#include "../Formats/OggFile.h"
#include "err.h"

#include <AL/al.h>
#include <AL/alc.h>

namespace SND {
    namespace OpenAL {

        OpenALSoundLoader::OpenALSoundLoader()
        : DMGD::Loader<SND::Sound>("OpenALSoundLoader") {
        }

        OpenALSoundLoader::~OpenALSoundLoader() {
        }

        void OpenALSoundLoader::onLoadComplete(FSVR::Resource& resource, const FSVR::ResourceMetaData& metadata) {
            DMGD::Resource<SND::Sound>& res = static_cast<DMGD::Resource<SND::Sound>&> (resource);

            // read out metadata and instantiate
            // the appropriate subclass of SND::Sound
            if (metadata.getType() == "SFX")
                res.setInstance(new OpenALSound);
            else if (metadata.getType() == "OGG") {
                res.setInstance(new OpenALStream);
            } else {
                L(error) << "Unknown sound resource type: " << metadata.getType();
                THROWS("Unknown sound resource type: " + metadata.getType());
            }

            FSVR::Loader::onLoadComplete(resource, metadata);
        }

        void OpenALSoundLoader::instantiate(FSVR::Resource& resource, const FSVR::ResourceMetaData& metadata) {

            DMGD::Resource<SND::Sound>& res = static_cast<DMGD::Resource<SND::Sound>&> (resource);


            if (metadata.getType() == "SFX") {
                OpenALSound* openALSound = static_cast<OpenALSound*> (res.getInstance());
                if (openALSound)
                    instantiateWave(openALSound);
                else {
                    L(error) << "Instantiation failed.";
                    THROWS("Instantiation failed.");
                }
            } else if (metadata.getType() == "OGG") {
                OpenALStream* openALStream = static_cast<OpenALStream*> (res.getInstance());
                if (openALStream)
                    instantiateOgg(openALStream);
                else {
                    L(error) << "Instantiation failed.";
                    THROWS("Instantiation failed.");
                }
            } else {
                L(error) << "Unknown sound resource type: " << metadata.getType();
                THROWS("Unknown sound resource type: " + metadata.getType());
            }

            // mark as active
            FSVR::Loader::instantiate(resource, metadata);
        }

        void OpenALSoundLoader::instantiateWave(OpenALSound * openALSound) {
            ALsizei size;
            ALsizei frequency;
            ALenum format;
            SND::Formats::WaveFile waveFile(getRawData(), getRawDataSize(), false);

            L(normal) << "WAV file info:";
            L(normal) << "bits per sample: " << waveFile.getBitPerSample();
            L(normal) << "frequency: " << waveFile.getFrequency();
            L(normal) << "number of channels: " << waveFile.getNumChannels();
            L(normal) << "size: " << waveFile.getWaveDataSize();
            //The format is worked out by looking at the number of
            //channels and the bits per sample.
            if (waveFile.getNumChannels() == 1) {
                if (waveFile.getBitPerSample() == 8)
                    format = AL_FORMAT_MONO8;
                else if (waveFile.getBitPerSample() == 16)
                    format = AL_FORMAT_MONO16;
            } else if (waveFile.getNumChannels() == 2) {
                if (waveFile.getBitPerSample() == 8)
                    format = AL_FORMAT_STEREO8;
                else if (waveFile.getBitPerSample() == 16)
                    format = AL_FORMAT_STEREO16;
            } else {
                L(error) << "Unknown format.";
                THROWS("Unknown format.");
            }

            frequency = waveFile.getFrequency();
            size = waveFile.getWaveDataSize();

            // reset error state
            int err;
            alGetError();

            L(normal) << "Loading " << size << " bytes into openal buffer.";
            //now we put our data into the openAL buffer and
            //check for success
            alBufferData(openALSound->getBuffer(), format, (void*) waveFile.getWaveData(),
                    size, frequency);
            if ((err = alGetError()) != AL_NO_ERROR) {
                THROWS(getALErrorString(err));
            }
        }

        void OpenALSoundLoader::instantiateOgg(OpenALStream* openALStream) {
            SND::Formats::OggFile* oggFile = new SND::Formats::OggFile(getRawData(), getRawDataSize(), true);
            
            // make loader forget
            // so data is not deleted in d'tor.
            setRawData(0, 0);
            
            openALStream->setSoundFile(oggFile);
            openALStream->setSoundFileType(OpenALStream::OGG);
        }
    }
}
