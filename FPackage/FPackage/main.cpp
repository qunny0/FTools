#include "mainwindow.h"
#include <QApplication>

// http://www.devbean.net/2012/08/qt-study-road-2-custom-signal-slot/

// 1
// #include <QLabel>

// 2
// #include <QPushButton>
// #include <QDebug>

//	3. slot
#include "qtTest.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//     MainWindow w;
//     w.show();

//  1
// 	QLabel* label = new QLabel("hello world");
// 	label->show();
// 	label->setAttribute(Qt::WA_DeleteOnClose);

//	2 simple slot
// 	QPushButton button("quit");
// 	QObject::connect(&button, &QPushButton::clicked, &QApplication::quit);
// 	QObject::connect(&button, &QPushButton::clicked, [](bool ){
// 		qDebug() << "be clicked " ;
// 		QApplication::quit();
// 	});
// 	button.show();

//	3 slot signal observer
	Newspaper newspaper("Newspaper A");
	Reader reader;

	QObject::connect(&newspaper, &Newspaper::newPaper,
					 &reader, &Reader::receiveNewspaper);

	newspaper.send();

    return a.exec();
}
