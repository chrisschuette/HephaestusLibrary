/* 
 * File:   DirectoryBundle.cpp
 * Author: chris
 * 
 * Created on June 10, 2013, 2:57 PM
 */

#include "DirectoryBundle.h"
#include "../ERR/ERR.h"

#include <fstream>

namespace BNDL {

    DirectoryBundle::DirectoryBundle(std::string directory)
    : Bundle(boost::filesystem::path(directory).leaf().string())
    , LOG::Source("DirectoryBundle")
    , m_path(directory) {
    }

    DirectoryBundle::DirectoryBundle()
    : Bundle("")
    , LOG::Source("DirectoryBundle")
    , m_path("") {
    }

    DirectoryBundle::~DirectoryBundle() {
    }

    void DirectoryBundle::setDirectory(std::string directory) {
        m_path = directory;
        setID(boost::filesystem::path(directory).leaf().string());
    }

    int DirectoryBundle::read(tLocation location, unsigned char ** data) const {
        boost::filesystem::path filename(location);
        boost::filesystem::path fullpath = m_path / filename;
        std::ifstream is(fullpath.c_str(), std::ifstream::binary);
        if (is) {
            // get length of file:
            is.seekg(0, is.end);
            int length = is.tellg();
            is.seekg(0, is.beg);

            *data = new unsigned char [length];

            L(normal) << location << ": reading " << length << " bytes.";

            is.read((char*)*data, length);

            if (!is) {
                L(error) << "error: only " << is.gcount() << " could be read";
                THROWS("Error reading " + location);
            }
            is.close();

            return length;

        } else {
            // raise exception
            L(error) << "Unable to read location " << location;
            THROWS("Error reading " + location);
        }
    }

}
