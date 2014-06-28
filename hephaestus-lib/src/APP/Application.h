/* 
 * File:   Application.h
 * Author: chris
 *
 * Created on October 3, 2011, 12:01 PM
 */

#ifndef APP_APPLICATION_H
#define	APP_APPLICATION_H

#include <string>

namespace APP {
    class Configuration;

    class Application {
    public:
        Application();
        void LoadConfiguration(std::string Filename);
        virtual void Init() = 0;
        virtual void Exec() = 0;
        virtual bool IsDone() = 0;
        virtual void Shutdown() = 0;
        virtual ~Application();
    protected:
        Configuration* m_pConfiguration;
    };
}
#endif	/* APP_APPLICATION_H */

