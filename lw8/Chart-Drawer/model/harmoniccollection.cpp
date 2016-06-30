#include "stdafx.h"
#include "harmoniccollection.h"
#include <QModelIndex>

using namespace std;

int HarmonicCollection::rowCount(const QModelIndex &) const
{
    return static_cast<int>(m_harmonics.size());
}

QVariant HarmonicCollection::data(const QModelIndex &index, int role) const
{
    if (index.row() >= m_harmonics.size())
    {
        return QVariant();
    }

    switch (role)
    {
        case Qt::DisplayRole:
        case Qt::EditRole:
            return m_harmonics.at(index.row())->getText();
    default:
        return QVariant();
    }
}

double HarmonicCollection::operator () (double x) const
{
    return accumulate(m_harmonics.begin(), m_harmonics.end(), 0.0, [x](double acc, const std::shared_ptr<IHarmonic> & item){
        return acc + (*item)(x);
    });
}

void HarmonicCollection::addHarmonic(const shared_ptr<IHarmonic> & harmonic)
{
    emit layoutAboutToBeChanged();
    m_harmonics.push_back(harmonic);
    emit layoutChanged();
}

void HarmonicCollection::removeHarmonic(size_t index)
{
    auto it = m_harmonics.begin() + index;
    if (it < m_harmonics.end())
    {
        emit layoutAboutToBeChanged();
        m_harmonics.erase(it);
        emit layoutChanged();
    }
}

std::shared_ptr<IHarmonic> HarmonicCollection::getHarmonic(size_t index) const
{
    auto it = m_harmonics.begin() + index;
    if (it < m_harmonics.end())
    {
        return *it;
    }

    return nullptr;
}
