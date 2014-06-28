/* 
 * File:   ShaderProgramInstance.h
 * Author: chris
 *
 * Created on June 2, 2014, 12:30 AM
 */

#ifndef SHADERPROGRAMINSTANCE_H
#define	SHADERPROGRAMINSTANCE_H

#include "../SYS/Handle.h"
#include "ShaderProgram.h"

namespace REND {
    class UniformSetting;
    class ShaderProgram;

    class ShaderProgramInstance: public SYS::Handle<REND::ShaderProgram> {
    public:
        ShaderProgramInstance(const SYS::Handle<REND::ShaderProgram>& handle);
        virtual ~ShaderProgramInstance();
        
        UniformSetting* createUniformSetting(std::string name, bool allocate) const;
    private:
    };
}
#endif	/* SHADERPROGRAMINSTANCE_H */

