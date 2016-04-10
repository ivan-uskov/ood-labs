#include "FileInputStream.h"
#include "FileOutputStream.h"
#include "MemoryInputStream.h"
#include "MemoryOutputStream.h"
#include "VectorMemoryStream.h"
#include "DecoratorCreators.h"

using namespace std;

void CopyFiles(int argc, char ** argv)
{
    auto fileNamePtr = argv + argc - 1;
    unique_ptr<IOutputDataStream> outFile = make_unique<CFileOutputStream>(*(fileNamePtr--));
    unique_ptr<IInputDataStream> inFile = make_unique<CFileInputStream>(*fileNamePtr);

    vector<string> args(argv + 1, fileNamePtr);
    inFile = DecoratorCreators::Decorate(args, move(inFile));

    while (!inFile->IsEOF())
    {
        outFile->WriteByte(inFile->ReadByte());
    }
}

int main(int argc, char ** argv)
{
    if (argc < 2)
    {
        cerr << "Error: input output files not specified" << endl;
        return 1;
    }

    try
    {
        CopyFiles(argc, argv);
    }
    catch (exception const& e)
    {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}