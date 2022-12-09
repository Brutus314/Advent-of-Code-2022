#include <iostream>
#include "directoryEntry.hpp"
#include "file.hpp"
#include "folder.hpp"

using namespace std;

int findTotalOfFolderWithAtMost100000Size(DirectoryEntry* folder);

int main() {
    string input, command, destination, fileFolderName;
    DirectoryEntry* pointer = new Folder(NULL, "/");
    DirectoryEntry* topPointer = pointer;

    // Go until end of input
    while ((cin >> input) && input.length() > 0) {
        if (input == "$") {
            // Doing a command
            cin >> command;
            if (command == "cd") {
                // Our pointer will change
                cin >> destination;
                if (destination == "/") {
                    // To the top
                    pointer = topPointer;
                } else if (destination == "..") {
                    // Up one
                    pointer = pointer->parent();
                } else {
                    // Find the child
                    vector<DirectoryEntry*> children = pointer->children();
                    for (int i = 0; i < children.size(); i++) {
                        if (children[i]->name() == destination) {
                            pointer = children[i];
                        }
                    }
                }
            }
            // The ls command contributes nothing to our state
        } else if (input == "dir") {
            // Current pointer has a subfolder child
            cin >> fileFolderName;
            pointer->addChild(new Folder(pointer, fileFolderName));
        } else {
            // Current folder has a file, and we need its size
            int size = stoi(input);
            cin >> fileFolderName;
            pointer->addChild(new File(size, pointer, fileFolderName));
        }
    }

    cout << findTotalOfFolderWithAtMost100000Size(topPointer) << endl;

    return 0;
}

int findTotalOfFolderWithAtMost100000Size(DirectoryEntry* folder) {
    // The same file can be tracked more than once in the case of subfolders
    int total = 0;
    int mySize = folder->size();
    if (mySize <= 100000) {
        // This folder counts
        total += mySize;
    }
    vector<DirectoryEntry*> children = folder->children();
    for (int i = 0; i < children.size(); i++) {
        // Only need folders here
        if (children[i]->isFolder()) {
            // Returns either 0 or its size
            total += findTotalOfFolderWithAtMost100000Size(children[i]);
        }
    }
    return total;
}
