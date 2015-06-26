#include "mainwindow.h"
#include "ui_mainwindow.h"

//	8
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QDialog>
#include <QDebug>
#include <QFileDialog>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

//	8
//     ui(new Ui::MainWindow)
//     ui->setupUi(this);
	setWindowTitle(tr("FPackage Windows"));
	
	_openAction = new QAction(QIcon(":/images/doc-open"), tr("&open..."), this);
	_openAction->setShortcut(QKeySequence::Open);
	_openAction->setStatusTip(tr("Open an existing file"));
	connect(_openAction, &QAction::triggered, this, &MainWindow::open);

	_saveAction = new QAction(QIcon(":/images/doc-save"), tr("&Save..."), this);
	_saveAction->setShortcut(QKeySequence::Save);
	_saveAction->setStatusTip(tr("Save file"));
	connect(_saveAction, &QAction::triggered, this, &MainWindow::save);

	QMenu* file = menuBar()->addMenu(tr("&file"));
	file->addAction(_openAction);
	file->addAction(_saveAction);

	QToolBar* toolBar = addToolBar(tr("&file"));
	toolBar->addAction(_openAction);
	toolBar->addAction(_saveAction);

	statusBar();

	_textEdit = new QTextEdit();
	setCentralWidget(_textEdit);
}

MainWindow::~MainWindow()
{
//	8
//     delete ui;
}

void MainWindow::open()
{
// 	QMessageBox::information(this, tr("Information"), tr("Open"));
// 	QDialog dialog(this); // dialog()
// 	QDialog* dialog = new QDialog(this);
// 	dialog->setWindowTitle(tr("Hello, dialog"));
// // 	dialog.exec();
// 	dialog->setAttribute(Qt::WA_DeleteOnClose);
// 	dialog->show();

// 	if (QMessageBox::Yes == QMessageBox::question(	this,
// 													tr("Question"),
// 													tr("Are you OK?"),
// 													QMessageBox::Yes | QMessageBox::No,
// 													QMessageBox::Yes))
// 	{
// 		QMessageBox::information(this, tr("Hmmmm..."), tr("I`m glad to hear that!"));
// 	}
// 	else {
// 		QMessageBox::information(this, tr("Hmmmm..."), tr("I`m sorry!"));
// 	}

// 	QMessageBox msgBox;
// 	msgBox.setText(tr("The document has been modified."));
// 	msgBox.setInformativeText(tr("Do you want to save your changes?"));
// 	msgBox.setStandardButtons(QMessageBox::Save
// 		| QMessageBox::Discard
// 		| QMessageBox::Cancel);
// 	msgBox.setDetailedText(tr("Differences here..."));
// 	msgBox.setDefaultButton(QMessageBox::Save);
// 	int ret = msgBox.exec();
// 	switch (ret) {
// 	case QMessageBox::Save:
// 		qDebug() << "Save document!";
// 		break;
// 	case QMessageBox::Discard:
// 		qDebug() << "Discard changes!";
// 		break;
// 	case QMessageBox::Cancel:
// 		qDebug() << "Close document!";
// 		break;
// 	}

	QString path = QFileDialog::getOpenFileName(this,
												tr("Open Fils"),
												".",
												tr("Text Files(*.txt)"));
	if (!path.isEmpty())
	{
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QMessageBox::warning(this, tr("Read Files"), tr("Cannot open file:\n%l").arg(path));
			return ;
		}
		QTextStream in(&file);
		_textEdit->setText(in.readAll());
		file.close();
	}
	else 
	{
		QMessageBox::warning(this, tr("path"), tr("You did not select any file"));
	}
}

void MainWindow::save()
{

}


