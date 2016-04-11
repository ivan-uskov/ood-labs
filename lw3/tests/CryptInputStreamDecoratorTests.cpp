#include "stdafx.h"
#include <functional>

#include "../streams/EncryptInputStreamDecorator.h"
#include "../streams/DecryptInputStreamDecorator.h"
#include "../streams/FileInputStream.h"

using namespace std;
using namespace std::placeholders;

namespace
{
    auto CreateEncryptInputStream(unsigned seed, const string & fileName)
    {
        return make_unique<CEncryptInputStreamDecorator>(make_unique<CFileInputStream>(fileName), seed);
    }

    auto CreateDecryptInputStream(unsigned seed, const string & fileName)
    {
        return make_unique<CDecryptInputStreamDecorator>(make_unique<CFileInputStream>(fileName), seed);
    }

    void CheckReadByte(function<unique_ptr<IInputDataStream>(string const&)> const& decoratorCreator, function<uint8_t(uint8_t)> replacer)
    {
        string bytes("0123456789");
        {
            ofstream("not_existing_file") << bytes;
        }

        auto in = decoratorCreator("not_existing_file");
        BOOST_CHECK_EQUAL(in->IsEOF(), false);

        std::for_each(bytes.begin(), bytes.end(), [&](auto & currChar) {
            uint8_t byte = in->ReadByte();
            BOOST_CHECK_EQUAL(byte, replacer(currChar));
        });

        BOOST_CHECK_EQUAL(in->IsEOF(), true);

        remove("not_existing_file");
    }

    void CheckReadBlock(function<unique_ptr<IInputDataStream>(string const&)> const& decoratorCreator, function<uint8_t(uint8_t)> replacer)
    {
        string bytes("0123456789");
        {
            ofstream("not_existing_file") << bytes;
        }

        std::array<uint8_t, 10> myBlock;

        {
            auto in = decoratorCreator("not_existing_file");
            BOOST_CHECK_EQUAL(in->IsEOF(), false);

            streamsize redCount;
            BOOST_CHECK_NO_THROW(redCount = in->ReadBlock(myBlock.data(), 5));
            BOOST_CHECK_EQUAL(redCount, 5);
            BOOST_CHECK_EQUAL(in->IsEOF(), false);

            BOOST_CHECK_NO_THROW(redCount = in->ReadBlock(myBlock.data() + 5, 5));
            BOOST_CHECK_EQUAL(redCount, 5);
            BOOST_CHECK_EQUAL(in->IsEOF(), true);
        }

        remove("not_existing_file");

        for (size_t i = 0; i < myBlock.size(); ++i)
        {
            BOOST_CHECK_EQUAL(myBlock[i], replacer(bytes[i]));
        }
    }
}

BOOST_AUTO_TEST_SUITE(EncryptInputStreamTests)

BOOST_AUTO_TEST_CASE(CheckReadByteEncrypted)
{
    unsigned seed = static_cast<unsigned>(rand());
    CNumberReplacementTable<uint8_t> table(seed);

    CheckReadByte(bind(CreateEncryptInputStream, seed, _1), bind(&CNumberReplacementTable<uint8_t>::replace, ref(table), _1));
}

BOOST_AUTO_TEST_CASE(CheckReadBlockEncrypted)
{
    unsigned seed = static_cast<unsigned>(rand());
    CNumberReplacementTable<uint8_t> table(seed);

    CheckReadBlock(bind(CreateEncryptInputStream, seed, _1), bind(&CNumberReplacementTable<uint8_t>::replace, ref(table), _1));
}

BOOST_AUTO_TEST_CASE(CheckReadByteDecrypted)
{
    unsigned seed = static_cast<unsigned>(rand());
    CNumberReplacementTable<uint8_t> table(seed);

    CheckReadByte(bind(CreateDecryptInputStream, seed, _1), bind(&CNumberReplacementTable<uint8_t>::unreplace, ref(table), _1));
}

BOOST_AUTO_TEST_CASE(CheckReadBlockDecrypted)
{
    unsigned seed = static_cast<unsigned>(rand());
    CNumberReplacementTable<uint8_t> table(seed);

    CheckReadBlock(bind(CreateDecryptInputStream, seed, _1), bind(&CNumberReplacementTable<uint8_t>::unreplace, ref(table), _1));
}

BOOST_AUTO_TEST_SUITE_END()