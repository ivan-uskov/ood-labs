#include "stdafx.h"
#include "../WeatherStation/Observer.h"

using namespace std;

struct FooObserver : IObserver<int>
{
    void Update(int const& data) override
    {
    }
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

struct SumstructingOneObserver : IObserver<int>
{
    SumstructingOneObserver(int & value)
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
    auto observer = make_shared<FooObserver>();
    auto emptyObserver = shared_ptr<FooObserver>();

    BOOST_CHECK_THROW(subject.RegisterObserver(emptyObserver), invalid_argument);
    BOOST_CHECK_NO_THROW(subject.RegisterObserver(observer));
}

BOOST_AUTO_TEST_CASE(CheckRemoveObserver)
{
    EmptySubject subject;
    auto observer = make_shared<FooObserver>();
    auto emptyObserver = shared_ptr<FooObserver>();

    BOOST_CHECK_THROW(subject.RemoveObserver(emptyObserver), invalid_argument);
    BOOST_CHECK_NO_THROW(subject.RemoveObserver(observer));
}

BOOST_AUTO_TEST_CASE(CheckNotifyObservers)
{
    EmptySubject subject;

    auto observer = make_shared<FooObserver>();

    subject.RegisterObserver(observer);
    BOOST_CHECK_NO_THROW(subject.NotifyObservers());
    observer.reset();
    BOOST_CHECK_NO_THROW(subject.NotifyObservers());
}

BOOST_AUTO_TEST_CASE(CheckRemoveEmptyObservers)
{
    EmptySubject subject;

    auto observer = make_shared<FooObserver>();

    subject.RegisterObserver(observer);
    observer.reset();

    BOOST_CHECK_NO_THROW(subject.NotifyObservers());
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
    auto subObserver = make_shared<SumstructingOneObserver>(value);

    subject.RegisterObserver(mulObserver, 1);
    subject.RegisterObserver(subObserver, 2);
    subject.NotifyObservers();
    BOOST_CHECK_EQUAL(value, -2);
}

BOOST_AUTO_TEST_SUITE_END()