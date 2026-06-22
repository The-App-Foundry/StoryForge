#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class SideBar;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    SideBar* m_sideBar = nullptr;
};
#endif // MAINWINDOW_H
