/*
 * File:   Body.cpp
 * Author: chris
 *
 * Created on May 21, 2014, 7:45 PM
 */

#include "Body.h"
#include "System.h"
#include "BodyPartDescription.h"
#include "../BodyPartUserData.h"
#include <Box2D/Common/b2Math.h>
#include "../../LOG/Core.h"

#include <iostream>

#define NAME "Body"

namespace PHYSICS {
    namespace BOX2D {

        Body::Body(b2Body* body, PHYSICS::System& world)
        : PHYSICS::Body(world)
        , m_body(body) {
            m_body->SetUserData(this);
        }

        Body::~Body() {
            for (b2Fixture* f = m_body->GetFixtureList(); f; f = f->GetNext()) {
                BodyPartUserData* userData = static_cast<BodyPartUserData*>(f->GetUserData());
                if(userData)
                    delete userData;
                f->SetUserData(0);                
            }
            PHYSICS::BOX2D::System& box2dsystem = static_cast<PHYSICS::BOX2D::System&> (m_world);
            // remove body from the world
            box2dsystem.destroyBody(this);
        }

        void Body::createBodyPart(const PHYSICS::BodyPartDescription& description) {
            const BodyPartDescription& desc = static_cast<const BodyPartDescription&> (description);
            b2Fixture* fixture = m_body->CreateFixture(desc.getBox2DDescription());
            fixture->SetFriction(0.01);
        }

        std::list<MATH::vec4> Body::getBoundingBox() const {
            std::list<MATH::vec4> boundingBoxes;
            for (b2Fixture* f = m_body->GetFixtureList(); f; f = f->GetNext()) {
                if (f->GetType() == b2Shape::e_polygon) {
                    b2PolygonShape* polygonShape = (b2PolygonShape*) f->GetShape();
                    MATH::vec4 boundingBox;
                    float maxX, maxY, minX, minY;
                    minX = polygonShape->m_vertices[0].x;
                    maxX = polygonShape->m_vertices[0].x;
                    minY = polygonShape->m_vertices[0].y;
                    maxY = polygonShape->m_vertices[0].y;
                    for (int i = 0; i < polygonShape->GetVertexCount(); i++) {
                        minX = std::min(minX, polygonShape->m_vertices[i].x);
                        minY = std::min(minY, polygonShape->m_vertices[i].y);
                        maxX = std::max(maxX, polygonShape->m_vertices[i].x);
                        maxY = std::max(maxY, polygonShape->m_vertices[i].y);
                    }
                    boundingBox.data[0] = minX;
                    boundingBox.data[1] = minY;
                    boundingBox.data[2] = maxX;
                    boundingBox.data[3] = maxY;
                    boundingBoxes.push_back(boundingBox);
                }
            }
            return boundingBoxes;
        }

        void Body::applyLinearImpulse(const MATH::vec2& F) {
            if (m_body)
                m_body->ApplyLinearImpulse(reinterpret_cast<const b2Vec2&> (F), m_body->GetWorldCenter(), true);
        }

        void Body::applyLinearImpulse(float px, float py) {
            MATH::vec2 p;
            p.x = px;
            p.y = py;
            if (m_body)
                m_body->ApplyLinearImpulse(reinterpret_cast<const b2Vec2&> (p), m_body->GetWorldCenter(), true);
        }

        void Body::applyForce(float fx, float fy) {
            MATH::vec2 f;
            f.x = fx;
            f.y = fy;
            if (m_body)
                m_body->ApplyForceToCenter(reinterpret_cast<const b2Vec2&> (f), true);
        }

        void Body::applyAngularMomentum(float f) {
            m_body->ApplyAngularImpulse(f, true);
        }

        const MATH::vec2& Body::getPosition() const {
            return reinterpret_cast<const MATH::vec2&> (m_body->GetPosition());
        }

        float Body::getOrientation() const {
            return m_body->GetAngle();
        }

        const MATH::vec2& Body::getVelocity() const {
            return reinterpret_cast<const MATH::vec2&> (m_body->GetLinearVelocity());
        }

        float Body::getAngularVelocity() const {
            return m_body->GetAngularVelocity();
        }

        float Body::getMass() const {
            return m_body->GetMass();
        }

        float Body::getMomentOfInertia() const {
            return m_body->GetInertia();
        }

        std::list< std::pair< int, MATH::vec2* > > Body::getBodyPartShapes() const {
            std::list< std::pair< int, MATH::vec2* > > shapes;
            // iterate over fixtures
            for (b2Fixture* f = m_body->GetFixtureList(); f; f = f->GetNext()) {
                b2Shape::Type shapeType = f->GetType();
                if (shapeType == b2Shape::e_polygon) {
                    b2PolygonShape* polygonShape = (b2PolygonShape*) f->GetShape();
                    std::pair< int, MATH::vec2* > shape;
                    shape.first = polygonShape->GetVertexCount();
                    shape.second = new MATH::vec2[shape.first];
                    for (int n = 0; n < polygonShape->GetVertexCount(); n++) {
                        const b2Vec2& v = polygonShape->GetVertex(n);
                        shape.second[n].x = v.x;
                        shape.second[n].y = v.y;
                    }
                    shapes.push_back(shape);
                }
            }
            return shapes;
        }

        std::list<GEOMETRY::Polygon> Body::getBodyPartPolygons() const {
            std::list<GEOMETRY::Polygon> polygons;
            // iterate over fixtures
            for (b2Fixture* f = m_body->GetFixtureList(); f; f = f->GetNext()) {
                b2Shape::Type shapeType = f->GetType();
                if (shapeType == b2Shape::e_polygon) {
                    b2PolygonShape* polygonShape = (b2PolygonShape*) f->GetShape();
                    GEOMETRY::Polygon polygon;
                    MATH::vec2 vertex;
                    for (int n = 0; n < polygonShape->GetVertexCount(); n++) {
                        const b2Vec2& v = polygonShape->GetVertex(n);
                        vertex.x = v.x;
                        vertex.y = v.y;
                        polygon.addVertex(vertex);
                    }
                    polygons.push_back(polygon);
                }
            }
            return polygons;
        }


    }
}
