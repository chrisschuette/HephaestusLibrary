/* 
 * File:   Vertical.cpp
 * Author: chris
 * 
 * Created on February 9, 2014, 4:58 PM
 */

#include "Vertical.h"
#include "../Container.h"
#include "../Component.h"
#include <iostream>

namespace GUI {

    struct TotalHeightCalculator : public VIEW::ViewVisitor {

        TotalHeightCalculator(int& h) : m_height(h) {}

        virtual void operator()(VIEW::Element * pComponent) {
            Component* p = static_cast<Component*> (pComponent);
            if (p)
                m_height += p->getHeight();
        }
    private:
        int& m_height;
    };
    
    struct VerticalArranger : public VIEW::ViewVisitor {

        VerticalArranger(int& currentY, GEOMETRY::Vec2<int> containerDimensions, int wspc)
        : m_currentY(currentY)
        , m_containerDimensions(containerDimensions)
        , m_wspc(wspc) {}

        virtual void operator()(VIEW::Element * pComponent) {
            Component* p = static_cast<Component*> (pComponent);
            if(p) {
                m_currentY += m_wspc;
                int xPos = std::max((m_containerDimensions.x - p->getWidth()) / 2,0);
                int yPos = m_currentY;
                p->setPosition(GEOMETRY::Vec2<int>(xPos, yPos));
                m_currentY += p->getHeight();
            }
        }

    private:
        int& m_currentY;
        GEOMETRY::Vec2<int> m_containerDimensions;
        int m_wspc;
    };    
    namespace LAYOUT {

        Vertical::Vertical() : Layout("Vertical") {
        }

        Vertical::~Vertical() {
        }

        void Vertical::layoutContainer(Container& container) {
            int N = container.getChildCount();
            L(normal) << "Laying out container with " << N << " children.";
            int h = container.getHeight();
            int w = container.getWidth();
            L(normal) << "Width: " << w << " Height: " << h ;

            int totalComponentHeight = 0;
            TotalHeightCalculator thc(totalComponentHeight);
            const VIEW::View::tViewList& list = container.getChildren();
            std::for_each(list.begin(), list.end(),thc);
            
            L(normal) << "Total height of components: " << totalComponentHeight;
            
            if(h < totalComponentHeight)
                L(error) << "Overfull box.";
            
            int whiteSpace = h - totalComponentHeight;
            
            int wspc = round((float) whiteSpace / float (N+1));
            
            int currentY = 0;
            VerticalArranger va(currentY, container.getDimensions(), wspc);
            std::for_each(list.begin(), list.end(),va);
            
            for(VIEW::View::tViewList::const_iterator i = list.begin(), e = list.end(); i != e; ++i) {
                Component* c = static_cast<Component*>(*i);
                L(normal) << "x = " << c->getPosition().x << " y = " << c->getPosition().y;
                L(normal) << "w = " << c->getDimensions().x << " h = " << c->getDimensions().y;
            }
        }

    }
}
