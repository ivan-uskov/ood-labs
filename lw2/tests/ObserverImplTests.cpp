#include "stdafx.h"
#include "../WeatherStation/Observer.h"

using namespace std;

struct CounterObserver : IObserver<int>
{
    void Update(int const& data) override
    {
        ++m_updateCount;
    }

    size_t GetUpdateCount() const
    {
        return m_updateCount;
    }

private:
    size_t m_updateCount = 0;
};

struct EmptySubject : Observable<int>
{
    int GetChangedData() const override
    {
        return 42;
    }
};

struct SelfRemoverObserver : IObserver<int>, std::enable_shared_from_this<SelfRemoverObserver>
{
    SelfRemoverObserver(EmptySubject & subject)
        : m_subject(subject)
    {
    }

    void Update(int const& data) override
    {
        m_subject.RemoveObserver(shared_from_this());
    }
private:
    EmptySubject & m_subject;
};

struct MultiplyingTwoObserver : IObserver<int>
{
    MultiplyingTwoObserver(int & value)
        : m_value(value)
    {
    }

    void Update(int const&) override
    {
        m_value *= 2;
    }
private:
    int & m_value;
};

struct SubstructingOneObserver : IObserver<int>
{
    SubstructingOneObserver(int & value)
        : m_value(value)
    {
    }

    void Update(int const&) override
    {
        m_value -= 1;
    }
private:
    int & m_value;
};

BOOST_AUTO_TEST_SUITE(ObserverImplTests)

BOOST_AUTO_TEST_CASE(CheckRegisterObserver)
{
    EmptySubject subject;
    auto observer = make_shared<CounterObserver>();
    auto emptyObserver = shared_ptr<CounterObserver>();

    BOOST_CHECK_THROW(subject.RegisterObserver(emptyObserver), invalid_argument);
    BOOST_CHECK_NO_THROW(subject.RegisterObserver(observer));
}

BOOST_AUTO_TEST_CASE(CheckRemoveObserver)
{
    EmptySubject subject;
    auto observer = make_shared<CounterObserver>();
    auto emptyObserver = shared_ptr<CounterObserver>();

    subject.RegisterObserver(observer);

    subject.NotifyObservers();
    BOOST_CHECK_EQUAL(observer->GetUpdateCount(), 1);

    BOOST_CHECK_NO_THROW(subject.RemoveObserver(observer));

    subject.NotifyObservers();
    BOOST_CHECK_EQUAL(observer->GetUpdateCount(), 1);

    BOOST_CHECK_THROW(subject.RemoveObserver(emptyObserver), invalid_argument);
}

BOOST_AUTO_TEST_CASE(CheckNotifyObservers)
{
    EmptySubject subject;
    int value = 2;
    auto observer = make_shared<CounterObserver>();
    auto mulObserver = make_shared<MultiplyingTwoObserver>(value);

    subject.RegisterObserver(observer);
    subject.RegisterObserver(mulObserver);

    BOOST_CHECK_NO_THROW(subject.NotifyObservers());

    BOOST_CHECK_EQUAL(observer->GetUpdateCount(), 1);
    BOOST_CHECK_EQUAL(value, 4);

    mulObserver.reset();
    BOOST_CHECK_NO_THROW(subject.NotifyObservers());

    BOOST_CHECK_EQUAL(value, 4);
}

BOOST_AUTO_TEST_CASE(CheckRemoveEmptyObservers)
{
    EmptySubject subject;

    int value = 2;
    auto observer = make_shared<MultiplyingTwoObserver>(value);

    subject.RegisterObserver(observer);

    subject.NotifyObservers();
    BOOST_CHECK_EQUAL(value, 4);

    observer.reset();

    BOOST_CHECK_NO_THROW(subject.NotifyObservers());
    BOOST_CHECK_EQUAL(value, 4);
}

BOOST_AUTO_TEST_CASE(CheckObserverRemoveSelfInUpdate)
{
    EmptySubject subject;

    auto observer = make_shared<SelfRemoverObserver>(subject);

    subject.RegisterObserver(observer);
    BOOST_CHECK_NO_THROW(subject.NotifyObservers());
}

BOOST_AUTO_TEST_CASE(CheckObserversPriorityUpdate)
{
    int value = 0;
    EmptySubject subject;
    auto mulObserver = make_shared<MultiplyingTwoObserver>(value);
    auto subObserver = make_shared<SubstructingOneObserver>(value);

    subject.RegisterObserver(mulObserver, 2);
    subject.RegisterObserver(subObserver, 1);
    subject.NotifyObservers();
    BOOST_CHECK_EQUAL(value, -2);
}

BOOST_AUTO_TEST_CASE(CheckObserverRegisteredOnce)
{
    int value = 0;
    EmptySubject subject;
    auto observer = make_shared<CounterObserver>();
    subject.RegisterObserver(observer);
    subject.RegisterObserver(observer);
    subject.NotifyObservers();
    BOOST_CHECK_EQUAL(observer->GetUpdateCount(), 1);
}

BOOST_AUTO_TEST_SUITE_END()