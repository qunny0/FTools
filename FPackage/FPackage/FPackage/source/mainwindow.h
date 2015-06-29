#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
	void initUI();

	void about();

	void openFile();

	void saveFile();

	void newFile();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
