/* 
 * File:   UniformDescription.h
 * Author: chris
 *
 * Created on June 1, 2014, 7:37 PM
 */

#ifndef UNIFORMDESCRIPTION_H
#define	UNIFORMDESCRIPTION_H

#include <string>

namespace GL {

    template <int N, typename T, char S>
    class UniformDescription {
    public:
        UniformDescription(std::string name) : m_name(name) {}
        virtual ~UniformDescription() {}
        const std::string& getName() const { return m_name; }
    private:
        std::string m_name;
    };
}
#endif	/* UNIFORMDESCRIPTION_H */

