/* 
 * File:   WaveFile.h
 * Author: chris
 *
 * Created on March 11, 2014, 3:15 PM
 */

#ifndef FORMATS_WAVEFILE_H
#define	FORMATS_WAVEFILE_H

#include "../SoundFile.h"
#include "../../SYS/sys.h"

namespace SND {
    namespace Formats {

        class WaveFile : public SND::SoundFile {
        private:

            /*
             * Struct that holds the RIFF data of the Wave file.
             * The RIFF data is the meta data information that holds,
             * the ID, size and format of the wave file
             */
            struct RIFF_Header {
                byte chunkID[4];
                dword chunkSize; //size not including chunkSize or chunkID
                byte format[4];
            };

            /*
             * Struct to hold fmt subchunk data for WAVE files.
             */
            struct WAVE_Format {
                byte subChunkID[4];
                dword subChunkSize;
                word audioFormat;
                word numChannels;
                dword sampleRate;
                dword byteRate;
                word blockAlign;
                word bitsPerSample;
            };

            /*
             * Struct to hold the data of the wave file
             */
            struct WAVE_Data {
                byte subChunkID[4]; //should contain the word data
                dword subChunk2Size; //Stores the size of the data block
            };
        public:
            WaveFile(unsigned char * rawData, unsigned int rawDataSize, bool ownsData = true);
            virtual ~WaveFile();

            virtual int getWaveDataSize() const;

            virtual int read(unsigned char* buffer, unsigned int bytesToRead);
            unsigned char* getWaveData() { return m_waveData; }
        private:
            void processHeader();
            unsigned char* m_waveData;
            unsigned char* m_waveDataPtr;
            unsigned int m_waveDataSize;
        };
    }
}
#endif	/* FORMATS_WAVEFILE_H */

