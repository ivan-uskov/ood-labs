#pragma once

#include "../streams/IInputDataStream.h"
#include "../streams/IOutputDataStream.h"

#include <vector>
#include <memory>
#include <string>

namespace DecoratorCreators
{
    class IDecoratorCreator
    {
    public:
        virtual bool IsValid() const = 0;
        virtual bool CanDecorate() const = 0;
        virtual bool AddValue(std::string const& arg) = 0;
        virtual std::unique_ptr<IInputDataStream> Decorate(std::unique_ptr<IInputDataStream> && stream) = 0;

        virtual ~IDecoratorCreator() = default;
    };

    class CDecompressDecoratorCreator : public IDecoratorCreator
    {
    public:
        bool AddValue(std::string const& arg) override;
        bool IsValid() const override;
        bool CanDecorate() const override;
        std::unique_ptr<IInputDataStream> Decorate(std::unique_ptr<IInputDataStream> && stream) override;

    private:
        bool m_argFetched = false;
    };

    class CCryptDecoratorCreator : public IDecoratorCreator
    {
    public:
        bool AddValue(std::string const& arg) override;
        bool IsValid() const override;
        bool CanDecorate() const override;
        std::unique_ptr<IInputDataStream> Decorate(std::unique_ptr<IInputDataStream> && stream) override;

    protected:
        CCryptDecoratorCreator(std::string && m_argName);
        virtual std::unique_ptr<IInputDataStream> CreateDecorator(std::unique_ptr<IInputDataStream> && stream, size_t seed) = 0;

    private:
        bool m_hasArgName = false;
        size_t m_seed = 0;
        std::string const m_argName;
    };

    class CEncryptDecoratorCreator : public CCryptDecoratorCreator
    {
    public:
        CEncryptDecoratorCreator()
            : CCryptDecoratorCreator("--encrypt")
        {}

    protected:
        std::unique_ptr<IInputDataStream> CreateDecorator(std::unique_ptr<IInputDataStream> && stream, size_t seed) override;
    };

    class CDecryptDecoratorCreator : public CCryptDecoratorCreator
    {
    public:
        CDecryptDecoratorCreator()
            : CCryptDecoratorCreator("--decrypt")
        {}

    protected:
        std::unique_ptr<IInputDataStream> CreateDecorator(std::unique_ptr<IInputDataStream> && stream, size_t seed) override;
    };

    std::unique_ptr<IInputDataStream> DecorateInputStream(std::vector<std::string> args, std::unique_ptr<IInputDataStream> && stream);
    std::unique_ptr<IOutputDataStream> DecorateOutputStream(std::vector<std::string> args, std::unique_ptr<IOutputDataStream> && stream);
}

