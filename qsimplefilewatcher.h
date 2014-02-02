#ifndef QSIMPLEFILEWATCHER_H
#define QSIMPLEFILEWATCHER_H

#include <QObject>
#include <QTimer>


enum Action
{
	/// Sent when a file is created or renamed
	Add = 1,
	/// Sent when a file is deleted or renamed
	Delete = 2,
	/// Sent when a file is modified
	Modified = 4
};

typedef unsigned long WatchID;



class QSimpleFileWatcher : public QObject
{
	Q_OBJECT

public:
	QSimpleFileWatcher(QObject *parent);
	~QSimpleFileWatcher();
public slots:
	WatchID addWatch(const QString &dir);
	void removeWatch(const QString &dir);
	void removeWatch(WatchID watch);
signals:
	void fileAction(WatchID watchId, const QString &dir, const QString &filename, Action action);
private:
	QTimer *timer;
	void *watcher;
	void *listener;
private slots:
	void update();
};




#endif // QSIMPLEFILEWATCHER_H
