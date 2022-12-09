#ifndef AOC_FILE
#define AOC_FILE

#include "directoryEntry.hpp"

class File: public DirectoryEntry {
    private:
        int _size;
        DirectoryEntry* _parent;
        std::string _name;

    public:
        File(int size, DirectoryEntry* parent, std::string name);
        int size();
        bool isFolder();
        DirectoryEntry* parent();
        std::string name();
        std::vector<DirectoryEntry*> children(); // This won't make sense
        void addChild(DirectoryEntry* child); // This won't make sense
};

#endif