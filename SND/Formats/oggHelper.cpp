#include "oggHelper.h"
#include <cstring>

namespace SND {
    namespace Formats {

        size_t AR_readOgg(void* dst, size_t size1, size_t size2, void* fh) {
            ogg_file* of = reinterpret_cast<ogg_file*> (fh);
            size_t len = size1 * size2;
            if (of->curPtr + len > of->filePtr + of->fileSize) {
                len = of->filePtr + of->fileSize - of->curPtr;
            }
            memcpy(dst, of->curPtr, len);
            of->curPtr += len;
            return len;
        }

        int AR_seekOgg(void *fh, ogg_int64_t to, int type) {
            ogg_file* of = reinterpret_cast<ogg_file*> (fh);

            switch (type) {
                case SEEK_CUR:
                    of->curPtr += to;
                    break;
                case SEEK_END:
                    of->curPtr = of->filePtr + of->fileSize - to;
                    break;
                case SEEK_SET:
                    of->curPtr = of->filePtr + to;
                    break;
                default:
                    return -1;
            }
            if (of->curPtr < of->filePtr) {
                of->curPtr = of->filePtr;
                return -1;
            }
            if (of->curPtr > of->filePtr + of->fileSize) {
                of->curPtr = of->filePtr + of->fileSize;
                return -1;
            }
            return 0;
        }

        int AR_closeOgg(void* fh) {
            return 0;
        }

        long AR_tellOgg(void *fh) {
            ogg_file* of = reinterpret_cast<ogg_file*> (fh);
            return (of->curPtr - of->filePtr);
        }
    }
}