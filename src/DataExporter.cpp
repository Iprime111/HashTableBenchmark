#include <Tracy.hpp>

#include "DataExporter.hpp"

char *GetApplicationDirectory () {
    char *applicationPath = (char *) calloc (FILENAME_MAX, sizeof (char));

    if (!applicationPath)
        return NULL;
    
    ssize_t count = readlink ("/proc/self/exe", applicationPath, FILENAME_MAX);
    
    return dirname (applicationPath);
}
