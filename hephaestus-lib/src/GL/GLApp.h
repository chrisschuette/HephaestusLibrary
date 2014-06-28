/* 
 * File:   GLApp.h
 * Author: chris
 *
 * Created on June 12, 2013, 8:49 PM
 */

#ifndef GLAPP_H
#define	GLAPP_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../APP/Application.h"
#include "../APP/Clock.h"
#include "../MATH/vec234.h"

namespace APP {
    class FPSController;
}

namespace GL {
    class GLApp : public APP::Application {
    public:
        GLApp();
        virtual void Init();
        void initGLEW();
        virtual void Exec() = 0;
        virtual bool IsDone() = 0;
        virtual void Shutdown();
        virtual ~GLApp();
        GLFWwindow* GetWindow() const;
        std::string GetTitle() const;
        virtual int GetWindowHeight() const;
        virtual int GetWindowWidth() const;
        virtual MATH::ivec2 GetWindowDimensions() const;
        
    protected:
        void display();
        int m_width;
        int m_height;
        int m_depth;
        std::string m_title;
        GLFWwindow* m_pWindow;
        APP::FPSController* m_FPSController;
    };
}
#endif	/* GLAPP_H */

