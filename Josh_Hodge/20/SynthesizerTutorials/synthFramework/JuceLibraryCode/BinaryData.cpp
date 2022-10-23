/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#include <cstring>

namespace BinaryData
{

//================== README.md ==================
static const unsigned char temp_binary_data_0[] =
"# PolyBLEP Oscillator\n"
"C++ port of the [PolyBLEP oscillator by Tale](http://www.taletn.com/reaper/mono_synth/).\n"
"\n"
"Includes a wrapper (`PolyBLEPStk`) to use the oscillator with components from [The Synthesis Toolkit](https://ccrma.stanford.edu/software/stk/index.html). To use it with [JUCE](http://juce.com), install the [stk_module](https://github.com/drowaudio/s"
"tk_module).\n"
"\n"
"## License\n"
"```\n"
"This software is provided 'as-is', without any express or implied\n"
"warranty.  In no event will the authors be held liable for any damages\n"
"arising from the use of this software.\n"
"\n"
"Permission is granted to anyone to use this software for any purpose,\n"
"including commercial applications, and to alter it and redistribute it\n"
"freely, subject to the following restrictions:\n"
"\n"
"1. The origin of this software must not be misrepresented; you must not\n"
"   claim that you wrote the original software. If you use this software\n"
"   in a product, an acknowledgment in the product documentation would be\n"
"   appreciated but is not required.\n"
"2. Altered source versions must be plainly marked as such, and must not be\n"
"   misrepresented as being the original software.\n"
"3. This notice may not be removed or altered from any source distribution.\n"
"```\n";

const char* README_md = (const char*) temp_binary_data_0;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes);
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;

    if (resourceNameUTF8 != nullptr)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x64791dc8:  numBytes = 1213; return README_md;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "README_md"
};

const char* originalFilenames[] =
{
    "README.md"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
        if (strcmp (namedResourceList[i], resourceNameUTF8) == 0)
            return originalFilenames[i];

    return nullptr;
}

}
