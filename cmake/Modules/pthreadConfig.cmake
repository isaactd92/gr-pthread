INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_PTHREAD pthread)

FIND_PATH(
    PTHREAD_INCLUDE_DIRS
    NAMES pthread/api.h
    HINTS $ENV{PTHREAD_DIR}/include
        ${PC_PTHREAD_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    PTHREAD_LIBRARIES
    NAMES gnuradio-pthread
    HINTS $ENV{PTHREAD_DIR}/lib
        ${PC_PTHREAD_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(PTHREAD DEFAULT_MSG PTHREAD_LIBRARIES PTHREAD_INCLUDE_DIRS)
MARK_AS_ADVANCED(PTHREAD_LIBRARIES PTHREAD_INCLUDE_DIRS)

