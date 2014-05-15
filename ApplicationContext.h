/* 
 * File:   Context.h
 * Author: chris
 *
 * Created on February 11, 2014, 10:24 PM
 */

#ifndef APPLICATIONCONTEXT_H
#define	APPLICATIONCONTEXT_H

#include "STATE/Context.h"
#include "APP/Clock.h"

namespace APP {
    class Clock;
}

namespace STATE {
    class StateManager;
}

namespace LOC {
    class LangDict;
}

namespace SND {
    class SoundManager;
}

namespace REND {
    class TextureManager;
    namespace FONTS {
        class FontManager;
    }
}

namespace REND {
    class ShaderManager;
}

namespace FSVR {
    class FileServer;
}

class ApplicationContext: public STATE::Context {
public:
    ApplicationContext();
    virtual ~ApplicationContext();
    virtual REND::ShaderManager& getShaderManager() = 0;
    virtual REND::FONTS::FontManager& getFontManager() = 0;
    virtual LOC::LangDict& getLocalisation() = 0;
    virtual SND::SoundManager& getSoundManager() = 0;
    virtual FSVR::FileServer& getFileServer() = 0;
    virtual STATE::StateManager& getStateManager() = 0;
    virtual REND::TextureManager& getTextureManager() = 0;
private:

};

#endif	/* APPLICATIONCONTEXT_H */

