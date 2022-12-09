#include <iostream>
#include "directoryEntry.hpp"
#include "file.hpp"
#include "folder.hpp"

using namespace std;

const int MAXIMUM_SIZE = 70000000;
const int NEEDED_SPACE = 30000000;

int smallestFolderThatHasTargetSize(DirectoryEntry* folder, int targetSize);

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

    int usedSize = topPointer->size();
    int targetSizeToRemove = usedSize - (MAXIMUM_SIZE - NEEDED_SPACE);

    cout << smallestFolderThatHasTargetSize(topPointer, targetSizeToRemove) << endl;

    return 0;
}

int smallestFolderThatHasTargetSize(DirectoryEntry* folder, int targetSize) {
    int size = folder->size();
    if (size < targetSize) {
        // If this folder is too small, any folders it contains are also too small
        return -1;
    }
    vector<DirectoryEntry*> children = folder->children();
    int sizeToReturn = -1;
    // Find the smallest subfolder that still meets the target size
    for (int i = 0; i < children.size(); i++) {
        if (children[i]->isFolder()) {
            int subFolderSize = smallestFolderThatHasTargetSize(children[i], targetSize);
            if (subFolderSize > -1 && (subFolderSize < sizeToReturn || sizeToReturn == -1)) {
                // Found either a first smallest, or the new smallest
                sizeToReturn = subFolderSize;
            }
        }
    }
    if (sizeToReturn > -1) {
        // Child folder fits the bill and will never be bigger than this folder
        return sizeToReturn;
    }
    // No children fit the bill, so return this folder's own size
    return size;
}
