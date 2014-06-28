/* 
 * File:   Context.h
 * Author: chris
 *
 * Created on May 20, 2014, 11:03 PM
 */

#ifndef LVLCONTEXT_H
#define	LVLCONTEXT_H

#include "../CMPN/Context.h"

namespace REND {
    class ShaderManager;
    class SpriteManager;
    class TextureManager;
    namespace SHAPES {
        class GeometryManager;
    }
}

namespace FSVR {
    class FileServer;
}

namespace PHYSICS {
    class System;
}

namespace SND {
    class SoundManager;
}

namespace LVL {
    class Level;

    class Context : public CMPN::Context {
    public:
        Context();
        virtual ~Context();

        virtual REND::SpriteManager& getSpriteManager() = 0;
        virtual REND::ShaderManager& getShaderManager() = 0;
        virtual REND::TextureManager& getTextureManager() = 0;
        virtual REND::SHAPES::GeometryManager& getGeometryManager() = 0;
        virtual FSVR::FileServer& getFileServer() = 0;
        virtual PHYSICS::System* getPhysicsWorld() = 0;
        virtual SND::SoundManager& getSoundManager() = 0;
        virtual int GetWindowHeight() const = 0;
        virtual int GetWindowWidth() const = 0;
        //virtual LVL::Level& getLevel() = 0;
    private:

    };
}
#endif	/* LVLCONTEXT_H */

