/* 
 * File:   Application.cpp
 * Author: chris
 * 
 * Created on October 3, 2011, 12:01 PM
 */

#include "Application.h"
#include "Configuration.h"

using namespace APP;

Application::Application()
: LOG::Source("Application")
, m_pConfiguration(new Configuration) {
}

Application::~Application() {
    delete m_pConfiguration;
}

void Application::LoadConfiguration(std::string Filename) {
    m_pConfiguration->ReadConfigFile(Filename);
    m_pConfiguration->CheckComplete();
}



