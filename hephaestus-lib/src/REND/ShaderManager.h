/* 
 * File:   ShaderManager.h
 * Author: chris
 *
 * Created on February 10, 2014, 5:48 PM
 */

#ifndef SHADERMANAGER_H
#define	SHADERMANAGER_H

#include "../SYS/Handle.h"
#include "ShaderProgram.h"
#include "ShaderProgramInstance.h"

#include <string>
#include <map>

namespace REND {
        namespace ShaderManager_CONST {
        const int MAX_RESOURCE_REFERENCES = 200;
    }
    class ShaderManager {
    public:
        ShaderManager();
        virtual ~ShaderManager();
        
        //const ShaderProgram* getShaderProgram(std::string name);
        
        REND::ShaderProgramInstance getShaderProgramInstance(std::string name);
        
        bool addShaderProgram(ShaderProgram* shaderProgram);
        void deleteShaderProgram(std::string name);
        virtual void showInfo() = 0;
    protected:
        typedef std::map<std::string, ShaderProgram*> tShaderMap;
        tShaderMap m_shaderMap;
        MEM::Pool< SYS::Reference<ShaderProgram> > m_referencePool;
    };
}
#endif	/* SHADERMANAGER_H */

