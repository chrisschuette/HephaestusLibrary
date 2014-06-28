#include "vec234.h"

namespace MATH {

    vec2 operator -(const vec2& a, const vec2 b) {
        vec2 result;
        result.x = a.x - b.x;
        result.y = a.y - b.y;
        return result;
    }
}
