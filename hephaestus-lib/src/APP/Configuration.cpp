/* 
 * File:   Configuration.cpp
 * Author: chris
 * 
 * Created on October 3, 2011, 1:31 PM
 */

#include "Configuration.h"
#include <sstream>
#include "../ERR/ERR.h"
#include "../LOG/Core.h"

using namespace APP;

#define NAME "Configuration"

Configuration::Configuration()
: m_pConfiguration(new libconfig::Config) {
}

Configuration::Configuration(std::string ConfigFile)
: m_pConfiguration(new libconfig::Config) {
    ReadConfigFile(ConfigFile.c_str());
}

void Configuration::ReadConfig(std::string Configuration) {
    try {
        m_pConfiguration->readString(Configuration);
    } catch (libconfig::ParseException& e) {
        L(error) << e.what() << ": " << e.getError() << " "
                << e.getFile() << " -- line: " << e.getLine();
        THROW(1, "Unable to parse config file.");
    }
}

void Configuration::ReadConfigFile(std::string ConfigFile) {
    try {
        m_pConfiguration->readFile(ConfigFile.c_str());
    } catch (libconfig::ParseException& e) {
        L(error) << e.what() << ": " << e.getError() << " "
                << e.getFile() << " -- line: " << e.getLine();
        THROW(1, "Unable to parse config file.");
    } catch (libconfig::FileIOException& f) {
        THROW(2, "Unable to open config file: " + ConfigFile);
    }

}

Configuration::~Configuration() {
    delete m_pConfiguration;
}

bool Configuration::ValueExists(std::string Path) {
    if (m_pConfiguration != 0)
        return m_pConfiguration->exists(Path);
    return false;
}

void Configuration::CheckComplete() {
    std::list<std::string>::iterator it;
    for (it = m_Compulsory.begin(); it != m_Compulsory.end(); it++) {
        if (!ValueExists(*it)) {
            THROW(1, "Compulsory value not found in config: " + *it);
        }
    }
}

bool Configuration::IsComplete() {
    std::list<std::string>::iterator it;
    for (it = m_Compulsory.begin(); it != m_Compulsory.end(); it++) {
        if (!ValueExists(*it)) {
            return false;
        }
    }
    return true;
}

void Configuration::AddCompulsory(std::string Path) {
    m_Compulsory.push_back(Path);
}