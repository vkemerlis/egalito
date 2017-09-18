#ifndef EGALITO_CONDUCTOR_CONDUCTOR_H
#define EGALITO_CONDUCTOR_CONDUCTOR_H

#include "elf/elfforest.h"

class ChunkVisitor;

class Conductor {
private:
    ElfForest *forest;
    Program *program;
    address_t mainThreadPointer;
public:
    Conductor();
    ~Conductor();

    void parseExecutable(ElfMap *elf);
    void parseEgalito(ElfMap *elf);
    void parseLibraries();
    void parseAddOnLibrary(ElfMap *elf);
    void parseEgalitoArchive(const char *archive);

    void resolvePLTLinks();
    void fixDataSections();

    void writeDebugElf(const char *filename, const char *suffix = "$new");
    void acceptInAllModules(ChunkVisitor *visitor, bool inEgalito = true);

    Program *getProgram() const { return program; }
    ElfSpace *getMainSpace() const { return forest->getMainSpace(); }
    LibraryList *getLibraryList() const { return forest->getLibraryList(); }
    ElfSpaceList *getSpaceList() const { return forest->getSpaceList(); }

    address_t getMainThreadPointer() const { return mainThreadPointer; }
private:
    ElfSpace *parse(ElfMap *elf, SharedLib *library);
    void allocateTLSArea();
    void loadTLSData();
};

#endif
