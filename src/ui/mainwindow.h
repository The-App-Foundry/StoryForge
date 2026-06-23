#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class SideBar;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    SideBar* m_sideBar = nullptr;
};

#endif // MAINWINDOW_H