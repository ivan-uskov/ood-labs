#include "../stdafx.h"
#include "insertharmonicdialog.h"
#include "ui_insertharmonicdialog.h"
#include "../model/iharmonicfactory.h"
#include "../model/iharmonic.h"
#include "../model/anglefunction.h"

InsertHarmonicDialog::InsertHarmonicDialog(const shared_ptr<IHarmonicFactory> & factory, QWidget * parent)
    : QDialog(parent)
    , m_ui(new Ui::InsertHarmonicDialog)
{
    m_ui->setupUi(this);

    initializeHarmonic(factory);
}

void InsertHarmonicDialog::accept()
{
    emit harmonicReady(m_harmonic);
    QDialog::accept();
}

void InsertHarmonicDialog::initializeHarmonic(const shared_ptr<IHarmonicFactory> & factory)
{
    m_harmonic = factory->Create(
        m_ui->amplitudeField->value(),
        m_ui->frequencyField->value(),
        m_ui->phaseField->value()
    );

    connect(m_ui->amplitudeField, SIGNAL(valueChanged(double)), m_harmonic.get(), SLOT(setAmplitude(double)));
    connect(m_ui->frequencyField, SIGNAL(valueChanged(double)), m_harmonic.get(), SLOT(setFrequency(double)));
    connect(m_ui->phaseField, SIGNAL(valueChanged(double)), m_harmonic.get(), SLOT(setPhase(double)));
    connect(m_ui->functionField, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(updateHarmonicFunction(const QString &)));
    connect(m_harmonic.get(), SIGNAL(updated()), this, SLOT(updateHarmonicTextView()));

    updateHarmonicTextView();
}

void InsertHarmonicDialog::updateHarmonicTextView()
{
    m_ui->harmonicTextView->setText(m_harmonic->getText());
}

void InsertHarmonicDialog::updateHarmonicFunction(const QString & functionStr)
{
    AngleFunction func(functionStr);
    if (func.isValid())
    {
        m_harmonic->setFunction(func);
    }
}
