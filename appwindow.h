#ifndef APPWINDOW_H
#define APPWINDOW_H

#include "generator.h"

#include <QMainWindow>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class AppWindow; }
QT_END_NAMESPACE

class AppWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::AppWindow *ui;
    QString dir_source;
    Generator* generator;
    QString current_path;
public:
    AppWindow(QWidget *parent = nullptr);
    ~AppWindow();
private:
    void init();
    void initConnections();
    void initStyleSheet();
    void initGenerator();
private slots:
    void onClickedOutput();
    void onClickedGenerate();
    void onClickedPack();
    void onClickedExample();
};
#endif // APPWINDOW_H
