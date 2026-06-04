#include <dirent.h>

DIR* nuc_opendir(const char *name) { return opendir(name); }
struct dirent* nuc_readdir(DIR *dirp) { return readdir(dirp); }
int nuc_closedir(DIR *dirp) { return closedir(dirp); }
