#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

// 8 Ìí¼Ó¶¯×÷

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
//	8
	void open();
	void save();
	QAction*	_openAction;
	QAction*	_saveAction;
	QTextEdit*	_textEdit;
//     Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
