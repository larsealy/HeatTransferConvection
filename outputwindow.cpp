#include "outputwindow.h"
#include "ui_outputwindow.h"

void OutputWindow::print_string(QString s)
{
    ui->mOutputText->appendPlainText(s);
}

OutputWindow::OutputWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OutputWindow)
{
    ui->setupUi(this);
}

OutputWindow::~OutputWindow()
{
    delete ui;
}

void OutputWindow::clear_output_window()
{
    ui->mOutputText->clear();
}
