#include "err.h"

std::string getALErrorString(int err) {
        switch (err) {
      case AL_NO_ERROR:
        return "AL_NO_ERROR";
      case AL_INVALID_NAME:
        return "AL_INVALID_NAME";
      case AL_INVALID_ENUM:
        return "AL_INVALID_ENUM";
      case AL_INVALID_VALUE:
        return "AL_INVALID_VALUE";
      case AL_INVALID_OPERATION:
        return "AL_INVALID_OPERATION";
      case AL_OUT_OF_MEMORY:
        return "AL_OUT_OF_MEMORY";
      default:
        return "No such error code";
    }
}

std::string getALCErrorString(int err) {
        switch (err) {
      case ALC_NO_ERROR:
        return "AL_NO_ERROR";
      case ALC_INVALID_DEVICE:
        return "ALC_INVALID_DEVICE";
      case ALC_INVALID_CONTEXT:
        return "ALC_INVALID_CONTEXT";
      case ALC_INVALID_ENUM:
        return "ALC_INVALID_ENUM";
      case ALC_INVALID_VALUE:
        return "ALC_INVALID_VALUE";
      case ALC_OUT_OF_MEMORY:
        return "ALC_OUT_OF_MEMORY";
      default:
        return "no such error code";
    }
}