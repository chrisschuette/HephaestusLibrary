/* 
 * File:   UniformSetting.h
 * Author: chris
 *
 * Created on June 1, 2014, 7:03 PM
 */

#ifndef UNIFORMSETTING_H
#define	UNIFORMSETTING_H


namespace REND {
    class Uniform;
    class UniformSetting {
    public:
        UniformSetting(const Uniform& uniform);
        virtual ~UniformSetting();
        
        const Uniform& getUniform() const { return m_uniform; }
        
        virtual void* getRawData() = 0;
        
        virtual void set() const = 0;
        virtual void set(const void* data) const = 0;
    protected:
        const Uniform& m_uniform;
    };
}
#endif	/* UNIFORMSETTING_H */

