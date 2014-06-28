/* 
 * File:   SVGtoCompound.h
 * Author: chris
 *
 * Created on May 31, 2014, 12:32 PM
 */

#ifndef SVGTOCOMPOUND_H
#define	SVGTOCOMPOUND_H

#include "../../GEOMETRY/Compound.h"
#include <rapidxml.hpp>
#include <list>
#include <string>
#include "../../MATH/vec234.h"

namespace REND {
    namespace SHAPES {
        std::list<GEOMETRY::Compound*> parseSVG(const unsigned char * pData, int nBytes);
        void find_polygons(rapidxml::xml_node<>* node, GEOMETRY::Compound& compound);
        void parse_polygon(rapidxml::xml_node<>* polygon_node, GEOMETRY::Compound& compound);
        std::list<MATH::vec2> parsePointsString(std::string points_string);
    }
}
#endif	/* SVGTOCOMPOUND_H */

