/* 
 * File:   Algorithms.h
 * Author: chris
 *
 * Created on June 2, 2014, 12:51 PM
 */

#ifndef ALGORITHMS_H
#define	ALGORITHMS_H

#include "../MATH/vec234.h"
#include "Compound.h"

#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

namespace GEOMETRY {

    std::list< MATH::vec2 > constructOutline( const Compound& compound );
    std::list< Compound > split(Compound& compound, int N);
    
    template <typename ForwardIterator, typename OutputIterator>
    OutputIterator grahamScan(ForwardIterator begin, ForwardIterator end,
            OutputIterator out);

    namespace grahamScan_implementation {

        bool compareYCoordinates(const MATH::vec2& lhs, const MATH::vec2& rhs);

        class CompareByAngle {
        public:
            explicit CompareByAngle(const MATH::vec2& origin);
            bool operator() (const MATH::vec2& lhs, const MATH::vec2& rhs) const;
        private:
            const MATH::vec2 origin;
        };
    }

    template <typename ForwardIterator, typename OutputIterator>
    OutputIterator GrahamScan(ForwardIterator begin, ForwardIterator end,
            OutputIterator out) {
        using namespace grahamScan_implementation;

        if (size_t(std::distance(begin, end)) < 3) {
            std::cout << "Trivial" << std::endl;
            return std::copy(begin, end, out);
        }

        ForwardIterator minY = std::min_element(begin, end, compareYCoordinates);

        ForwardIterator next = minY;
        ++next;

        std::vector< MATH::vec2 > points;
        points.insert(points.end(), begin, minY); // First portion of the points.
        points.insert(points.end(), next, end); // Remainder of the points.
        std::sort(points.begin(), points.end(), CompareByAngle(*minY));
        points.push_back(*minY);
        std::vector< MATH::vec2 > result;
        result.push_back(*minY);
        result.push_back(points[0]);
        for (size_t i = 1; i < points.size(); ++i) {
            while (true) {
                const MATH::vec2 last = result[result.size() - 1] - result[result.size() - 2];
                const MATH::vec2 curr = points[i] - result[result.size() - 1];
                if (last.data[0] * curr.data[1] - last.data[1] * curr.data[0] >= 0) break;
                result.pop_back();
            }
            result.push_back(points[i]);
        }
        result.pop_back();
        return std::copy(result.begin(), result.end(), out);
    }

}

#endif	/* ALGORITHMS_H */

