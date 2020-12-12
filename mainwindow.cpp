#include "mainwindow.h"
#include "ui_mainwindowform.h"
#include "outputwindow.h"
#include "StuffPanel.h"
#include "mysettings.h"

#include <QDockWidget>
#include <QToolBar>
#include <QKeySequence>

QAction * MainWindow::create_doughnut_action()
{
    const QIcon doughnutIcon = QIcon(":myicons/doughnut_64x64.png");
    QAction *doughnutAction = new QAction(doughnutIcon, tr("&Eat Doughnut"), this);
    doughnutAction->setShortcut(QKeySequence{tr("Ctrl+D")});
    doughnutAction->setStatusTip(tr("Eat a doughnut"));
    connect(doughnutAction, &QAction::triggered, this, &MainWindow::eat_doughnut);

    return doughnutAction;
}

QAction * MainWindow::create_settings_action()
{
    const QIcon settingsIcon = QIcon(":myicons/balloons_64x64.png");
    QAction *settingsAction = new QAction(settingsIcon, tr("&Change Settings"), this);
    settingsAction->setShortcut(QKeySequence{tr("Ctrl+B")});
    settingsAction->setStatusTip(tr("Change Settings"));
    connect(settingsAction, &QAction::triggered, this, &MainWindow::update_settings);

    return settingsAction;
}

void MainWindow::create_toolbar()
{
    QToolBar *toolBar = addToolBar(tr("My actions"));
    QAction *doughnutAction = create_doughnut_action();
    toolBar->addAction(doughnutAction);
    QAction *settingsAction = create_settings_action();
    toolBar->addAction(settingsAction);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow{parent},
    mMainWindowUI{new Ui::MainWindowForm}
{
    mMainWindowUI->setupUi(this);

    mDockWidget = new QDockWidget("Output Window",this);
    this->addDockWidget(Qt::BottomDockWidgetArea,mDockWidget);
    mOutputWindow = new OutputWindow(this);
    mDockWidget->setWidget(mOutputWindow);

    mStuffPanel = new StuffPanel(this);
    this->setCentralWidget(mStuffPanel);

    connect(mStuffPanel, SIGNAL(stuff_done(QString)),mOutputWindow,SLOT(print_string(QString)));


    create_toolbar();
}

MainWindow::~MainWindow()
{
    delete mMainWindowUI;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::stuff_done(QString message)
{
    mOutputWindow->print_string(message);
}

void MainWindow::eat_doughnut()
{
    mOutputWindow->print_string("Mmmmm Doughnut!");
}

void MainWindow::update_settings()
{
    MySettings* settings = new MySettings(this);
    if(settings->exec()==QDialog::Accepted)
    {
        QString message= "Minimum " + settings->getMinimumText();
        mOutputWindow->print_string(message);
        message= "Maximum " + settings->getMaximumText();
        mOutputWindow->print_string(message);
    }
}
