/* 
 * File:   TestState.cpp
 * Author: chris
 * 
 * Created on June 13, 2013, 3:31 PM
 */

#include "TestState.h"
#include "StateManager.h"
#include "ResourceManager.h"

//PHYSICS
#include "PHYSICS/BOX2D/Box2DBodyDefinition.h"
#include "PHYSICS/BOX2D/Box2DBodyPart.h"
#include "PHYSICS/BOX2D/Box2DOrientation.h"
#include "PHYSICS/BOX2D/Box2DPosition.h"
#include "PHYSICS/BOX2D/Box2DBody.h"

#include "INPUT/Input.h"
#include "INPUT/InputManager.h"

#include "GL/GLVertexBuffer.h"
#include "GL/GLShader.h"
#include "GL/GLTextureAtlas.h"
#include "MATH/vec234.h"


#include <GL/glew.h>



bool TestState::m_Registered = StateManager::getInstance().Register("TestState", &TestState::create);

TestState::TestState(STATE::Context& context)
: STATE::State("TestState", context)
, m_buffer("vertex:3f,tex_coord:2f,color:4f")
, m_atlas(600, 600, 1)
, m_program("v3f-t2f-c4f") {
    m_frustum.SetOrthographic(0,600,0,600,-10,10);
    /*GLuint indices[6] = {0, 1, 2, 0, 2, 3};
    float x0 = 1;
    float y0 = -1.0;
    float x1 = -1.0;
    float y1 = 1;

    typedef struct {
        float x, y, z, u, v, r, g, b, a;
    } vertex_t;
    vertex_t vertices[4] = {
        { x0, y0, 0, 1, 1, 0.4,0.4,0.8, 1},
        { x0, y1, 0, 1, 0, 0.4,0.4,0.8, 1},
        { x1, y1, 0, 0, 0, 0.4,0.4,0.8, 1},
        { x1, y0, 0, 0, 1, 0.4,0.4,0.8, 1}
    };
    m_buffer.push_back(vertices, 4, indices, 6);*/
}

TestState::~TestState() {
    L(normal) << "TestState::~TestState()";
}

void TestState::Update() {
    //    m_physicsController.evolve(m_physicsSystem);

    // some output
    //    PHYSICS::BOX2D::Box2DBody* dynamicBody = static_cast<PHYSICS::BOX2D::Box2DBody*>( (*m_bodyHandle).operator *() );
    //    b2Vec2 position = dynamicBody->getBodyPtr()->GetPosition();
    //    L(normal) << "Position: " << position.x << " " << position.y;
}

void TestState::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program.activate();
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_atlas.getTexture());

    m_program.setUniformi("texture", 1);
    m_program.setUniform("projection", m_frustum.GetProjectionMatrix());
    //glUniformMatrix4fv( glGetUniformLocation( m_program.getProgram(), "projection" ),
    //                        1, 0, m_frustum.GetProjectionMatrix());
    
    /*
    m_program.setUniform<int>("N",3);
    m_program.setUniform<float>("positions[0].y", -0.5);
    m_program.setUniform<float>("positions[0].color", 1.0, 0.0, 0.0, 1.0);
    m_program.setUniform<float>("positions[1].y", 0.0);
    m_program.setUniform<float>("positions[1].color", 0.0, 1.0, 0.0, 1.0);
    m_program.setUniform<float>("positions[2].y", 0.5);
    m_program.setUniform<float>("positions[2].color", 0.0, 0.0, 1.0, 1.0);
     */
    m_buffer.render(GL_TRIANGLES);
}

void TestState::add_text(GL::GLVertexBuffer& buffer, GL::FONTS::TextureFont& font,
        wchar_t * text, MATH::vec4 * color, MATH::vec2 * pen) {
    /*size_t i;
    float r = color->red, g = color->green, b = color->blue, a = color->alpha;
    for (i = 0; i < wcslen(text); ++i) {
        GL::FONTS::TextureGlyph * glyph = font.get_glyph(text[i]);
        if (glyph != NULL) {
            int kerning = 0;
            if (i > 0) {
                kerning = glyph->getKerning(text[i - 1]);
            }
            pen->x += kerning;
            float x0 = (pen->x + glyph->offset_x);
            float y0 = (pen->y + glyph->offset_y);
            float x1 = (x0 + glyph->width);
            float y1 = (y0 - glyph->height);
            float s0 = glyph->s0;
            float t0 = glyph->t0;
            float s1 = glyph->s1;
            float t1 = glyph->t1;
            GLuint indices[6] = {0, 1, 2, 0, 2, 3};
            typedef struct {
                float x, y, z, u, v, r, g, b, a;
            } vertex_t;
            vertex_t vertices[4] = {
                { x0, y0, 0, s0, t0, r, g, b, a},
                { x0, y1, 0, s0, t1, r, g, b, a},
                { x1, y1, 0, s1, t1, r, g, b, a},
                { x1, y0, 0, s1, t0, r, g, b, a}
            };
            m_buffer.push_back(vertices, 4, indices, 6);
            pen->x += glyph->advance_x;
        }
    }*/
}

void TestState::OnEnter() {
/*
    const char *filename = "fonts/Courier_New.ttf";
    const wchar_t *cache = L" !\"#$%&'()*+,-./0123456789:;<=>?"
            L"@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
            L"`abcdefghijklmnopqrstuvwxyz{|}~";
    size_t minsize = 20, maxsize = 40;
    size_t count = maxsize - minsize;
    size_t i, missed = 0;


    MATH::vec2 pen = {
        {5, 600}};


    wchar_t *text = L"Hello world!";

    
    for (i = minsize; i < maxsize; ++i) {
        float r = ((float) rand()) / ((float) RAND_MAX);
        float g = ((float) rand()) / ((float) RAND_MAX);
        float b = ((float) rand()) / ((float) RAND_MAX);
        
            MATH::vec4 black = {
        { r,g,b, 1}};
    GL::FONTS::TextureFont* font = new GL::FONTS::TextureFont(&m_atlas, i, filename);
    missed += font->load_glyphs(text);
        pen.x = 5;
        pen.y -= font->getHeight();
    add_text(m_buffer, *font, text, &black, &pen);
    delete font;
    }


    GL::GLShader vertexShader(GL::GLShader::VERTEX);
    vertexShader.compileFromFile("shaders/v3f-t2f-c4f.vp");

    GL::GLShader fragmentShader(GL::GLShader::FRAGMENT);
    fragmentShader.compileFromFile("shaders/v3f-t2f-c4f.fp");

    m_program.attachShader(vertexShader);
    m_program.attachShader(fragmentShader);
    m_program.link();

*/
    // ResourceManager Test
    /*    Context& ctx = static_cast<Context&>(context);
    ctx.getResourceManager().loadTexture("image", FSVR::Resource::IMMEDIATELY);
    ctx.getResourceManager().loadSound("plop", FSVR::Resource::IMMEDIATELY);
     */

    /*
    INPUT::InputManager::getInstance().registerInputMap(&m_inputMap);
    
    using namespace PHYSICS::BOX2D;
    // Physics Test
    Box2DBodyDefinition bodyDefinition;
    Box2DBodyPart bodyPart;
    
    //create ground body
    bodyDefinition.setBodyType(PHYSICS::STATIC);
    bodyDefinition.setOrientation(Box2DOrientation(0.0f));
    bodyDefinition.setPosition(Box2DPosition(0.0f, 0.0f));
    PHYSICS::BodyHandle handle = m_physicsSystem.createBody(bodyDefinition);
    bodyPart.setDimensions(10.0f, 1.0f);
    m_physicsSystem.attachBodyPart(handle, bodyPart);
    
    bodyDefinition.setBodyType(PHYSICS::DYNAMIC);
    bodyDefinition.setOrientation(Box2DOrientation(0.0f));
    bodyDefinition.setPosition(Box2DPosition(0.0f, 10.0f));
    handle = m_physicsSystem.createBody(bodyDefinition); // is this safe?
    bodyPart.setDimensions(1.0f, 1.0f);
    m_physicsSystem.attachBodyPart(handle, bodyPart);
     */
    L(normal) << "Enter.";

    //    m_physicsSystem.showBodyInfo();

    // Setup a perspective projection

    // Set color and depth clear value
    glClearDepth(1.f);
    glClearColor(1.f, 1.f, 1.f, 1.f);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);

    /*
    // Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, 500.f);
     */

}

void TestState::OnLeave() {
    INPUT::InputManager::getInstance().removeInputMap(&m_inputMap);
    L(normal) << "Leave.";
}

void TestState::OnResize(int width, int height) {
    
}


STATE::State* TestState::create(STATE::Context& context) {
    return new TestState(context);
}