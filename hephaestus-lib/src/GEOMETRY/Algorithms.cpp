#include "Algorithms.h"
#include "Compound.h"
#include "Polygon.h"
#include "../LOG/Core.h"

#include <cmath>

#define NAME "Algorithms"

namespace GEOMETRY {

    std::list< Compound > split(Compound& compound, int N) {
        assert(N > 0);

        std::list< Compound > compounds;

        for (int i = 0; i < N; i++) {
            Compound c;
            int size = compound.countPolygons();
            if(size == 0)
                break;
            int choice = rand() % size;
            std::list<Polygon*>& shapes = compound.getShapes();
            std::list<Polygon*>::iterator it = shapes.begin();
            std::advance(it, choice);
            c.addPolygon(*it);
            compound.removePolygon(*it);
            compounds.push_back(c);
        }

        bool progress = false;
        do {
            progress = false;
            // iterate over list of compounds and grow them!
            for (std::list< Compound >::iterator i = compounds.begin(), e = compounds.end(); i != e; ++i) {
                Compound& c = (*i);
                const std::list<Polygon*>& shapes = c.getShapes();
                const std::list<Polygon*>& shapes_left = compound.getShapes();

                // compile a list of neighbouring polygons
                std::list< Polygon* > neighbouring_polygons;
                for (std::list<Polygon*>::const_iterator i1 = shapes.begin(), e1 = shapes.end(); i1 != e1; ++i1)
                    for (std::list<Polygon*>::const_iterator i2 = shapes_left.begin(), e2 = shapes_left.end(); i2 != e2; ++i2)
                        if ((*i1)->countSharedVertices(*(*i2)) == 2) {
                            //L(normal) << "Neighbours:";
                            //L(normal) << *(*i1);
                            //L(normal) << *(*i2);
                            neighbouring_polygons.push_back((*i2));
                        }
                if (neighbouring_polygons.size() == 0) {
                    continue;
                }
                int choice = rand() % neighbouring_polygons.size();
                std::list<Polygon*>::const_iterator it = neighbouring_polygons.begin();
                std::advance(it, choice);
                c.addPolygon(*it);
                compound.removePolygon(*it);
                progress = true;
            }

        } while (progress);


        return compounds;
    }

    std::list< MATH::vec2 > constructOutline(const Compound& compound) {
        std::list< MATH::vec2 > outline;
        std::list< MATH::vec2 > points;
        // collect all points in a list and use the graham scan to calculate the convex hull
        const std::list<Polygon*>& polygons = compound.getShapes();
        for (std::list<Polygon*>::const_iterator i = polygons.begin(), e = polygons.end(); i != e; ++i) {
            Polygon* polygon = (*i);
            const std::vector<MATH::vec2>& vertices = polygon->getVertices();
            for (std::vector<MATH::vec2>::const_iterator j = vertices.begin(), f = vertices.end(); j != f; ++j) {
                bool tooClose = false;
                // calculate distance
                for (std::list< MATH::vec2 >::const_iterator k = points.begin(), g = points.end(); k != g; ++k)
                    if (std::sqrt(std::pow((*k).x - (*j).x, 2) + std::pow((*k).y - (*j).y, 2)) < 1e-4)
                        tooClose = true;
                if (!tooClose)
                    points.push_back(*j);


            }
        }
        GrahamScan(points.begin(), points.end(), std::back_inserter(outline));
        return outline;
    }

    namespace grahamScan_implementation {

        bool compareYCoordinates(const MATH::vec2& lhs, const MATH::vec2& rhs) {

            if (lhs.data[1] != rhs.data[1])
                return lhs.data[1] < rhs.data[1];
            return lhs.data[0] < rhs.data[0];
        }

        CompareByAngle::CompareByAngle(const MATH::vec2& origin) : origin(origin) {
        }

        bool CompareByAngle::operator() (const MATH::vec2& lhs,
                const MATH::vec2& rhs) const {
            const MATH::vec2 one = lhs - origin;
            const MATH::vec2 two = rhs - origin;

            const double normOne = std::sqrt(one.x * one.x + one.y * one.y);
            const double normTwo = std::sqrt(two.x * two.x + two.y * two.y);
            const double negCosOne = -one.data[0] / normOne;
            const double negCosTwo = -two.data[0] / normTwo;

            if (negCosOne != negCosTwo)
                return negCosOne < negCosTwo;

            return normOne < normTwo;
        }
    }
}