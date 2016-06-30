#pragma once
#include <QObject>
#include <memory>
#include "iharmonic.h"
#include <QAbstractListModel>

class HarmonicCollection : public QAbstractListModel, public IDecartesSpaceDrawable
{
    Q_OBJECT
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    double operator () (double x) const override;
    std::shared_ptr<IHarmonic> getHarmonic(size_t index) const;

public slots:
    void addHarmonic(const std::shared_ptr<IHarmonic> & harmonic);
    void removeHarmonic(size_t index);

private:
    std::vector<std::shared_ptr<IHarmonic>> m_harmonics;
};
