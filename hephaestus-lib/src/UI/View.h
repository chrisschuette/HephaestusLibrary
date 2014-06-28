/* 
 * File:   View.h
 * Author: chris
 *
 * Created on May 23, 2014, 7:17 PM
 */

#ifndef VIEW_H
#define	VIEW_H

#include "Component.h"
#include "LAYOUT/Layout.h"

#include <list>

namespace UI {
    namespace LAYOUT {
        class Layout;
    }

    class View : public Component {
    public:
        typedef std::list<Component *> tViewList;

    public:
        View(std::string name);
        virtual ~View();

        // component management
        virtual void addComponent(Component* component);

        const tViewList& getChildren() const {
            return m_children;
        }

        tViewList& getChildren() {
            return m_children;
        }

        bool hasChildren() const {
            return m_children.size();
        }

        unsigned int getChildCount() const {
            return m_children.size();
        }

        // render & update
        virtual void render(Context& context) const;

        //validity
        virtual void validate(Context& context);

        // layout
        virtual void resize(int x, int y);

        void setLayout(LAYOUT::Layout* layout) {
            m_layout = layout;
        }

        // other
        virtual void setUI(UI* ui);
        virtual Component* getComponent(const MATH::ivec2& position);

        void setContainerOrigin(int x, int y) {
            m_containerOrigin.x = x;
            m_containerOrigin.y = y;
        }

        int getContainerHOrigin() const {
            return m_containerOrigin.x;
        }

        int getContainerVOrigin() const {
            return m_containerOrigin.y;
        }

        const MATH::ivec2& getContainerDimensions() const {
            return m_containerDimensions;
        }

        void setContainerDimensions(const MATH::ivec2& dimensions) {
            m_containerDimensions = dimensions;
        }

        void setContainerDimensions(int x, int y) {
            m_containerDimensions.x = x;
            m_containerDimensions.y = y;
        }

    protected:
        tViewList m_children;
    private:
        LAYOUT::Layout* m_layout;
        MATH::ivec2 m_containerOrigin;
        MATH::ivec2 m_containerDimensions;
    };
}

#endif	/* VIEW_H */

