#include "FileInputStream.h"
#include "FileOutputStream.h"
#include "MemoryInputStream.h"
#include "MemoryOutputStream.h"
#include "VectorMemoryStream.h"

using namespace std;

int main()
{
    CVectorMemoryStream memory;
    CMemoryOutputStream out(memory);
    out.WriteByte(1);
    out.WriteByte(2);
    out.WriteByte(3);

    for (int i = 0; i < memory.Size(); ++i)
    {
        cout << static_cast<int>(memory[i]);
    }

    return 0;
}