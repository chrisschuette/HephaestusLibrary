/* 
 * File:   GradientLayer.h
 * Author: chris
 *
 * Created on May 27, 2014, 12:48 PM
 */

#ifndef GLGRADIENTLAYER_H
#define	GLGRADIENTLAYER_H

#include "../../LVL/LAYERS/GradientLayer.h"
#include "../GLShaderManager.h"
#include "../GLShaderProgram.h"
#include "../GLVertexBuffer.h"

namespace GL {
    namespace LAYERS {

        template <int N>
        class GradientLayer : public LVL::LAYERS::GradientLayer<N> {
        public:

            GradientLayer(LVL::LAYERS::GRADIENT_TYPE type, LVL::Context& context)
            : LVL::LAYERS::GradientLayer<N>(context)
            , m_shaderManager(static_cast<GLShaderManager&> (context.getShaderManager())) {
                this->m_shaderProgram = new REND::ShaderProgramInstance(m_shaderManager.getShaderProgramInstance("linearGradient"));
                m_screen = new GL::GLVertexBuffer("vertex:2f");
                GLuint indices[6] = {0, 1, 2, 0, 3, 1};
                MATH::vec2 vertices[4] = {
                    {-1, -1},
                    {1, 1},
                    {-1, 1},
                    {1, -1}
                };
                m_screen->push_back(vertices, 4, indices, 6);
                setGradientType(type);
            }

            virtual ~GradientLayer() {
                if(m_screen)
                    delete m_screen;
            }

            virtual void setGradientType(LVL::LAYERS::GRADIENT_TYPE type) {
                if (this->m_shaderProgram)
                    delete this->m_shaderProgram;
                this->m_shaderProgram = 0;
                if (type == LVL::LAYERS::LINEAR) {
                    // linear gradient
                    this->m_shaderProgram = new REND::ShaderProgramInstance(m_shaderManager.getShaderProgramInstance("linearGradient"));
                } else {
                    // radial gradient
                    this->m_shaderProgram = new REND::ShaderProgramInstance(m_shaderManager.getShaderProgramInstance("radialGradient"));
                }
            }

            virtual void update(unsigned long int time, unsigned long int diff) {

            }

            virtual void render(REND::Renderer& renderer, LVL::Context& context) {
                if (this->m_shaderProgram) {
                    GL::GLShaderProgram* shaderProgram = static_cast<GL::GLShaderProgram*>(this->m_shaderProgram->operator *());
                    shaderProgram->activate();
                    shaderProgram->setUniformi("N", N);
                    for (int i = 0; i < N; i++) {
                        /*std::cout << this->m_gradientStops[i].position_name << std::endl;
                        std::cout << this->m_gradientStops[i].position << std::endl;
                        std::cout << this->m_gradientStops[i].color_name << std::endl;
                        std::cout << this->m_gradientStops[i].rgba.r << " " << this->m_gradientStops[i].rgba.g << " " << this->m_gradientStops[i].rgba.b << " " << this->m_gradientStops[i].rgba.a << std::endl;*/
                        shaderProgram->setUniformf(this->m_gradientStops[i].position_name, this->m_gradientStops[i].position);
                        shaderProgram->setUniformf(this->m_gradientStops[i].color_name, this->m_gradientStops[i].rgba.r, this->m_gradientStops[i].rgba.g, this->m_gradientStops[i].rgba.b, this->m_gradientStops[i].rgba.a);
                    }
                    m_screen->render(GL_TRIANGLES);
                }
            }
        private:
            GLVertexBuffer* m_screen;
            GLShaderManager& m_shaderManager;
        };
    }
}
#endif	/* GLGRADIENTLAYER_H */

