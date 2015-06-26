#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenu>
#include <QToolBar>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	initUI();
}

void MainWindow::initUI()
{
	//	about action
// 	_pAboutAction = new QAction(QIcon(tr("")), tr("&About"), this);
// 	_pAboutAction->setStatusTip(tr("About FPackage"));
// 	connect(_pAboutAction, &QAction::triggered, this, &MainWindow::about);
}

MainWindow::~MainWindow()
{
    delete ui;
}