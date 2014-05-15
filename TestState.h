/* 
 * File:   TestState.h
 * Author: chris
 *
 * Created on June 13, 2013, 3:31 PM
 */

#ifndef TESTSTATE_H
#define	TESTSTATE_H

#include "STATE/State.h"

//PHYSICS
#include "PHYSICS/BOX2D/Box2DSystem.h"
#include "PHYSICS/BOX2D/Box2DController.h"
#include "PHYSICS/BodyDefinition.h"
#include "PHYSICS/Body.h"

#include "AppInputMap.h"

#include "GL/GLShaderProgram.h"
#include "GL/GLVertexBuffer.h"
#include "GL/GLTextureAtlas.h"
#include "GL/FONTS/TextureFont.h"
#include "GL/GLFrustum.h"
#include "STATE/Context.h"

class TestState : public STATE::State {
public:
    TestState(STATE::Context& context);
    virtual void Update();
    virtual void Render();
    virtual void OnEnter();
    virtual void OnLeave();
    virtual void OnResize(int width, int height);

    virtual ~TestState();
    static STATE::State* create(STATE::Context& context);
    
    void add_text( GL::GLVertexBuffer& buffer, GL::FONTS::TextureFont& font,
               wchar_t * text, MATH::vec4 * color, MATH::vec2 * pen );
private:
    static bool m_Registered;
    
    PHYSICS::BOX2D::Box2DSystem m_physicsSystem;
    //PHYSICS::BOX2D::Box2DController m_physicsController;
    
    AppInputMap m_inputMap;
    GL::GLShaderProgram m_program;
    GL::GLVertexBuffer m_buffer;
    GL::GLTextureAtlas m_atlas;
    GL::GLFrustum m_frustum;
    
};

#endif	/* TESTSTATE_H */

