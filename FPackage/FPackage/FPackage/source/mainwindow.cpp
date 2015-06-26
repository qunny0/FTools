#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	initUI();
}

void MainWindow::initUI()
{
	// About
	connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
	// Open
	connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
	// New
	connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newFile);
	// Save
	connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::about()
{
	qDebug() << "about";
}

void MainWindow::openFile()
{
	qDebug() << "open";
}

void MainWindow::saveFile()
{
	qDebug() << "save";
}

void MainWindow::newFile()
{
	qDebug() << "new";
}
