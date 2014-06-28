    # FindConfig++.cmake
    # Copyright © 2014 Christoph Schütte
    #
    # This file is free software. It comes without any warranty, to the
    # extent permitted by applicable law. You can redistribute it and/or
    # modify it under the terms of the Do What The Fuck You Want To Public
    # License, Version 2, as published by Sam Hocevar. See
    # http://sam.zoy.org/wtfpl/COPYING for more details.
    # This module tries to find the config++ library and sets the following
    # variables:
    # CONFIG++_INCLUDE_DIR
    # CONFIG++_LIBRARY
    # CONFIG++_FOUND
    include(FindPackageHandleStandardArgs)
    # Search for the header file
    find_path(CONFIG++_INCLUDE_DIR libconfig.h++
    PATH_SUFFIXES include)
    # Search for the library
    find_library(CONFIG++_LIBRARY NAMES config++
    PATH_SUFFIXES lib)
    # Did we find everything we need?
    FIND_PACKAGE_HANDLE_STANDARD_ARGS(CONFIG++ DEFAULT_MSG
    CONFIG++_LIBRARY CONFIG++_INCLUDE_DIR)
