#pragma once

#include <memory>
#include <exception>

#include "boost\multi_index\ordered_index.hpp"
#include "boost\multi_index\member.hpp"
#include "boost\multi_index\identity.hpp"
#include "boost\multi_index_container.hpp"

template <typename T> 
class IObservable;

template <typename T>
class IObserver
{
public:
    typedef IObservable<T> ObservableType;

    virtual void Update(ObservableType const& subject) = 0;
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

    virtual T GetChangedData() const = 0;
    virtual size_t GetObservableId() const = 0;
};

template <typename T>
class Observable : public IObservable<T>
{
public:
    size_t GetObservableId() const override
    {
        return m_observableId;
    }

    void SetObservableId(size_t observableId)
    {
        m_observableId = observableId;
    }

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
        auto observersCopy = m_observers;
        auto & orderedObservers = observersCopy.get<1>();
        auto observer = orderedObservers.begin();

        while (observer != orderedObservers.end())
        {
            auto current = (observer++)->ptr.lock();
            if (current)
            {
                current->Update(*this);
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

    size_t m_observableId = 0;
};