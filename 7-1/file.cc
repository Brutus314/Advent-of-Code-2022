#include "file.hpp"

File::File(int size, DirectoryEntry* parent, std::string name) {
    _size = size;
    _parent = parent;
    _name = name;
}

int File::size() {
    return _size;
}

bool File::isFolder() {
    return false;
}

std::string File::name() {
    return _name;
}

DirectoryEntry* File::parent() {
    return _parent;
}

std::vector<DirectoryEntry*> File::children() {
    // Makes no sense for files
    return std::vector<DirectoryEntry*>();
}

void File::addChild(DirectoryEntry* child) {
    // Makes no sense for files
    return;
}