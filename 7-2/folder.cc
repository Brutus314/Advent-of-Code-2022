#include "folder.hpp"

Folder::Folder(DirectoryEntry* parent, std::string name) {
    _parent = parent;
    _name = name;
}

int Folder::size() {
    // Not stored; need to calculate from subfolders and files
    int total = 0;
    for (int i = 0; i < _children.size(); i++) {
        total += _children[i]->size();
    }
    return total;
}

bool Folder::isFolder() {
    return true;
}

std::string Folder::name() {
    return _name;
}

DirectoryEntry* Folder::parent() {
    return _parent;
}

std::vector<DirectoryEntry*> Folder::children() {
    return _children;
}

void Folder::addChild(DirectoryEntry* child) {
    _children.push_back(child);
}