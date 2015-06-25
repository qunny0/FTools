#include <QObject>
#include <QDebug>

class Newspaper : public QObject
{
	Q_OBJECT

public:
	Newspaper(const QString& name) : _name(name)
	{
	
	}

	virtual ~Newspaper() 
	{

	}

	void send()
	{
		emit newPaper(_name);
	}

signals:
	void newPaper(const QString& name);

private:
	QString		_name;
};

class Reader : public QObject
{
	Q_OBJECT

public:
	Reader() {}

	void receiveNewspaper(const QString& name)
	{
		qDebug() << "Receives Newspaper: " << name;
	}
};