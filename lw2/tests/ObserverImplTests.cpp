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

BOOST_AUTO_TEST_SUITE_END()