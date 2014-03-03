#include "qsimplefilewatcher.h"
#include "FileWatcher/FileWatcher.h"

//http://stackoverflow.com/a/8481695
/*! Convert a QString to an std::wstring */
std::wstring qToStdWString(const QString &str)
{
#ifdef _MSC_VER
    return std::wstring((const wchar_t *)str.utf16());
#else
    return str.toStdWString();
#endif
}

/*! Convert an std::wstring to a QString */
QString stdWToQString(const std::wstring &str)
{
#ifdef _MSC_VER
    return QString::fromUtf16((const ushort *)str.c_str());
#else
    return QString::fromStdWString(str);
#endif
}

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
#ifdef UNICODE
	QString directory =stdWToQString(dir);
	QString file = stdWToQString(filename);
#else
	QString directory = QString::fromStdString(dir);
	QString file = QString::fromStdString(filename);
#endif
	
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
#ifdef UNICODE	
	return (WatchID)(((FW::FileWatcher*)watcher)->addWatch(qToStdWString(dir), (UpdateListener*)listener));
#else
	return (WatchID)(((FW::FileWatcher*)watcher)->addWatch(dir.toStdString(), (UpdateListener*)listener));
#endif
}

void QSimpleFileWatcher::removeWatch(const QString &dir)
{
#ifdef UNICODE	
	((FW::FileWatcher*)watcher)->removeWatch(qToStdWString(dir));
#else
	((FW::FileWatcher*)watcher)->removeWatch(dir.toStdString());
#endif

}

void QSimpleFileWatcher::removeWatch(WatchID id)
{
	((FW::FileWatcher*)watcher)->removeWatch((FW::WatchID)id);
}
