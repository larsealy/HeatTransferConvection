#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>

class OutputWindow;
class StuffPanel;
class MySettings;


namespace Ui {
class MainWindowForm;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_actionExit_triggered();
    void stuff_done(QString message);
//    void stuff_done2(QString message);
    void eat_doughnut();
    void update_settings();
protected:
    void create_toolbar();

    QAction *create_doughnut_action();
    QAction *create_settings_action();
private:
    Ui::MainWindowForm *mMainWindowUI;
    QDockWidget* mDockWidget;
    OutputWindow* mOutputWindow;
    StuffPanel* mStuffPanel;
    MySettings* mMySettings;

};

#endif // MAINWINDOW_H
