/* 
 * File:   main.cpp
 * Author: chris
 *
 * Created on June 9, 2013, 7:23 PM
 */

#include "Application.h"

#include "LOG/ConsoleSink.h"
#include "LOG/FileSink.h"
#include "LOG/LogIOSink.h"

#include "REND/FONTS/FontDescription.h"
#include "UTIL/hash.h"
#include <IL/il.h>

/*
#include "CMPN/example/Test.h"
#include "CMPN/example/Test2.h"
#include "CMPN/example/TestMessage.h"
#include "CMPN/Container.h"
*/
std::string getName() {
    return "main";
}

int main(int, char*[]) {
  
    
/*    Example example;
    return 0;
    // 1
    CMPN::Container container(CMPN::Container::REJECT);
    container.addComponent<Test>();
    
    //2
    CMPN::Container container2(CMPN::Container::REJECT);
    container2.addComponent<Test2>();
    TestMessage msg;
    container.sendMessage<ITest>(container2.getObjectID(), msg);
    
    CMPN::ComponentManager::getInstance().broadcastMessage(msg);
    CMPN::ComponentManager::getInstance().sendMessage(CMPN::Implements<ITest>::getInterfaceTypeID(), container2.getObjectID(), msg);
    
    return 0;
    */
    // add 2 sinks
    LOG::Core::getInstance().addSink(new LOG::ConsoleSink());
    LOG::Core::getInstance().addSink(new LOG::FileSink("log.txt"));
      
    // Log.IO forwards all output to the Javascript logging
    // framework of the same name.
    LOG::Core::getInstance().addSink(new LOG::LogIOSink());
    
    // initialize DevIL
    ilInit();

    Application app;
    app.LoadConfiguration("config.txt");
    app.Init();
    app.Exec();
    app.Shutdown();
    
    return 0;
}
