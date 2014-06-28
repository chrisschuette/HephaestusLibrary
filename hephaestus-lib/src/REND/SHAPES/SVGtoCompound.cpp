#include "SVGtoCompound.h"
#include "../../ERR/ERR.h"
#include <string.h>
#include "../../LOG/Core.h"
#include "Polygon.h"
#include <boost/algorithm/string.hpp>

#define NAME "parseSVG"

namespace REND {
    namespace SHAPES {

        std::list<GEOMETRY::Compound*> parseSVG(const unsigned char * pData, int nBytes) {
            using namespace rapidxml;

            std::list<GEOMETRY::Compound*> compound_list;

            char * xml = new char[nBytes + 1];
            memcpy(xml, pData, nBytes);
            xml[nBytes] = 0;
            xml_document<> doc; // character type defaults to char
            doc.parse < 0 > (xml); // 0 means default parse flags

            xml_node<>* svg_root = doc.first_node("svg");
            if (!svg_root)
                THROWS("No SVG node found.");

            //determine whether the file is grouped
            bool grouped = false;
            for (xml_node<> *child = svg_root->first_node(); child; child = child->next_sibling()) {
                if (strcmp(child->name(), "g") == 0)
                    grouped = true;
            }
            if (grouped) {
                L(normal) << "GROUPED!";
                for (xml_node<> *child = svg_root->first_node(); child; child = child->next_sibling())
                    if (strcmp(child->name(), "g") == 0) {
                        GEOMETRY::Compound* compound = new GEOMETRY::Compound;
                        find_polygons(child, *compound);
                        compound_list.push_back(compound);
                    }
                
            } else {
                L(normal) << "NOT GROUPED!";
                GEOMETRY::Compound* compound = new GEOMETRY::Compound;
                find_polygons(svg_root, *compound);
                compound_list.push_back(compound);
            }

            delete [] xml;
            return compound_list;
        }

        MATH::vec4 parseColorString(std::string color_string) {
            // remove tabs and newlines
            color_string.erase(std::remove(color_string.begin(), color_string.end(), '\n'), color_string.end());
            color_string.erase(std::remove(color_string.begin(), color_string.end(), '\t'), color_string.end());

            assert(color_string.size() == 7);
            MATH::vec4 color;
            color.a = 1;

            int raw = strtoul(&color_string[1], NULL, 16);
            color.r = ((raw & 16711680) >> 16) / 255.f;
            color.g = ((raw & 65280) >> 8) / 255.f;
            color.b = (raw & 255) / 255.f;

            return color;
        }

        std::list<MATH::vec2> parsePointsString(std::string points_string) {
            using namespace boost;

            std::list<MATH::vec2> points;

            // remove tabs and newlines
            points_string.erase(std::remove(points_string.begin(), points_string.end(), '\n'), points_string.end());
            points_string.erase(std::remove(points_string.begin(), points_string.end(), '\t'), points_string.end());

            // split on spaces (vertices are separated by spaces)
            std::vector<std::string> vertex_strings;
            split(vertex_strings, points_string, is_any_of(" "));

            for (std::vector<std::string>::const_iterator i = vertex_strings.begin(), e = vertex_strings.end(); i != e; ++i) {
                if ((*i).size() == 0)
                    continue;

                // individual coordinates are comma separated
                std::vector<std::string> coordinates;
                split(coordinates, (*i), is_any_of(","));

                if (coordinates.size() != 2)
                    THROWS("Coordinate invalid: " + (*i));

                // add to point list
                MATH::vec2 vertex;
                vertex.x = ::atof(coordinates[0].c_str());
                vertex.y = ::atof(coordinates[1].c_str());
                points.push_back(vertex);
            }
            return points;
        }

        void parse_polygon(rapidxml::xml_node<>* polygon_node, GEOMETRY::Compound& compound) {
            using namespace rapidxml;
            xml_attribute<> *points = polygon_node->first_attribute("points");
            if (!points->value()) {
                L(error) << "Unable to find vertices for polygon.";
                return;
            }
            REND::SHAPES::Polygon* polygon = new REND::SHAPES::Polygon;

            // extract vertices
            std::list<MATH::vec2> vertex_list = parsePointsString(points->value());
            for (std::list<MATH::vec2>::iterator i = vertex_list.begin(), e = vertex_list.end(); i != e; ++i)
                polygon->addVertex(*i);

            // extract color
            MATH::vec4 color;
            xml_attribute<> *fill = polygon_node->first_attribute("fill");
            if (fill)
                color = parseColorString(fill->value());
            else {
                color.r = 0.5;
                color.g = 0.5;
                color.b = 0.5;
                color.a = 1;
            }

            // extract opacity
            xml_attribute<> *opacity = polygon_node->first_attribute("opacity");
            if (opacity)
                color.a = ::atof(opacity->value());

            polygon->setFillColor(color);

            // check if we are good

            // add to compound
            compound.addPolygon(polygon);
        }

        void find_polygons(rapidxml::xml_node<>* node, GEOMETRY::Compound& compound) {
            using namespace rapidxml;
            // check if this is a polygon
            if (strcmp(node->name(), "polygon") == 0)
                parse_polygon(node, compound);
            else
                for (xml_node<> *child = node->first_node(); child; child = child->next_sibling())
                    find_polygons(child, compound);
        }
    }
}