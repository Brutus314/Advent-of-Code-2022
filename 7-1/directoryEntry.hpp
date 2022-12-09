#ifndef AOC_DIRECTORY_ENTRY
#define AOC_DIRECTORY_ENTRY

#include <vector>
#include <string>

class DirectoryEntry {
    public:
        // We'll need all these to check information about them later
        virtual int size() = 0;
        virtual bool isFolder() = 0;
        virtual DirectoryEntry* parent() = 0;
        virtual std::string name() = 0;
        virtual std::vector<DirectoryEntry*> children() = 0;
        virtual void addChild(DirectoryEntry* child) = 0;
};

#endif