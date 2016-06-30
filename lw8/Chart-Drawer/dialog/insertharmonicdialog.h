#pragma once
#include <QDialog>
#include <memory>

class IHarmonicFactory;
class IHarmonic;

namespace Ui
{
    class InsertHarmonicDialog;
}

class InsertHarmonicDialog : public QDialog
{
    Q_OBJECT
public:
    explicit InsertHarmonicDialog(const std::shared_ptr<IHarmonicFactory> & factory, QWidget * parent = 0);

signals:
    void harmonicReady(std::shared_ptr<IHarmonic> const& harmonic);

public slots:
    void accept() override;

private slots:
    void updateHarmonicTextView();
    void updateHarmonicFunction(const QString & functionStr);

private:
    void initializeHarmonic(const std::shared_ptr<IHarmonicFactory> & factory);

    std::unique_ptr<Ui::InsertHarmonicDialog> m_ui;
    std::shared_ptr<IHarmonic> m_harmonic;
};
