#ifndef AOC_FOLDER
#define AOC_FOLDER

#include "directoryEntry.hpp"

class Folder: public DirectoryEntry {
    private:
        DirectoryEntry* _parent;
        std::string _name;
        std::vector<DirectoryEntry*> _children;

    public:
        Folder(DirectoryEntry* parent, std::string name);
        int size(); // Will need to calculate this
        bool isFolder();
        DirectoryEntry* parent();
        std::string name();
        std::vector<DirectoryEntry*> children();
        void addChild(DirectoryEntry* child);
};

#endif