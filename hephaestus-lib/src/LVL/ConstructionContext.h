/* 
 * File:   ConstructionContext.h
 * Author: chris
 *
 * Created on May 20, 2014, 9:07 PM
 */

#ifndef LVLCONSTRUCTIONCONTEXT_H
#define	LVLCONSTRUCTIONCONTEXT_H

#include "../STATE/ConstructionContext.h"
#include "LevelID.h"
#include "../MATH/vec234.h"

namespace LVL {
class ConstructionContext: public STATE::ConstructionContext {
public:
    ConstructionContext(LevelID id);
    virtual ~ConstructionContext();
    
    void setWindowDimensions(int width, int height) {
        m_windowDimensions.x = width;
        m_windowDimensions.y = height;
    }
    
    const MATH::ivec2& getWindowDimensions() const { return m_windowDimensions; }
    
    LevelID getLevelID() const { return m_ID; }
private:
    LevelID m_ID;
    MATH::ivec2 m_windowDimensions;
};
}
#endif	/* LVLCONSTRUCTIONCONTEXT_H */

