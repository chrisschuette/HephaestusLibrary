/* 
 * File:   Level.h
 * Author: chris
 *
 * Created on May 20, 2014, 9:01 PM
 */

#ifndef LVLLEVEL_H
#define	LVLLEVEL_H

#include "LevelID.h"
#include "RENDER.h"
#include "UPDATE.h"
#include "Entity.h"
#include "../REND/Camera.h"
#include "EntityManager.h"
#include "../CMPN/Container.h"
#include "IEntityManager.h"
#include "../LOG/Core.h"

#include <list>
#include <set>

namespace CMPN {
    class ComponentManager;
}

namespace PHYSICS {
    class System;
}

namespace REND {
    class Renderer;
}

namespace LVL {
    class Context;
    class Layer;

    class Level : public CMPN::Container {
    public:
        Level(LVL::LevelID id, Context&);
        virtual ~Level();
        
        virtual void init(LVL::Context& ctx);

        virtual void render(REND::Renderer& renderer);
        virtual void renderLayers(REND::Renderer& renderer);
        virtual void renderEntities(REND::Renderer& renderer);
        virtual void update(unsigned long int time, unsigned long int diff);

        void setPhysicsSystem(PHYSICS::System* world);

        template <class T>
        void createEntityManager() {
            addComponent<T>();
            m_entityManager = getComponent<IEntityManager>();
            if(m_entityManager)
                m_entityManager->setLevel(this);
        }

        //entities
        void addEntity(Entity* entity);
        void removeEntity(Entity* entity);

        //layers

        void addLayer(Layer* layer) {
            m_layers.push_back(layer);
        }

        // getters & setters

        void setCamera(REND::Camera* camera) {
            m_camera = camera;
        }

        REND::Camera* getCamera() {
            return m_camera;
        }

        // scrolling

        void scroll(float dx, float dy) {
            m_camera->translateLocal(dx, dy, 0);
        }

        void onResize(int width, int height);
        
        PHYSICS::System* getPhysicsWorld() {
            return m_world;
        }
    protected:
        LevelID m_ID;
        Context& m_ctx;

        REND::Camera* m_camera;
        std::set<Entity*> m_entities;
        std::list<Layer*> m_layers;

        PHYSICS::System* m_world;
        CMPN::ComponentManager& m_cmpnMgr;

        LVL::IEntityManager* m_entityManager;
    };
}
#endif	/* LVLLEVEL_H */

