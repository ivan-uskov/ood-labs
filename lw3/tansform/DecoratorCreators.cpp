#include "stdafx.h"
#include "DecoratorCreators.h"

#include "../streams/DecryptInputStreamDecorator.h"
#include "../streams/EncryptInputStreamDecorator.h"

#include <boost/lexical_cast.hpp>

using namespace std;

namespace
{
    size_t StringToNumber(string const& str)
    {
        try
        {
            return boost::lexical_cast<size_t>(str);
        }
        catch (boost::bad_lexical_cast const&)
        {
            return 0;
        }
    }
}

namespace DecoratorCreators
{

    bool CCryptDecoratorCreator::AddValue(string const& arg)
    {
        if (!m_hasArgName)
        {
            m_hasArgName = (arg == m_argName);
        }
        else
        {
            m_seed = StringToNumber(arg);
            if (!m_seed)
            {
                throw invalid_argument("Seed expected");
            }
        }

        return m_hasArgName;
    }

    bool CCryptDecoratorCreator::IsValid() const
    {
        return !m_hasArgName && !m_seed;
    }

    bool CCryptDecoratorCreator::CanDecorate() const
    {
        return m_hasArgName && m_seed;
    }

    CCryptDecoratorCreator::CCryptDecoratorCreator(string && m_argName)
        : m_argName(move(m_argName))
    {}

    unique_ptr<IInputDataStream> CCryptDecoratorCreator::Decorate(unique_ptr<IInputDataStream> && stream)
    {
        auto decoratedStream = CreateDecorator(move(stream), m_seed);

        m_seed = 0;
        m_hasArgName = false;

        return move(decoratedStream);
    }

    unique_ptr<IInputDataStream> CEncryptDecoratorCreator::CreateDecorator(unique_ptr<IInputDataStream> && stream, size_t seed)
    {
        return make_unique<CEncryptInputStreamDecorator>(move(stream), static_cast<unsigned>(seed));
    }

    unique_ptr<IInputDataStream> CDecryptDecoratorCreator::CreateDecorator(unique_ptr<IInputDataStream> && stream, size_t seed)
    {
        return make_unique<CDecryptInputStreamDecorator>(move(stream), static_cast<unsigned>(seed));
    }

    vector<unique_ptr<IDecoratorCreator>> CreateDecoratorCreators()
    {
        unique_ptr<IDecoratorCreator> encryptDecoratorCreator = make_unique<CEncryptDecoratorCreator>();
        unique_ptr<IDecoratorCreator> decryptDecoratorCreator = make_unique<CDecryptDecoratorCreator>();

        vector<unique_ptr<IDecoratorCreator>> decoratorCreators;
        decoratorCreators.push_back(move(encryptDecoratorCreator));
        decoratorCreators.push_back(move(decryptDecoratorCreator));

        return move(decoratorCreators);
    }

    void CheckDecoratorCreatorsValid(vector<unique_ptr<IDecoratorCreator>> const& decoratorCreators)
    {
        auto notValidCreator = std::find_if(decoratorCreators.begin(), decoratorCreators.end(), [](auto const& creator) {
            return !creator->IsValid();
        });

        if (notValidCreator != decoratorCreators.end())
        {
            throw invalid_argument("Failed to parse arguments!");
        }
    }

    unique_ptr<IInputDataStream> Decorate(vector<string> args, unique_ptr<IInputDataStream> && stream)
    {
        auto decoratorCreators = CreateDecoratorCreators();

        for (auto currArg = args.begin(); currArg != args.end(); ++currArg)
        {
            for (auto currCreator = decoratorCreators.begin(); currCreator != decoratorCreators.end(); ++currCreator)
            {
                if ((*currCreator)->AddValue(*currArg))
                {
                    if ((*currCreator)->CanDecorate())
                    {
                        stream = (*currCreator)->Decorate(move(stream));
                    }
                }
            }
        }

        CheckDecoratorCreatorsValid(decoratorCreators);

        return move(stream);
    }
}