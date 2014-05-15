/* 
 * File:   ExportToLua.h
 * Author: chris
 *
 * Created on September 2, 2013, 11:17 AM
 */

#ifndef EXPORTTOLUA_H
#define	EXPORTTOLUA_H

#include "ScriptManager.h"

namespace SCRIPT {
    template <class T>
    class ExportToLua {
        public:
            ExportToLua() { (void)&m_registered; }
            ~ExportToLua() {}
            static const int& isRegistered() { return m_registered; }
        protected:
            static int m_registered;
    };
    template <class T> int ExportToLua<T>::m_registered = T::exportToLua();
}

#endif	/* EXPORTTOLUA_H */

