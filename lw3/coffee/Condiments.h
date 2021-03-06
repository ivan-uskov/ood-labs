﻿#pragma once

#include "IBeverage.h"
#include <algorithm>

// Базовый декоратор "Добавка к напитку". Также является напитком
class CCondimentDecorator : public IBeverage
{
public:
    std::string GetDescription()const override
    {
        return m_beverage->GetDescription() + ", " + GetCondimentDescription();
    }

    double GetCost()const override
    {
        return m_beverage->GetCost() + GetCondimentCost();
    }

    virtual std::string GetCondimentDescription()const = 0;
    virtual double GetCondimentCost()const = 0;
protected:
    CCondimentDecorator(IBeveragePtr && beverage)
        : m_beverage(move(beverage))
    {}
private:
    IBeveragePtr m_beverage;
};

// Добавка из корицы
class CCinnamon : public CCondimentDecorator
{
public:
    CCinnamon(IBeveragePtr && beverage)
        : CCondimentDecorator(move(beverage))
    {}
protected:
    double GetCondimentCost()const override
    {
        return 20;
    }

    std::string GetCondimentDescription()const override
    {
        return "Cinnamon";
    }
};

// Лимонная добавка
class CLemon : public CCondimentDecorator
{
public:
    CLemon(IBeveragePtr && beverage, unsigned quantity = 1)
        : CCondimentDecorator(move(beverage))
        , m_quantity(quantity)
    {}
protected:
    double GetCondimentCost()const override
    {
        return 10 * m_quantity;
    }
    std::string GetCondimentDescription()const override
    {
        return "Lemon x " + std::to_string(m_quantity);
    }
private:
    unsigned m_quantity;
};


enum class IceCubeType
{
    Dry,    // Сухой лед (для суровых сибирских мужиков)
    Water   // Обычные кубики из воды
};

// Добавка "Кубики льда". Определяется типом и количеством кубиков, что влияет на стоимость
// и описание
class CIceCubes : public CCondimentDecorator
{
public:
    CIceCubes(IBeveragePtr && beverage, unsigned quantity, IceCubeType type = IceCubeType::Water)
        : CCondimentDecorator(move(beverage))
        , m_quantity(quantity)
        , m_type(type)
    {}
protected:
    double GetCondimentCost()const override
    {
        // Чем больше кубиков, тем больше стоимость.
        // Сухой лед стоит дороже
        return (m_type == IceCubeType::Dry ? 10 : 5) * m_quantity;
    }
    std::string GetCondimentDescription()const override
    {
        return std::string(m_type == IceCubeType::Dry ? "Dry" : "Water")
            + " ice cubes x " + std::to_string(m_quantity);
    }
private:
    unsigned m_quantity;
    IceCubeType m_type;
};

// Тип сиропа
enum class SyrupType
{
    Chocolate,	// Шоколадный
    Maple,		// Кленовый
};

// Добавка "Сироп"
class CSyrup : public CCondimentDecorator
{
public:
    CSyrup(IBeveragePtr && beverage, SyrupType syrupType)
        : CCondimentDecorator(move(beverage))
        , m_syrupType(syrupType)
    {}
protected:
    double GetCondimentCost()const override
    {
        return 15;
    }
    std::string GetCondimentDescription()const override
    {
        return std::string(m_syrupType == SyrupType::Chocolate ? "Chocolate" : "Maple")
            + " syrup";
    }
private:
    SyrupType m_syrupType;
};

// Шоколадная крошка
class CChocolateCrumbs : public CCondimentDecorator
{
public:
    CChocolateCrumbs(IBeveragePtr && beverage, unsigned mass)
        :CCondimentDecorator(move(beverage))
        , m_mass(mass)
    {
    }

    double GetCondimentCost()const override
    {
        return 2 * m_mass;
    }

    std::string GetCondimentDescription()const override
    {
        return "Chocolate crumbs " + std::to_string(m_mass) + "g";
    }
private:
    unsigned m_mass;
};

// Кокосовая стружка
class CCoconutFlakes : public CCondimentDecorator
{
public:
    CCoconutFlakes(IBeveragePtr && beverage, unsigned mass)
        : CCondimentDecorator(move(beverage))
        , m_mass(mass)
    {}

protected:
    double GetCondimentCost()const override
    {
        return 1 * m_mass;
    }
    std::string GetCondimentDescription()const override
    {
        return "Coconut flakes " + std::to_string(m_mass) + "g";
    }
private:
    unsigned m_mass;
};

class CCream : public CCondimentDecorator
{
public:
    CCream(IBeveragePtr && beverage, unsigned volume)
        : CCondimentDecorator(move(beverage))
        , m_volume(volume)
    {}

protected:
    double GetCondimentCost()const override
    {
        return 25;
    }
    std::string GetCondimentDescription()const override
    {
        return "Cream " + std::to_string(m_volume) + "ml";
    }
private:
    unsigned m_volume;
};

class CChocolatePices : public CCondimentDecorator
{
public:
    CChocolatePices(IBeveragePtr && beverage, unsigned pices)
        : CCondimentDecorator(move(beverage))
        , m_pices(std::min(pices, 5u))
    {}

protected:
    double GetCondimentCost()const override
    {
        return m_pices * 10;
    }
    std::string GetCondimentDescription()const override
    {
        return "Chocolate " + std::to_string(m_pices) + " pices";
    }
private:
    unsigned m_pices;
};

enum class LiquorType
{
    Walnut,
    Chocolate
};

class CLiquor : public CCondimentDecorator
{
public:
    CLiquor(IBeveragePtr && beverage, LiquorType const& type = LiquorType::Walnut)
        : CCondimentDecorator(move(beverage))
        , m_type(type)
    {}

protected:
    double GetCondimentCost()const override
    {
        return 30;
    }
    std::string GetCondimentDescription()const override
    {
        return (m_type == LiquorType::Chocolate ? "Walnut" : "Chocolate") + std::string(" liquor");
    }
private:
    LiquorType m_type;
};

