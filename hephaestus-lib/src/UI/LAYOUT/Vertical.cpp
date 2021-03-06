/* 
 * File:   Vertical.cpp
 * Author: chris
 * 
 * Created on February 9, 2014, 4:58 PM
 */

#include "Vertical.h"
#include "../View.h"
#include "../Component.h"
#include <iostream>

namespace UI {

    struct TotalHeightCalculator {

        TotalHeightCalculator(int& h) : m_height(h) {
        }

        virtual void operator()(Component * c) {
            //            if (c)
            //                m_height += p->getHeight();
        }
    private:
        int& m_height;
    };

    struct VerticalArranger {

        VerticalArranger(int& currentY, /*GEOMETRY::Vec2<int> containerDimensions, */int wspc)
        : m_currentY(currentY)
        //        , m_containerDimensions(containerDimensions)
        , m_wspc(wspc) {
        }

        virtual void operator()(Component * c) {
            if (c) {
                m_currentY += m_wspc;
                //                int xPos = std::max((m_containerDimensions.x - p->getWidth()) / 2,0);
                //                int yPos = m_currentY;
                //                p->setPosition(GEOMETRY::Vec2<int>(xPos, yPos));
                //                m_currentY += p->getHeight();
            }
        }

    private:
        int& m_currentY;
        //        GEOMETRY::Vec2<int> m_containerDimensions;
        int m_wspc;
    };
    namespace LAYOUT {

        Vertical::Vertical() : Layout("Vertical") {
            //std::cout << "Vertical::Vertical()" << std::endl;
        }

        Vertical::~Vertical() {
            //std::cout << "Vertical::~Vertical()" << std::endl;
        }

        void Vertical::layoutOverflow(View& view, Context& context) {
            // do the best you can
            //std::cout << "Layouing out overflowing view." << std::endl;
        }

        void Vertical::layout(View& view, Context& context) {
            int N = view.getChildCount();
            int W = view.getContainerDimensions().x;
            int H = view.getContainerDimensions().y;
            
           // std::cout << "Container: " << N << " children and dimensions: " << W << " x " << H << std::endl;
            View::tViewList& components = view.getChildren();

            /*
             * Horizontal sizes and positions
             */
            
            int widths[N];
            int n = 0;
            for (View::tViewList::const_iterator i = components.begin(), e = components.end();
                    i != e; ++i) {
                switch ((*i)->getHorizontalBehaviour()) {
                    case Component::EXPAND:
                        if ((*i)->getMaximumWidth() >= 0)
                            widths[n] = std::min((*i)->getMaximumWidth(), W);
                        else
                            widths[n] = W;

                        if ((*i)->getMinimumWidth() >= 0)
                            widths[n] = std::max(widths[n], (*i)->getMinimumWidth());

                        (*i)->setPositionX(W / 2 - widths[n] / 2);
                        break;
                    case Component::COMPACT:
                        widths[n] = (*i)->getMinimumWidth();
                        (*i)->setPositionX(W / 2 - widths[n] / 2);
                        break;
                    case Component::FIXED:
                        widths[n] = (*i)->getWidth();
                        (*i)->setPositionX(W / 2 - widths[n] / 2);
                        break;
                }
                n++;
            }

            /*
             * Is there in principle enough space to layout the components?
             */
            int minRequiredHeight = 0;
            for (View::tViewList::const_iterator i = components.begin(), e = components.end();
                    i != e; ++i)
                switch ((*i)->getVerticalBehaviour()) {
                    case Component::EXPAND:
                        minRequiredHeight += (*i)->getMinimumHeight();
                        break;
                    case Component::COMPACT:
                        minRequiredHeight += (*i)->getMinimumHeight();
                        break;
                    case Component::FIXED:
                        minRequiredHeight += (*i)->getHeight();
                        break;
                }
            //std::cout << "Minimum required space: " << minRequiredHeight << std::endl;

            if (minRequiredHeight > H) {// to small for content
                layoutOverflow(view, context);
                return;
            }

            /*
             * If everyone gets what he wants is there whitespace left?
             */

            // fixed heights
            int heights[N];
            int totalHeightFixedComponents = 0;
            int numberOfExpandingComponents = 0;
            int numberOfExpandingComponentsWithoutBound = 0;
            n = 0;
            for (View::tViewList::const_iterator i = components.begin(), e = components.end();
                    i != e; ++i) {
                switch ((*i)->getVerticalBehaviour()) {
                    case Component::EXPAND:
                        heights[n] = -1;
                        numberOfExpandingComponents++;
                        if ((*i)->getMaximumHeight() < 0)
                            numberOfExpandingComponentsWithoutBound++;
                        break;
                    case Component::COMPACT:
                        heights[n] = (*i)->getMinimumHeight();
                        totalHeightFixedComponents += heights[n];

                        break;
                    case Component::FIXED:
                        heights[n] = (*i)->getHeight();
                        totalHeightFixedComponents += heights[n];

                        break;

                }
                n++;
            }

            int spaceForExpandingComponents = H - totalHeightFixedComponents;
            //std::cout << "spaceForExpandingComponents: " << spaceForExpandingComponents << std::endl;
           // std::cout << "numberOfExpandingComponents: " << numberOfExpandingComponents << std::endl;
           // std::cout << "numberOfExpandingComponentsWithoutBound: " << numberOfExpandingComponentsWithoutBound << std::endl;

            // calculate white space
            int heightOfExpandingComponents = 0;
            for (View::tViewList::const_iterator i = components.begin(), e = components.end();
                    i != e; ++i) {
                switch ((*i)->getVerticalBehaviour()) {
                    case Component::EXPAND:
                        if ((*i)->getMaximumHeight() >= 0) {
                            heightOfExpandingComponents += (*i)->getMaximumHeight();
                        }
                        else
                            heightOfExpandingComponents += H;
                        break;
                }
            }
            
            
            //std::cout << "heightOfExpandingComponents: " << heightOfExpandingComponents << std::endl;

            int totalWhiteSpace = std::max(spaceForExpandingComponents - heightOfExpandingComponents, (int) 0);
            //std::cout << "totalWhiteSpace: " << totalWhiteSpace << std::endl;
            int whiteSpace = totalWhiteSpace / (N + 1);
            //std::cout << "whiteSpace: " << whiteSpace << std::endl;

            spaceForExpandingComponents -= totalWhiteSpace;
            int spaceLeft = spaceForExpandingComponents;
            //std::cout << "spaceForExpandingComponents: " << spaceForExpandingComponents << std::endl;
            //std::cout << "numberOfExpandingComponents: " << numberOfExpandingComponents << std::endl;

            // first those which have a minimum size
            int done = 0;
            n = 0;
            for (View::tViewList::const_iterator i = components.begin(), e = components.end();
                    i != e; ++i) {
                switch ((*i)->getVerticalBehaviour()) {
                    case Component::EXPAND:
                        if (  ( (*i)->getMaximumHeight() >= 0 ) && ( (*i)->getMinimumHeight() > 0)   )  {
                            heights[n] = std::max(std::min((*i)->getMaximumHeight(), spaceForExpandingComponents / numberOfExpandingComponents),(*i)->getMinimumHeight());
                            spaceLeft -= heights[n];
                            done++;
                            //std::cout << heights[n] << std::endl;
                        }
                }
                n++;
            }
            
            int temp = spaceLeft;
            //std::cout << "spaceLeft: " << spaceLeft << std::endl;
            
            //std::cout << "Components with minimum size: " << std::endl;
            n = 0;
            for (View::tViewList::const_iterator i = components.begin(), e = components.end();
                    i != e; ++i) {
                switch ((*i)->getVerticalBehaviour()) {
                    case Component::EXPAND:
                        if (  ( (*i)->getMaximumHeight() >= 0 ) && ( (*i)->getMinimumHeight() <= 0)   )  {
                            heights[n] = std::min((*i)->getMaximumHeight(), temp / (numberOfExpandingComponents-done));
                            spaceLeft -= heights[n];
                            
                            //std::cout << heights[n] << std::endl;
                        }
                }
                n++;
            }
            //std::cout << "space left: " << spaceLeft << std::endl;

            //std::cout << "Components without minimum size: " << std::endl;
            n = 0;
            for (View::tViewList::const_iterator i = components.begin(), e = components.end();
                    i != e; ++i) {
                switch ((*i)->getVerticalBehaviour()) {
                    case Component::EXPAND:
                        if ((*i)->getMaximumHeight() < 0) {
                            heights[n] = std::max(spaceLeft / numberOfExpandingComponentsWithoutBound,(*i)->getMinimumHeight());
                        }
                }
                n++;
            }
            //std::cout << "space left: " << spaceLeft << std::endl;

            for (n = 0; n < N; n++) {
                //std::cout << n << ": " << widths[n] << "x" << heights[n] << std::endl;
            }
            
            // assign positions and heights
            n=0;
            int yPosition = whiteSpace;
            for (View::tViewList::const_iterator i = components.begin(), e = components.end();
                    i != e; ++i) {
                (*i)->setPositionY(yPosition);
                yPosition += heights[n] + whiteSpace;
                //(*i)->init(context, false);
                (*i)->resize(widths[n], heights[n]);
                n++;
            }
            
            //std::cout << "OVERSHOOT: " << H - yPosition << std::endl;
        }

    }
}
