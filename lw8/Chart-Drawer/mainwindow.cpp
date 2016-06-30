#include "stdafx.h"
#include "mainwindow.h"
#include "dialog/insertharmonicdialog.h"
#include <QDebug>

MainWindow::MainWindow(QWidget * parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow())
    , m_harmonics(new HarmonicCollection())
    , m_factory(new HarmonicFactory())
    , m_provider(new HarmonicPlotItemsProvider(Math::Range(-5, 5), 0.05))
{
    m_ui->setupUi(this);
    initializeItems();
}

void MainWindow::initializeItems()
{
    initializePlot();

    m_ui->harmonicsList->setModel(m_harmonics.get());
    m_provider->setGenerator(m_harmonics);

    connect(m_ui->harmonicsList, &QListView::pressed, this, &MainWindow::updateCurrentHarmonic);
    connect(m_ui->addItemButton, SIGNAL(released()), this, SLOT(runAddItemDialog()));
    connect(m_ui->deleteItemButton, SIGNAL(released()), this, SLOT(removeCurrentHarmonic()));
    connect(m_provider.get(), SIGNAL(regenerated(HarmonicItems)), this, SLOT(updatePlot(const HarmonicItems &)));
    connect(m_harmonics.get(), &HarmonicCollection::layoutChanged, m_provider.get(), &HarmonicPlotItemsProvider::regenerate);
}

void MainWindow::initializePlot()
{
    m_ui->plot->xAxis->setLabel("x");
    m_ui->plot->yAxis->setLabel("y");
    m_ui->plot->addGraph();
    m_ui->plot->graph(0)->setPen(QPen(Qt::blue));
    m_ui->plot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    m_ui->plot->graph(0)->setAntialiasedFill(true);
}

void MainWindow::updatePlot(const HarmonicItems & items)
{
    m_ui->plot->xAxis->setRange(items.xRange.from(), items.xRange.to());
    m_ui->plot->yAxis->setRange(items.yRange.from(), items.yRange.to());
    m_ui->plot->graph(0)->setData(items.xs, items.ys);
    m_ui->plot->replot();
}

void MainWindow::runAddItemDialog()
{
    auto dialog = make_unique<InsertHarmonicDialog>(m_factory, this);
    connect(dialog.get(), &InsertHarmonicDialog::harmonicReady, m_harmonics.get(), &HarmonicCollection::addHarmonic);
    dialog->exec();
}

void MainWindow::updateCurrentHarmonic(const QModelIndex & index)
{
    m_currentHarmonicIndex = index;
}

void MainWindow::removeCurrentHarmonic()
{
    if (m_currentHarmonicIndex.isValid())
    {
        m_harmonics->removeHarmonic(m_currentHarmonicIndex.row());
        m_currentHarmonicIndex = QModelIndex();
    }
}
