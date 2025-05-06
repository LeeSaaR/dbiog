#include "appwindow.h"
#include "./ui_appwindow.h"

#include <QDebug>
#include <QFileDialog>

AppWindow::AppWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AppWindow)
{
    ui->setupUi(this);
    init();
}

AppWindow::~AppWindow()
{
    delete generator;
    delete ui;
}

void AppWindow::init()
{
    initConnections();
    initStyleSheet();
    initGenerator();
}

void AppWindow::initConnections()
{
    connect(ui->btn_output, &QPushButton::clicked, this, &AppWindow::onClickedOutput);
    connect(ui->btn_generate, &QPushButton::clicked, this, &AppWindow::onClickedGenerate);
    connect(ui->btn_pack, &QPushButton::clicked, this, &AppWindow::onClickedPack);
    connect(ui->btn_example, &QPushButton::clicked, this, &AppWindow::onClickedExample);
}

void AppWindow::initStyleSheet()
{
    QFile file(":/theme/style.qss");

    file.open(QIODevice::ReadOnly | QIODevice::Text);

    const QString file_content = file.readAll();
    qApp->setStyleSheet(file_content);
    file.close();
}

void AppWindow::initGenerator()
{
    QDir dir;
    current_path = dir.homePath();
    generator = new Generator();
}

void AppWindow::onClickedOutput()
{
    dir_source = QFileDialog::getExistingDirectory(this, "select output directory", current_path);
    if (dir_source.isEmpty())
        ui->btn_output->setText("Select Output Dir");
    else
        ui->btn_output->setText(dir_source);

    current_path = dir_source;
    generator->setDirSource(dir_source);
}

void AppWindow::onClickedGenerate()
{
    if (!generator->isValidDir()) return;
    generator->make_data();
}

void AppWindow::onClickedPack()
{
    qDebug() << __FUNCTION__;
    if (!generator->isValidDir()) return;
    generator->make_pack();
}

void AppWindow::onClickedExample()
{
    if (!generator->isValidDir()) return;
    generator->make_example();
}


