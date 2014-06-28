/* 
 * File:   GLShaderManager.h
 * Author: chris
 *
 * Created on February 10, 2014, 6:01 PM
 */

#ifndef GLSHADERMANAGER_H
#define	GLSHADERMANAGER_H

#include "../REND/ShaderManager.h"
#include <list>

namespace GL {
    class GLShaderProgram;
    class GLShaderManager : public REND::ShaderManager {
    public:
        GLShaderManager();
        virtual ~GLShaderManager();
        GLShaderProgram& addShaderPairFromFile(std::string name, std::string vertexShaderFile, std::string fragmentShaderFile);
        virtual void showInfo();
    private:

    };
}
#endif	/* GLSHADERMANAGER_H */

