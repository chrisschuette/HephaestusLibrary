/* 
 * File:   RENDER.h
 * Author: chris
 *
 * Created on May 21, 2014, 11:03 PM
 */

#ifndef RENDER_H
#define	RENDER_H

#include "../CMPN/Message.h"
#include "DEFAULT_MIDs.h"
#include "Context.h"

#include <iostream>

namespace REND {
    class Renderer;
}

namespace LVL {
    class RENDER: public CMPN::Message<MID_RENDER> {
    public:
        RENDER(REND::Renderer& r, LVL::Context& ctx) : CMPN::Message<MID_RENDER>(), renderer(r), context(ctx) {}
        virtual ~RENDER() {}
        REND::Renderer& renderer;
        LVL::Context& context;
    private:
    };
}
#endif	/* RENDER_H */

