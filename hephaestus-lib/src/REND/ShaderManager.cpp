/* 
 * File:   ShaderManager.cpp
 * Author: chris
 * 
 * Created on February 10, 2014, 5:48 PM
 */

#include "ShaderProgram.h"
#include "ShaderManager.h"

namespace REND {

    ShaderManager::ShaderManager() : m_referencePool(ShaderManager_CONST::MAX_RESOURCE_REFERENCES) {
    }

    ShaderManager::~ShaderManager() {
        //delete all shaders in the map
        for (tShaderMap::iterator i = m_shaderMap.begin(), e = m_shaderMap.end();
                i != e; ++i)
            delete (*i).second;
    }

        /*
        const ShaderProgram* ShaderManager::getShaderProgram(std::string name) {
            int N = m_shaderMap.size();
            tShaderMap::const_iterator i = m_shaderMap.find(name);
            if (i != m_shaderMap.end())
                return (*i).second;
            else
                return 0;
        }
     */
    REND::ShaderProgramInstance ShaderManager::getShaderProgramInstance(std::string name) {
        int N = m_shaderMap.size();
        tShaderMap::const_iterator i = m_shaderMap.find(name);
        if (i != m_shaderMap.end())
            return (*i).second->getHandle();
        else
            return SYS::Handle<ShaderProgram> (0, m_referencePool);
    }

    bool ShaderManager::addShaderProgram(ShaderProgram* shaderProgram) {
        if (shaderProgram) {
            std::string name = shaderProgram->getProgramName();
            std::pair < tShaderMap::iterator, bool> result = m_shaderMap.insert(std::pair<std::string, ShaderProgram*>(name, shaderProgram));
            return result.second;
        }
        return false;
    }

    void ShaderManager::deleteShaderProgram(std::string name) {
        tShaderMap::iterator i = m_shaderMap.find(name);
        if (i != m_shaderMap.end()) {
            delete (*i).second;
            m_shaderMap.erase(i);
        }
    }


}
