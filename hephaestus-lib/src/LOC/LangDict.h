/* 
 * File:   LangDict.h
 * Author: chris
 *
 * Created on March 8, 2014, 12:13 PM
 */

#ifndef LOC_LANGDICT_H
#define	LOC_LANGDICT_H

#include "../FSVR/Resource.h"
#include "../FSVR/Loader.h"
#include "../LEX/LangDict.h"

namespace LOC {
    
    class LangDictLoader: public FSVR::Loader {
    public:
        LangDictLoader();
        virtual ~LangDictLoader();
        
        virtual void instantiate(FSVR::Resource& resource, const FSVR::ResourceMetaData& metadata);
    };

    class LangDict: public FSVR::Resource, public LEX::LangDict {
    public:
        LangDict();
        LangDict(const FSVR::tRID& rid);
        virtual ~LangDict();
        
        static FSVR::Loader* createLoader();
    private:

    };
}
#endif	/* LOC_LANGDICT_H */

