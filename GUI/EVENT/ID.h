/* 
 * File:   ID.h
 * Author: chris
 *
 * Created on February 2, 2014, 7:09 PM
 */

#ifndef ID_H
#define	ID_H
#include "IDType.h"


namespace GUI {
    namespace EVENT {
            class ID {
            public:
                ID();
                ID(tID id);
                virtual ~ID();
                
                bool isValid() const {
                    return (m_ID > 0);
                }
                tID operator++(int);
                bool operator<(const ID& rhs) const;
                operator const tID&() const {
                    return m_ID;
                }
            private:
                tID m_ID;
            };
    }
}
#endif	/* ID_H */

