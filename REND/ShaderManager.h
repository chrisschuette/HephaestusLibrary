/* 
 * File:   ShaderManager.h
 * Author: chris
 *
 * Created on February 10, 2014, 5:48 PM
 */

#ifndef SHADERMANAGER_H
#define	SHADERMANAGER_H

#include <string>
#include <map>

namespace REND {
    class ShaderProgram;
    class ShaderManager {
    public:
        ShaderManager();
        virtual ~ShaderManager();
        
        const ShaderProgram* getShaderProgram(std::string name);
        bool addShaderProgram(ShaderProgram* shaderProgram);
        void deleteShaderProgram(std::string name);
        virtual void showInfo() = 0;
    protected:
        typedef std::map<std::string, ShaderProgram*> tShaderMap;
        tShaderMap m_shaderMap;
    };
}
#endif	/* SHADERMANAGER_H */

