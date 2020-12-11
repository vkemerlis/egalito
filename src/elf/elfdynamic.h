#ifndef EGALITO_ELF_ELFDYNAMIC_H
#define EGALITO_ELF_ELFDYNAMIC_H

#include <iosfwd>
#include <vector>
#include <string>
#include <utility>  // for std::pair
#include "chunk/library.h"

class ElfMap;

class ElfDynamic {
private:
    // stores library names, and the library which created the dependency
    std::vector<std::pair<std::string, Library *>> dependencyList;
    const char *rpath;
    LibraryList *libraryList;

    std::vector<std::string> searchPath;
public:
    ElfDynamic(LibraryList *libraryList)
        : rpath(nullptr), libraryList(libraryList) {}
    void parse(ElfMap *elf, Library *library);

    void addDependency(Library *library, std::string soname);

    std::string findSharedObject(std::string name);
private:
    void setupSearchPath();
    std::vector<std::string> doGlob(std::string pattern);
    bool isValidElf(std::ifstream &file);
    void parseMuslLdConfig(std::string filename,
        std::vector<std::string> &searchPath);
    void parseLdConfig(std::string filename,
        std::vector<std::string> &searchPath);
    void processLibrary(const std::string &fullPath,
        const std::string &filename, Library *depend);
    void resolveLibraries();
};

#endif
