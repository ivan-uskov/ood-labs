﻿#pragma once

#include <set>
#include <vector>
#include <functional>
#include <iostream>
#include <exception>
#include <memory>
#include <algorithm>
#include <iterator>

template <typename T>
class IObserver
{
public:
    virtual void Update(T const& data) = 0;
    virtual ~IObserver() = default;
};

template <typename T>
class IObservable
{
public:
    typedef IObserver<T> ObserverType;

    virtual ~IObservable() = default;
    virtual void NotifyObservers() = 0;
    virtual void RegisterObserver(std::shared_ptr<ObserverType> const& observer, unsigned priority = 0) = 0;
    virtual void RemoveObserver(std::shared_ptr<ObserverType> const& observer) = 0;
};

template <typename T>
class Observable : public IObservable<T>
{
public:
    void RegisterObserver(std::shared_ptr<ObserverType> const& observer, unsigned priority = 0) override
    {
        if (!observer)
        {
            throw std::invalid_argument("Empty observer!");
        }

        m_observers.insert({ observer, priority });
    }

    void NotifyObservers() override
    {
        T data = GetChangedData();
        auto observers = GetObserversOrderedByPriority();
        auto observer = observers.begin();

        while (observer != observers.end())
        {
            auto current = (observer++)->ptr.lock();
            if (current)
            {
                current->Update(data);
            }
        }
    }

    void RemoveObserver(std::shared_ptr<ObserverType> const& observer) override
    {
        if (!observer)
        {
            throw std::invalid_argument("Empty observer!");
        }

        m_observers.erase({ observer, 0 });
    }

protected:
    virtual T GetChangedData() const = 0;

private:
    auto GetObserversOrderedByPriority()
    {
        std::vector<ObserverInfo> observers;
        std::copy(m_observers.begin(), m_observers.end(), std::back_inserter(observers));
        std::sort(observers.begin(), observers.end(), [](auto const& lhs, auto const& rhs) {
            return lhs.priority > rhs.priority;
        });

        return observers;
    }

    struct ObserverInfo
    {
        std::weak_ptr<ObserverType> ptr;
        unsigned priority;
    };

    struct ObserverInfoCompare
    {
        bool operator() (ObserverInfo const& lhs, ObserverInfo const& rhs) const
        {
            return lhs.ptr.lock().get() < rhs.ptr.lock().get();
        }
    };

    std::set<ObserverInfo, ObserverInfoCompare> m_observers;
};