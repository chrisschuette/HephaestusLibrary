/* 
 * File:   main.cpp
 * Author: chris
 *
 * Created on June 9, 2013, 7:23 PM
 */

#include "Application.h"

#include "LOG/Core.h"
#include "LOG/ConsoleSink.h"
#include "LOG/FileSink.h"
#include "ERR/ERR.h"

#define NAME "main"

int main(int, char*[]) {
  
  try {
    // add 2 sinks
    LOG::Core::getInstance().addSink(new LOG::ConsoleSink());
    LOG::Core::getInstance().addSink(new LOG::FileSink("log.txt"));
      
    Application app;
    app.LoadConfiguration("config.txt");
    app.Init();
    app.Exec();
    app.Shutdown();
  } catch(ERR::Exception& e) {
    L(error) << e.what();
  }
    return 0;
}
