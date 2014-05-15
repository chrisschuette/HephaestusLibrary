/* 
 * File:   DirectoryBundle.h
 * Author: chris
 *
 * Created on June 10, 2013, 2:57 PM
 */

#ifndef DIRECTORYBUNDLE_H
#define	DIRECTORYBUNDLE_H

#include "Bundle.h"

#include <string>
#include <boost/filesystem.hpp>
#include "../LOG/Source.h"

namespace BNDL {
class DirectoryBundle: public Bundle, public LOG::Source {
public:
    DirectoryBundle();
    DirectoryBundle(std::string directory);
    void setDirectory(std::string directory);
    virtual ~DirectoryBundle();
 
    virtual int read(tLocation location, unsigned char ** data) const;
private:
    boost::filesystem::path m_path;
};
}
#endif	/* DIRECTORYBUNDLE_H */

