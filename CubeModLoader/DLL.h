#ifndef DLL_H
#define DLL_H
#include <iostream>
#include <windows.h>
#include "CWSDK/cwsdk.h"

class DLL
{
    public:
        std::string fileName;
        HMODULE handle;

        FARPROC ModPreInitialize;
        FARPROC ModMajorVersion;
        FARPROC ModMinorVersion;
		FARPROC MakeMod;

		GenericMod* mod;

        DLL(std::string fileName);
        HMODULE Load();
        virtual ~DLL();

    protected:

    private:
};

#endif // DLL_H
