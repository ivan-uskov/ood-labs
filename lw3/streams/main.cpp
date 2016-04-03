#include "FileInputStream.h"
#include "FileOutputStream.h"
#include "MemoryInputStream.h"
#include "VectorMemoryStream.h"

using namespace std;

int main()
{
    CVectorMemoryStream memory;
    memory.Add(5);
    memory.Add(4);
    memory.Add(7);
    CMemoryInputStream in(memory);

    while (!in.IsEOF())
    {
        cout << static_cast<int>(in.ReadByte());
    }

    return 0;
}