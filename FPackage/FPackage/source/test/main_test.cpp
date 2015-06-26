#include "mainwindow.h"
#include <QApplication>

// http://www.devbean.net/2012/08/qt-study-road-2-custom-signal-slot/
// http://www.devbean.net/2012/08/qt-study-road-2-catelog/

// 1
// #include <QLabel>

// 2
// #include <QPushButton>
// #include <QDebug>

//	3. slot
// #include "qtTest.h"

//	11 ���ֹ�����
// #include <QSpinBox>
// #include <QSlider>
// #include <QHBoxLayout>

//	35	FileSystem
#include <QFile>
#include <QFileInfo>
#include <QDebug>

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
// 	Newspaper newspaper("Newspaper A");
// 	Reader reader;
// 	QObject::connect(&newspaper, &Newspaper::newPaper,
// 					 &reader, &Reader::receiveNewspaper);
// 	newspaper.send();

//	11
// 	QWidget windows;
// 	windows.setWindowTitle("Enter your age");
// 
// 	QSpinBox*	spinBox = new QSpinBox(&windows);
// 	QSlider*	slider = new QSlider(Qt::Horizontal, &windows);
// 	spinBox->setRange(0, 130);
// 	slider->setRange(0, 130);
// 
// 	QObject::connect(slider, &QSlider::valueChanged, spinBox, &QSpinBox::setValue);
// 	// valueChanged �����غ�������ȷ��ָ�����Ǹ�����
// 	void (QSpinBox:: *spinBoxSignal)(int) = &QSpinBox::valueChanged;
// 	QObject::connect(spinBox, spinBoxSignal, slider, &QSlider::setValue);
// 	spinBox->setValue(35);
// 
// 	QHBoxLayout* layout = new QHBoxLayout;
// 	layout->addWidget(spinBox);
// 	layout->addWidget(slider);
// 	windows.setLayout(layout);
// 
// 	windows.show();

//	35
	QFile file("C:/Users/cherryxue/Desktop/record.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Open file failed";
		return -1;
	}
	else {
		while (!file.atEnd())
		{
			qDebug() << file.readLine();
		}
	}

	QFileInfo fileInfo(file);
	qDebug() << fileInfo.isDir();
	qDebug() << fileInfo.isExecutable();
	qDebug() << fileInfo.baseName();
	qDebug() << fileInfo.completeBaseName();
	qDebug() << fileInfo.suffix();
	qDebug() << fileInfo.completeSuffix();

    return a.exec();	
}
