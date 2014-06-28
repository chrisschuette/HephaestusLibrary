/* 
 * File:   ConstructionContext.cpp
 * Author: chris
 * 
 * Created on May 20, 2014, 9:07 PM
 */

#include "ConstructionContext.h"

namespace LVL {
ConstructionContext::ConstructionContext(LevelID id)
: STATE::ConstructionContext()
, m_ID(id)
{
}

ConstructionContext::~ConstructionContext() {
}
}
