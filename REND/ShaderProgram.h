/* 
 * File:   ShaderProgram.h
 * Author: chris
 *
 * Created on February 10, 2014, 5:46 PM
 */

#ifndef SHADERPROGRAM_H
#define	SHADERPROGRAM_H

#include <string>

namespace REND {

    class ShaderProgram {
    public:
        ShaderProgram(std::string name);
        virtual ~ShaderProgram();
        
        virtual void activate() const = 0;
        const std::string& getProgramName() const { return m_name; }
    private:
        std::string m_name;
    };
}
#endif	/* SHADERPROGRAM_H */

