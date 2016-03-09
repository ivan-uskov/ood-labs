#pragma once

struct IFlyBehavior
{
    virtual ~IFlyBehavior() = default;
    virtual void Fly() = 0;
};

struct FlyWithCountingDepartures : IFlyBehavior
{
    void Fly() override;

protected:
    size_t getDeparturesCount() const;

private:
    size_t m_departuresCount = 0;
};

struct FlyWithWings : public FlyWithCountingDepartures
{
    void Fly() override;
};

struct FlyNoWay : public IFlyBehavior
{
    void Fly() override {}
};
