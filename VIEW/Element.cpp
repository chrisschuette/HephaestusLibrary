/* 
 * File:   Component.cpp
 * Author: chris
 * 
 * Created on February 2, 2014, 5:56 PM
 */

#include "Element.h"
#include "View.h"

namespace VIEW {
Element::Element()
: m_pParent(0)
, m_visible(true)
, m_valid(false)
, m_selectable(true)
{
}

Element::Element(const Element& orig)
: m_pParent(0)
, m_visible(orig.m_visible)
, m_valid(orig.m_valid)
, m_selectable(orig.m_selectable)
{
}


Element::~Element() {
}

void Element::invalidate() {
    m_valid = false;
    if ((m_pParent != 0) && (m_pParent->isValid()))
        m_pParent->invalidate();
}
}
