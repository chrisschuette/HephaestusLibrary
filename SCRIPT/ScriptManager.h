/* 
 * File:   ScriptManager.h
 * Author: chris
 *
 * Created on September 2, 2013, 11:35 AM
 */

#ifndef SCRIPTMANAGER_H
#define	SCRIPTMANAGER_H

namespace SCRIPT {
    class ScriptManager {
    public:
        static ScriptManager& getInstance() { return m_scriptManager; }
    private:
        ScriptManager();
        virtual ~ScriptManager();
        static ScriptManager m_scriptManager;
    };
}

#endif	/* SCRIPTMANAGER_H */

