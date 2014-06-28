/* 
 * File:   Level.cpp
 * Author: chris
 * 
 * Created on May 20, 2014, 9:01 PM
 */

#include "Level.h"
#include "Context.h"
#include "Layer.h"

#include "Entity.h"
#include "UPDATE.h"
#include "../ERR/ERR.h"

#include "../GL/Renderer.h"

#include "../PHYSICS/System.h"

#define NAME "Level"

namespace LVL {

    Level::Level(LVL::LevelID id, Context& context)
    : CMPN::Container()
    , m_ID(id)
    , m_ctx(context)
    , m_world(0)
    , m_cmpnMgr(CMPN::ComponentManager::getInstance())
    , m_camera(0)
    , m_entityManager(0) {

    }

    Level::~Level() {
        // destroy all entities
        for (std::set<Entity*>::iterator i = m_entities.begin(),
                e = m_entities.end(); i != e; ++i)
            delete (*i);

        // destroy all layers
        for (std::list<Layer*>::iterator i = m_layers.begin(),
                e = m_layers.end(); i != e; ++i)
            delete (*i);

        // destroy the physical world
        if (m_world)
            delete m_world;

        if (m_camera)
            delete m_camera;
    }

    void Level::init(LVL::Context& ctx) {
        // initialize components
        CMPN::ComponentManager::getInstance().initAllComponents(ctx);

    }

    void Level::onResize(int width, int height) {
        if (m_world)
            m_world->onResize(((float) width) / m_world->getScalingFactor(), ((float) (height)) / m_world->getScalingFactor());
    }

    void Level::render(REND::Renderer& renderer) {

        renderLayers(renderer);

        renderEntities(renderer);
    }
    
    void Level::renderLayers(REND::Renderer& renderer) {
        //draw layers
        for (std::list<Layer*>::iterator i = m_layers.begin(),
                e = m_layers.end(); i != e; ++i) {
            renderer.PushMatrix();
            if (m_camera)
                renderer.Translate(-m_camera->getPosition().x * (*i)->getScrollFactorX(), -m_camera->getPosition().y * (*i)->getScrollFactorY(), 0);
            (*i)->render(renderer, m_ctx);
            renderer.PopMatrix();
        }
    }

    void Level::renderEntities(REND::Renderer& renderer) {
        // draw the entities
        renderer.PushMatrix();
        if (m_camera)
            renderer.Translate(-m_camera->getPosition().x, -m_camera->getPosition().y, 0);
        m_cmpnMgr.broadcastMessage(LVL::RENDER(renderer, m_ctx));
        renderer.PopMatrix();
    }

    void Level::update(unsigned long int time, unsigned long int diff) {

        // update layers
        for (std::list<Layer*>::iterator i = m_layers.begin(),
                e = m_layers.end(); i != e; ++i)
            (*i)->update(time, diff);

        // update physics world
        if (m_world)
            m_world->update();

        // only then process the collisions
        if (m_world)
            m_world->processCollisions();

        // add and remove entities
        if (m_entityManager)
            m_entityManager->update(time, diff);

        // update the entities
        m_cmpnMgr.broadcastMessage(LVL::UPDATE(time, diff, *this));

        //        m_cmpnMgr.showInfo();

    }

    void Level::setPhysicsSystem(PHYSICS::System* world) {
        if (m_world)
            delete m_world;
        m_world = world;
    }

    void Level::addEntity(Entity* entity) {
        std::pair < std::set<Entity*>::iterator, bool> ret = m_entities.insert(entity);
        if (!ret.second)
            THROWS("Insert of entity into set failed.");
    }

    void Level::removeEntity(Entity* entity) {
        if (entity) {
            if (m_entities.erase(entity) == 1)
                delete entity;
            else
                L(error) << "Removal of entity from set failed.";
        }
    }

}
