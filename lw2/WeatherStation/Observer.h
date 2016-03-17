#pragma once

#include <set>
#include <vector>
#include <functional>
#include <iostream>
#include <exception>
#include <memory>
#include <algorithm>

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
    virtual void RegisterObserver(std::shared_ptr<ObserverType> const& observer) = 0;
    virtual void NotifyObservers() = 0;
    virtual void RemoveObserver(std::shared_ptr<ObserverType> const& observer) = 0;
};

template <typename T>
class Observable : public IObservable<T>
{
public:
    void RegisterObserver(std::shared_ptr<ObserverType> const& observer) override
    {
        if (!observer)
        {
            throw std::invalid_argument("Empty observer!");
        }

        m_observers.insert(observer);
    }

    void NotifyObservers() override
    {
        T data = GetChangedData();
        auto observer = m_observers.begin();
        while (observer != m_observers.end())
        {
            if (observer->expired())
            {
                auto observerToBeDeleted = observer++;
                m_observers.erase(observerToBeDeleted);
            }
            else
            {
                observer->lock()->Update(data);
                ++observer;
            }
        }
    }

    void RemoveObserver(std::shared_ptr<ObserverType> const& observer) override
    {
        if (!observer)
        {
            throw std::invalid_argument("Empty observer!");
        }

        m_observers.erase(observer);
    }

protected:
    virtual T GetChangedData() const = 0;

private:
    typedef std::weak_ptr<ObserverType> ObserverInfo;

    struct ObserverInfoLess
    {
        bool operator() (ObserverInfo const& lhs, ObserverInfo const& rhs) const
        {
            return lhs.lock().get() < rhs.lock().get();
        }
    };

    std::set<ObserverInfo, ObserverInfoLess> m_observers;
};