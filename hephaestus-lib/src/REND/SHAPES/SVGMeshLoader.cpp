/* 
 * File:   SVGMeshLoader.cpp
 * Author: chris
 * 
 * Created on May 30, 2014, 6:06 PM
 */

#include "SVGMeshLoader.h"
#include "../../LOG/Core.h"
#include "SVGtoCompound.h"
#include "../../GEOMETRY/Polygon.h"
#include "../../DMGD/Resource.h"
#include "../../FSVR/ResourceMetaData.h"
#include "../../GL/GLVertexBuffer.h"
#include "../../REND/ShaderManager.h"
#include "../../REND/SHAPES/CompoundRenderable.h"
#include "../../REND/SHAPES/Polygon.h"

#include "../../GEOMETRY/Algorithms.h"

#include <vector>

#define NAME "SVGMeshLoader"

namespace REND {
    namespace SHAPES {

        SVGMeshLoader::SVGMeshLoader(REND::ShaderManager& shaderManager) : DMGD::Loader<REND::SHAPES::Mesh>(), m_shaderManager(shaderManager) {
        }

        SVGMeshLoader::~SVGMeshLoader() {
            for (std::list<GEOMETRY::Compound*>::iterator i = m_compoundList.begin(), e = m_compoundList.end(); i != e; ++i)
                delete (*i);
        }

        void SVGMeshLoader::onLoadComplete(FSVR::Resource& resource, const FSVR::ResourceMetaData& metadata) {
            L(normal) << "SVGMeshLoader::onLoadComplete";

            // SVG ==> intermediate representation (Compound / Polygon)
            m_compoundList = parseSVG(getRawData(), getRawDataSize());
            discardRawData();
                       
            
            /*for (std::list<GEOMETRY::Compound*>::iterator i = m_compoundList.begin(), e = m_compoundList.end(); i != e; ++i) {
                MATH::vec2 com = (*i)->calculateCenterOfMass();
                com.x = -com.x;
                com.y = -com.y;
                (*i)->translate(com);
            }*/

            /*
                        // move anchor point to center of mass
                        MATH::vec2 com = m_compoundList->calculateCenterOfMass();
                        com.x = -com.x;
                        com.y = -com.y;
                        m_compound->translate(com);
             */

            // decide about instantiation
            FSVR::Loader::onLoadComplete(resource, metadata);
        }

        GL::GLVertexBuffer* SVGMeshLoader::createBuffer(const GEOMETRY::Compound& compound) {
            std::list< std::vector<GEOMETRY::Triangle> > triangulations;
            const std::list<GEOMETRY::Polygon*>& shapes = compound.getShapes();
            int nTriangles = 0;
            for (std::list<GEOMETRY::Polygon*>::const_iterator i = shapes.begin(), e = shapes.end(); i != e; ++i) {
                triangulations.push_back((*i)->triangulate());
                nTriangles += triangulations.back().size();
            }

            // allocate memory

            typedef struct {
                float x, y, r, g, b, a;
            } vertex_t;
            vertex_t vertices[nTriangles * 3];

            int a = 0;
            std::list<GEOMETRY::Polygon*>::const_iterator iter = compound.getShapes().begin();
            for (std::list< std::vector<GEOMETRY::Triangle> >::const_iterator i = triangulations.begin(), e = triangulations.end(); i != e; ++i) {
                const REND::SHAPES::Polygon* p = static_cast<const REND::SHAPES::Polygon*> (*iter);
                const std::vector<GEOMETRY::Triangle>& triangulation = (*i);
                const MATH::vec4& fillColor = p->getFillColor();

                for (std::vector<GEOMETRY::Triangle>::const_iterator j = triangulation.begin(), f = triangulation.end(); j != f; ++j) {
                    vertices[a].x = (*j).getA().x;
                    vertices[a].y = (*j).getA().y;
                    vertices[a].r = fillColor.r;
                    vertices[a].g = fillColor.g;
                    vertices[a].b = fillColor.b;
                    vertices[a].a = fillColor.a;

                    vertices[a + 1].x = (*j).getB().x;
                    vertices[a + 1].y = (*j).getB().y;
                    vertices[a + 1].r = fillColor.r;
                    vertices[a + 1].g = fillColor.g;
                    vertices[a + 1].b = fillColor.b;
                    vertices[a + 1].a = fillColor.a;

                    vertices[a + 2].x = (*j).getC().x;
                    vertices[a + 2].y = (*j).getC().y;
                    vertices[a + 2].r = fillColor.r;
                    vertices[a + 2].g = fillColor.g;
                    vertices[a + 2].b = fillColor.b;
                    vertices[a + 2].a = fillColor.a;

                    a += 3;
                }
                ++iter;
            }

            // compound contains lots of polygons
            // for each polygon (constant color)
            // triangulate and add to Renderable
            GL::GLVertexBuffer* vb = new GL::GLVertexBuffer("vertex:2f,color:4f");
            vb->push_back_vertices(vertices, nTriangles * 3);
            return vb;
        }

        void SVGMeshLoader::instantiate(FSVR::Resource& resource, const FSVR::ResourceMetaData& metadata) {
            L(normal) << "SVGMeshLoader::instantiate";
            DMGD::Resource<REND::SHAPES::Mesh>& res = static_cast<DMGD::Resource<REND::SHAPES::Mesh>&> (resource);

            // create a new mesh
            REND::SHAPES::Mesh* mesh = new REND::SHAPES::Mesh;

            // intermediate representation (Compound / Polygon) ==> VBO
            for (std::list<GEOMETRY::Compound*>::iterator i = m_compoundList.begin(), e = m_compoundList.end(); i != e; ++i) {
                GL::GLVertexBuffer* vb = createBuffer(*(*i));


                // shader information stored with resource?
                const char* shader = metadata.getValue("shader");
                if (!shader) {
                    L(normal) << "No shader set. Using default shader flatColored.";
                    shader = "flatColored";
                }

                REND::Renderable* renderable = new REND::SHAPES::CompoundRenderable((*i), vb, m_shaderManager.getShaderProgramInstance(shader));

                mesh->addRenderable(renderable);
            }
            m_compoundList.clear();

            // set instance
            res.setInstance(mesh);

            // mark as active
            FSVR::Loader::instantiate(resource, metadata);
        }
    }
}
