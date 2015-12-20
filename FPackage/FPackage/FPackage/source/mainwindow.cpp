#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>

#include "FPackageCore.h"

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
	QFileDialog* fileDialog = new QFileDialog(this);
	fileDialog->setWindowTitle(tr("create new package"));
// 	fileDialog->setAcceptMode(QFileDialog::AcceptSave);
// 	fileDialog->setFileMode(QFileDialog::AnyFile);
	fileDialog->setViewMode(QFileDialog::List);

	fileDialog->setDirectory(".");
// 	fileDialog->setFilter(tr("Image Files(*.jpg *.png)"));
	if (fileDialog->exec() == QDialog::Accepted)
	{
		QString path = fileDialog->selectedFiles()[0];

		createNewPackage(path);
	}
}

void MainWindow::createNewPackage(const QString& path)
{
	// 对路径进行处理，得到一个zpk的路径

	auto strPath = path.toStdString();

	F_PACKAGE::createFPackage(strPath);
}

