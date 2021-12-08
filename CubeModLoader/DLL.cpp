#include "DLL.h"
#include <iostream>

DLL::DLL(std::string fileName) {
    this->fileName = fileName;
    this->handle = nullptr;
    this->enabled = true;
}

HMODULE DLL::Load() {
    this->handle = LoadLibraryA(this->fileName.c_str());
    if (!this->handle) {
        printf("Could not load %s: %ld\n", this->fileName.c_str(), GetLastError());
        exit(1);
    }
    return this->handle;
}

DLL::~DLL() {
    //dtor
}
