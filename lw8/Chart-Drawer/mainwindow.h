#pragma once
#include "ui_mainwindow.h"
#include "model/harmoniccollection.h"
#include "model/harmonicfactory.h"
#include "model/harmonicplotitemsprovider.h"
#include <QMainWindow>
#include <QModelIndex>
#include <memory>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget * parent = 0);

private slots:
    void runAddItemDialog();
    void updateCurrentHarmonic(const QModelIndex &);
    void removeCurrentHarmonic();
    void updatePlot(const HarmonicItems & items);

private:
    void initializeItems();

    std::shared_ptr<HarmonicFactory> m_factory;
    std::unique_ptr<HarmonicCollection> m_harmonics;
    std::unique_ptr<HarmonicPlotItemsProvider> m_provider;
    std::unique_ptr<Ui::MainWindow> m_ui;
    QModelIndex m_currentHarmonicIndex;

    size_t m_plotXSize = 200;
    size_t m_plotTSize = 150;
};
