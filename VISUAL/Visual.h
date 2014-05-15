/* 
 * File:   Visual.h
 * Author: chris
 *
 * Created on June 23, 2013, 5:47 PM
 */

#ifndef VISUAL_H
#define	VISUAL_H

namespace REND {
    class Renderer;
}

namespace VISUAL {
    class VisualInstance;
class Visual {
public:
    Visual();
    virtual void render(const VisualInstance& instance, REND::Renderer& renderer) const = 0;
    virtual ~Visual();
private:

};
}
#endif	/* VISUAL_H */

