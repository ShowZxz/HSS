#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "manager.h"

#include <QMainWindow>
#include <QFileDialog>
#include <QSettings>
#include <QDebug>
#include <QMessageBox>
#include <QUrl>
#include <QDesktopServices>
#include <QScreen>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_comboBox_ScreeNumber_currentIndexChanged(int index);

    void on_pushButton_testScreen_clicked();

    void on_comboBox_Resolution_currentTextChanged(const QString &arg1);

    void on_pushButton_Save_clicked();

    void on_pushButton_Inscription_clicked();

private:
    Ui::MainWindow *ui;
    Manager man;
};
#endif // MAINWINDOW_H
