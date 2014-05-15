/* 
 * File:   GUI.cpp
 * Author: chris
 * 
 * Created on February 2, 2014, 7:17 PM
 */

#include "GUI.h"
#include "Context.h"
#include "Renderer.h"
#include "Theme.h"
#include "Component.h"
#include "../ERR/ERR.h"

namespace GUI {

    GUI::GUI(Theme* theme, EVENT::EventManager* eventManager)
    : Container()
    , m_theme(theme)
    , m_eventMgr(eventManager) {
    }

    GUI::~GUI() {
        if (m_theme)
            delete m_theme;
        if (m_eventMgr)
            delete m_eventMgr;
    }

    void GUI::update() {
        //ensure validity of the Container!
        if (!isValid()) {
            validate();
        }
    }

    void GUI::render(VIEW::Context& context) const {
        Context& ctx = static_cast<Context&> (context);
        Renderer& renderer = ctx.getRenderer();
        Container::render(context);
    }

    void GUI::addComponent(Component * pChild, Context& ctx) {
        Component* c = static_cast<Component*> (pChild);
        if (c && m_theme) {
            c->initView(m_theme, ctx);
        }
        VIEW::View::addChild(pChild);

        // events
        if (m_eventMgr) {
            typedef std::list<VIEW::Element*> tElementList;
            tElementList elements;
            pChild->addToList(elements);
            for (tElementList::iterator i = elements.begin(),
                    e = elements.end(); i != e; ++i)
                m_eventMgr->addEventListener(static_cast<Component*> (*i));
            m_eventMgr->showInfo();
        }

    }

    void GUI::addChild(VIEW::Element * pChild) {
        THROWS("Use void GUI::addComponent(Component * const pChild, Context& ctx) to add Components to the GUI");
    }

    void GUI::removeChild(VIEW::Element * pChild) {
        THROWS("NOT IMPLEMENTED.");
    }

    void GUI::removeAllChildren() {
        THROWS("NOT IMPLEMENTED.");
    }

    EVENT::EventManager& GUI::getEventManager() {
        if (m_eventMgr)
            return *m_eventMgr;
        else
            THROWS("No EventManager available.");
    }



}
