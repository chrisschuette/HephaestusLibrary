/* 
 * File:   BodyPartDescription.h
 * Author: chris
 *
 * Created on May 21, 2014, 11:34 PM
 */

#ifndef BODYPARTDESCRIPTION_H
#define	BODYPARTDESCRIPTION_H

namespace PHYSICS {

    class BodyPartDescription {
    public:
        BodyPartDescription();
        virtual ~BodyPartDescription();
        virtual BodyPartDescription* clone() const = 0;
       
    private:

    };
}
#endif	/* BODYPARTDESCRIPTION_H */

