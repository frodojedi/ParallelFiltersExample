/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   exciter_wav;
    const int            exciter_wavSize = 13942;

    extern const char*   preset1_xml;
    const int            preset1_xmlSize = 1284;

    extern const char*   preset2_xml;
    const int            preset2_xmlSize = 1278;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 3;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
