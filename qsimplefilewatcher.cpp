#include "qsimplefilewatcher.h"
#include "FileWatcher/FileWatcher.h"



class UpdateListener : public FW::FileWatchListener, public QObject
{
public:
	UpdateListener(QSimpleFileWatcher *parent);
	void handleFileAction(FW::WatchID watchid, const FW::String& dir, const FW::String& filename, FW::Action action);
private:
	QSimpleFileWatcher* parent;

};

UpdateListener::UpdateListener(QSimpleFileWatcher *parent)

{
	this->parent = parent;
}

void UpdateListener::handleFileAction(FW::WatchID watchid, const FW::String& dir, const FW::String& filename, FW::Action action) 
{
	WatchID id = (WatchID)watchid;
	QString directory = QString::fromStdString(dir);
	QString file = QString::fromStdString(filename);
	Action act = (Action)action;

	emit parent->fileAction(id, directory, file, act);
}


QSimpleFileWatcher::QSimpleFileWatcher(QObject *parent)
	: QObject(parent)
{
	watcher = new FW::FileWatcher();
	listener = new UpdateListener(this);
	timer = new QTimer(this);
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->setInterval(1);
	timer->start();
}

QSimpleFileWatcher::~QSimpleFileWatcher()
{
	delete listener;
	delete watcher;
	timer->stop();
	delete timer;
}

void QSimpleFileWatcher::update()
{
	((FW::FileWatcher*)watcher)->update();
}

WatchID QSimpleFileWatcher::addWatch(const QString &dir)
{
	
	return (WatchID)(((FW::FileWatcher*)watcher)->addWatch(dir.toStdString(), (UpdateListener*)listener));
}

void QSimpleFileWatcher::removeWatch(const QString &dir)
{
	((FW::FileWatcher*)watcher)->removeWatch(dir.toStdString());
}

void QSimpleFileWatcher::removeWatch(WatchID id)
{
	((FW::FileWatcher*)watcher)->removeWatch((FW::WatchID)id);
}
