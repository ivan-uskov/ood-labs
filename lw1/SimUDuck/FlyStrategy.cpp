#include "stdafx.h"
#include "FlyStrategy.h"

using namespace std;

void FlyWithWings::Fly()
{
    FlyWithCountingDepartures::Fly();
    cout << "I'm flying with wings for "<< getDeparturesCount() << " times!!" << endl;
}

void FlyWithCountingDepartures::Fly()
{
    ++m_departuresCount;
}

size_t FlyWithCountingDepartures::getDeparturesCount() const
{
    return m_departuresCount;
}
