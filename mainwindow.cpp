#include "mainwindow.h"
#include "ui_mainwindowform.h"
#include "outputwindow.h"
#include "stuffpanel.h"
#include "mysettings.h"

#include <QDockWidget>
#include <QToolBar>
#include <QKeySequence>

QAction * MainWindow::create_doughnut_action()
{
    const QIcon doughnutIcon = QIcon(":myicons/question_mark_icon.png");
    QAction *doughnutAction = new QAction(doughnutIcon, tr("&How To: Convection"), this);
    doughnutAction->setShortcut(QKeySequence{tr("Ctrl+H")});
    doughnutAction->setStatusTip(tr("How To Solve Convection Heat Transfer Problems"));
    connect(doughnutAction, &QAction::triggered, this, &MainWindow::print_convection_instructions);

    return doughnutAction;
}

QAction * MainWindow::create_settings_action()
{
    const QIcon settingsIcon = QIcon(":myicons/icon-flame-red.png");
    QAction *settingsAction = new QAction(settingsIcon, tr("&Change Thermalphysical Properties"), this);
    settingsAction->setShortcut(QKeySequence{tr("Ctrl+P")});
    settingsAction->setStatusTip(tr("Change Thermalphysical Properties"));
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
//    connect(mStuffPanel, SIGNAL(stuff_done2(QString)),mOutputWindow,SLOT(print_string(QString)));

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

void MainWindow::on_actionClear_Output_Window_triggered()
{
    mOutputWindow->clear_output_window();
}

void MainWindow::stuff_done(QString message)
{
    mOutputWindow->print_string(message);
}

void MainWindow::print_convection_instructions()
{
    mOutputWindow->print_string("\nHow To Solve Convection Heat Transfer Problems");
    mOutputWindow->print_string("    1) Identify the flow geometery (over flat plate, cylinder, inside pipe, ...)");
    mOutputWindow->print_string("    2) Evaluate the fluid properties (be sure to use the correct temperature)");
    mOutputWindow->print_string("    3) Determine the flow regime (laminar, mixed, turbulent");
    mOutputWindow->print_string("    4) Identify what is needed (local or average)");
    mOutputWindow->print_string("    5) Select the correct correlation (Nu = C*Re^m*Pr*n)");
    mOutputWindow->print_string("    6) Compute h (Nu = hL / k)");
    mOutputWindow->print_string("    7) Use h (q = hA(T_s - T_inf))");
    mOutputWindow->print_string("    8) Iterate if you don't end up with the same T_s (go to step 2)\n");
}

void MainWindow::update_settings()
{
    MySettings* settings = new MySettings(this);
    if(settings->exec()==QDialog::Accepted)
    {
        double rho = settings->getDensity();
        double Cp = settings->getSpecificHeat();
        double mu = settings->getDynamicViscosity();
        double nu = settings->getKinematicViscosity();
        double k = settings->getThermalConductivity();
        double alpha = settings->getThermalDiffusivity();
        double Pr = settings->getPrandtlNumber();
        double beta = settings->getBeta();
        mStuffPanel->load_thermophysical_properties(rho, Cp, mu, nu, k, alpha, Pr, beta);

        mOutputWindow->print_string("Thermophysical properties loaded:");
        mOutputWindow->print_string("    Density = " + QString::number(rho));
        mOutputWindow->print_string("    Specific Heat = " + QString::number(Cp));
        mOutputWindow->print_string("    Dynamic Viscosity = " + QString::number(mu));
        mOutputWindow->print_string("    Kinematic Viscosity = " + QString::number(nu));
        mOutputWindow->print_string("    Thermal Conductivity = " + QString::number(k));
        mOutputWindow->print_string("    Thermal Diffusivity = " + QString::number(alpha));
        mOutputWindow->print_string("    Prandtl Number = " + QString::number(Pr));
        mOutputWindow->print_string("    Beta = " + QString::number(beta));

        mStuffPanel->enable_functions_to_calculate_reynolds_number();
    }
}

