/* 
 * File:   Horizontal.cpp
 * Author: chris
 * 
 * Created on February 9, 2014, 4:58 PM
 */

#include "Horizontal.h"
#include "../View.h"
#include "../Component.h"
#include <iostream>
#include <iterator>     // std::distance

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

    struct HorizontalArranger {

        HorizontalArranger(int& currentY, /*GEOMETRY::Vec2<int> containerDimensions, */int wspc)
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

        Horizontal::Horizontal() : Layout("Horizontal") {
            ////std::cout << "Horizontal::Horizontal()" << std::endl;
        }

        Horizontal::~Horizontal() {
            ////std::cout << "Horizontal::~Horizontal()" << std::endl;
        }

        void Horizontal::layoutOverflow(View& view, Context& context) {
            // do the best you can
            ////std::cout << "Layouing out overflowing view." << std::endl;
        }

        void Horizontal::layout(View& view, Context& context) {
            int N = view.getChildCount();
            int W = view.getContainerDimensions().x;
            int H = view.getContainerDimensions().y;
            //std::cout << "Container: " << N << " children and dimensions: " << W << " x " << H << std::endl;
            View::tViewList& components = view.getChildren();

            /*
             * Vertical sizes and positions
             */

            int heights[N];
            int n = 0;
            for (View::tViewList::const_iterator i = components.begin(), e = components.end();
                    i != e; ++i) {
                switch ((*i)->getVerticalBehaviour()) {
                    case Component::EXPAND:
                        if ((*i)->getMaximumHeight() >= 0)
                            heights[n] = std::min((*i)->getMaximumHeight(), H);
                        else
                            heights[n] = H;

                        if ((*i)->getMinimumHeight() >= 0)
                            heights[n] = std::max(heights[n], (*i)->getMinimumHeight());

                        (*i)->setPositionY(H / 2 - heights[n] / 2);
                        break;
                    case Component::COMPACT:
                        heights[n] = (*i)->getMinimumHeight();
                        (*i)->setPositionY(H / 2 - heights[n] / 2);
                        break;
                    case Component::FIXED:
                        heights[n] = (*i)->getHeight();
                        (*i)->setPositionY(H / 2 - heights[n] / 2);
                        break;
                }
                n++;
            }

            /*
             * Is there in principle enough space to layout the components?
             */
            int minRequiredWidth = 0;
            for (View::tViewList::const_iterator i = components.begin(), e = components.end();
                    i != e; ++i) {
                int minWidth;
                switch ((*i)->getHorizontalBehaviour()) {
                    case Component::EXPAND:
                        minWidth = (*i)->getMinimumWidth();
                        break;
                    case Component::COMPACT:
                        minWidth = (*i)->getMinimumWidth();
                        break;
                    case Component::FIXED:
                        minWidth = (*i)->getWidth();
                        break;
                }
                minRequiredWidth += minWidth;
            }
            //std::cout << "Minimum required space: " << minRequiredWidth << std::endl;

            if (minRequiredWidth > W) {// to small for content
                layoutOverflow(view, context);
                return;
            }

            /*
             * If everyone gets what he wants is there whitespace left?
             */

            // fixed widths
            int widths[N];
            int totalWidthFixedComponents = 0;
            int numberOfExpandingComponents = 0;
            int numberOfExpandingComponentsWithoutBound = 0;
            n = 0;
            for (View::tViewList::const_iterator i = components.begin(), e = components.end();
                    i != e; ++i) {
                switch ((*i)->getHorizontalBehaviour()) {
                    case Component::EXPAND:
                        widths[n] = -1;
                        numberOfExpandingComponents++;
                        if ((*i)->getMaximumWidth() < 0)
                            numberOfExpandingComponentsWithoutBound++;
                        break;
                    case Component::COMPACT:
                        widths[n] = (*i)->getMinimumWidth();
                        totalWidthFixedComponents += widths[n];

                        break;
                    case Component::FIXED:
                        widths[n] = (*i)->getWidth();
                        totalWidthFixedComponents += widths[n];

                        break;
                }
                n++;
            }

            int spaceForExpandingComponents = W - totalWidthFixedComponents;
            //std::cout << "spaceForExpandingComponents: " << spaceForExpandingComponents << std::endl;
            //std::cout << "numberOfExpandingComponents: " << numberOfExpandingComponents << std::endl;
            //std::cout << "numberOfExpandingComponentsWithoutBound: " << numberOfExpandingComponentsWithoutBound << std::endl;

            // calculate white space
            int widthOfExpandingComponents = 0;
            for (View::tViewList::iterator i = components.begin(), e = components.end();
                    i != e; ++i) {
                n = std::distance(components.begin(), i);

                switch ((*i)->getHorizontalBehaviour()) {
                    case Component::EXPAND:
                        if ((*i)->getMaximumWidth() >= 0)
                            widthOfExpandingComponents += (*i)->getMaximumWidth();
                        else
                            widthOfExpandingComponents += W;
                        break;
                }
            }


            //std::cout << "widthOfExpandingComponents: " << widthOfExpandingComponents << std::endl;

            int totalWhiteSpace = std::max(spaceForExpandingComponents - widthOfExpandingComponents, (int) 0);
            //std::cout << "totalWhiteSpace: " << totalWhiteSpace << std::endl;
            int whiteSpace = totalWhiteSpace / (N + 1);
            //std::cout << "whiteSpace: " << whiteSpace << std::endl;

            spaceForExpandingComponents -= totalWhiteSpace;
            int spaceLeft = spaceForExpandingComponents;
            //std::cout << "spaceForExpandingComponents: " << spaceForExpandingComponents << std::endl;

            // first those which have a minimum size
            int done = 0;
            for (View::tViewList::iterator i = components.begin(), e = components.end();
                    i != e; ++i) {
                n = std::distance(components.begin(), i);
                switch ((*i)->getHorizontalBehaviour()) {
                    case Component::EXPAND:
                        if (((*i)->getMaximumWidth() >= 0) && ((*i)->getMinimumWidth() > 0)) {
                            widths[n] = std::max(std::min((*i)->getMaximumWidth(), spaceForExpandingComponents / numberOfExpandingComponents), (*i)->getMinimumWidth());
                            spaceLeft -= widths[n];
                            done++;
                            //std::cout << widths[n] << std::endl;
                        }
                }
            }
            
                        for (n = 0; n < N; n++) {
                //std::cout << n << ": " << widths[n] << "x" << heights[n] << std::endl;
            }

            int temp = spaceLeft;
            ////std::cout << "spaceLeft: " << spaceLeft << std::endl;

            ////std::cout << "Components with minimum size: " << std::endl;
            for (View::tViewList::iterator i = components.begin(), e = components.end();
                    i != e; ++i) {
                n = std::distance(components.begin(), i);

                switch ((*i)->getHorizontalBehaviour()) {
                    case Component::EXPAND:
                        if (((*i)->getMaximumWidth() >= 0) && ((*i)->getMinimumWidth() <= 0)) {
                            widths[n] = std::min((*i)->getMaximumWidth(), temp / (numberOfExpandingComponents - done));
                            spaceLeft -= widths[n];

                            ////std::cout << widths[n] << std::endl;
                        }
                }
            }
            //std::cout << "space left: " << spaceLeft << std::endl;
            
                        for (n = 0; n < N; n++) {
                //std::cout << n << ": " << widths[n] << "x" << heights[n] << std::endl;
            }

            //std::cout << "Components without minimum size: " << std::endl;
            for (View::tViewList::iterator i = components.begin(), e = components.end();
                    i != e; ++i) {
                n = std::distance(components.begin(), i);

                switch ((*i)->getHorizontalBehaviour()) {
                    case Component::EXPAND:
                        if ((*i)->getMaximumWidth() < 0) {
                            widths[n] = std::max(spaceLeft / numberOfExpandingComponentsWithoutBound, (*i)->getMinimumWidth());
                        }
                }
            }
            
                        for (n = 0; n < N; n++) {
                //std::cout << n << ": " << widths[n] << "x" << heights[n] << std::endl;
            }
            //std::cout << "space left: " << spaceLeft << std::endl;

            for (n = 0; n < N; n++) {
                //std::cout << n << ": " << widths[n] << "x" << heights[n] << std::endl;
            }

            // assign positions and widths
            n = 0;
            int xPosition = whiteSpace;
            for (View::tViewList::const_iterator i = components.begin(), e = components.end();
                    i != e; ++i) {
                (*i)->setPositionX(xPosition);
                xPosition += widths[n] + whiteSpace;
                //(*i)->init(context, false);
                (*i)->resize(widths[n], heights[n]);
                n++;
            }

            ////std::cout << "OVERSHOOT: " << W - xPosition << std::endl;


        }

    }
}
