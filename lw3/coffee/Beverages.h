#pragma once

#include "IBeverage.h"
#include "BeverageQuantity.h"
#include "BeverageType.h"
#include "BeverageCostProvider.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
    CBeverage(const std::string & description)
        : m_description(description)
    {}

    std::string GetDescription() const override final
    {
        return m_description;
    }

    double GetCost() const override final
    {
        return BeverageCostProvider::GetBaseBeverageCost(GetType(), m_quantity);
    }

    void SetQuantity(const BeverageQuantity & quantity)
    {
        m_quantity = quantity;
    }

protected:
    virtual BeverageType GetType() const = 0;

private:
    std::string m_description;
    BeverageQuantity m_quantity = BeverageQuantity::Standard;
};

// Кофе
class CCoffee : public CBeverage
{
public:
    CCoffee(const std::string & description = "Coffee")
        : CBeverage(description)
    {}

protected:
    BeverageType GetType() const override
    {
        return BeverageType::Coffee;
    }
};

// Капуччино
class CCapuccino : public CCoffee
{
public:
    CCapuccino()
        : CCoffee("Capuccino")
    {}

protected:
    BeverageType GetType() const override
    {
        return BeverageType::Cappuchino;
    }
};

// Латте
class CLatte : public CCoffee
{
public:
    CLatte()
        : CCoffee("Latte")
    {}

protected:
    BeverageType GetType() const override
    {
        return BeverageType::Latte;
    }
};

// Чай
class CTea : public CBeverage
{
public:
    CTea()
        : CBeverage("Tea")
    {}

protected:
    BeverageType GetType() const override
    {
        return BeverageType::Tea;
    }
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
    CMilkshake()
        : CBeverage("Milkshake")
    {}

protected:
    BeverageType GetType() const override
    {
        return BeverageType::Milkshake;
    }
};
