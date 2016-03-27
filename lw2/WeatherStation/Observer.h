#pragma once

#include <memory>
#include <exception>

#include "boost\multi_index\ordered_index.hpp"
#include "boost\multi_index\member.hpp"
#include "boost\multi_index\identity.hpp"
#include "boost\multi_index_container.hpp"

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
        auto observersCopy = m_observers;
        auto & orderedObservers = observersCopy.get<1>();
        auto observer = orderedObservers.begin();

        while (observer != orderedObservers.end())
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
    struct ObserverInfo
    {
        std::weak_ptr<ObserverType> ptr;
        unsigned priority;

        bool operator < (ObserverInfo const& rhs) const
        {
            return ptr.lock().get() < rhs.ptr.lock().get();
        }

        bool operator == (ObserverInfo const& rhs) const
        {
            return ptr.lock().get() == rhs.ptr.lock().get();
        }
    };

    boost::multi_index_container<
        ObserverInfo,
        boost::multi_index::indexed_by<
            boost::multi_index::ordered_unique<
                boost::multi_index::identity<ObserverInfo>
            >,
            boost::multi_index::ordered_non_unique<
                boost::multi_index::member<ObserverInfo, unsigned, &ObserverInfo::priority>
            >
        >
    > m_observers;
};