/* 
 * File:   Configuration.h
 * Author: chris
 *
 * Created on October 3, 2011, 1:31 PM
 */

#ifndef APP_CONFIGURATION_H
#define	APP_CONFIGURATION_H

#include "../LOG/Source.h"
#include <string>
#include <libconfig.h++>
#include <list>
#include <memory>

namespace APP {
    class Configuration : public LOG::Source {
    public:
        Configuration();
        Configuration(std::string ConfigFile);
        virtual ~Configuration();

        void ReadConfig(std::string Configuration);
        void ReadConfigFile(std::string ConfigFile);

        //Config routines
        bool ValueExists(std::string Path);

        template<class T>
        bool Get(const std::string &path, T &value) {
            if (m_pConfiguration != 0)
                return m_pConfiguration->lookupValue(path, value);
            return false;
        }
        bool IsComplete();
        void CheckComplete();
        void AddCompulsory(std::string Path);
    private:
        libconfig::Config* m_pConfiguration;
        std::list<std::string> m_Compulsory;
    };
}
#endif	/* APP_CONFIGURATION_H */

