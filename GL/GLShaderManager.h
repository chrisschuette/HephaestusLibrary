/* 
 * File:   GLShaderManager.h
 * Author: chris
 *
 * Created on February 10, 2014, 6:01 PM
 */

#ifndef GLSHADERMANAGER_H
#define	GLSHADERMANAGER_H

#include "../REND/ShaderManager.h"
#include "../LOG/Source.h"

namespace GL {

    class GLShaderManager : public REND::ShaderManager, public LOG::Source {
    public:
        GLShaderManager();
        virtual ~GLShaderManager();
        bool addShaderPairFromFile(std::string name, std::string vertexShaderFile, std::string fragmentShaderFile);
        virtual void showInfo();
    private:

    };
}
#endif	/* GLSHADERMANAGER_H */

