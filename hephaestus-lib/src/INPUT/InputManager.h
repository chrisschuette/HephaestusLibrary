/* 
 * File:   InputManager.h
 * Author: chris
 *
 * Created on June 22, 2013, 5:06 PM
 */

#ifndef INPUTMANAGER_H
#define	INPUTMANAGER_H

#include <memory>
#include <list>

namespace INPUT {
    class Input;
    class InputMap;
class InputManager {
public:
    typedef std::list<InputMap*> tInputMapList;
    static InputManager& getInstance();
    void processInput(const Input& input) const;
    void registerInputMap(InputMap* map);
    void removeInputMap(InputMap* map);
private:
    InputManager();
    virtual ~InputManager();
    static std::auto_ptr<InputManager> m_pInstance;
    friend class std::auto_ptr<InputManager>;
    tInputMapList m_inputMaps;
};
}
#endif	/* INPUTMANAGER_H */

