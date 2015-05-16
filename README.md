QSimpleFileWatcher
=========
**This library doesn't take kindly to Unicode. Probably best not to use it.**

This is a wrapper around [SimpleFileWatcher](https://code.google.com/p/simplefilewatcher/) by [James Wynn](http://jameswynn.com/).

This wrapper has been tested on Windows. It should compile on Linux and OS X, but I've not tested it yet. If not, getting it to do so will probably be quite easy.

Usage
=========
You can compile as a library or include directly in your own project.

Defining your handler slot:
`void fileActionHandler(WatchID watchId, const QString &dir, const QString &filename, Action action);
Set up the watcher:
`QSimpleFileWatcher *watcher = new QSimpleFileWatcher(this);
`QObject::connect(watcher, SIGNAL(fileAction(WatchID, const QString&, const QString&, Action)), this, SLOT(fileActionHandler(WatchID, const QString&, const QString&, Action)));
`watcher->addWatch(directoryString);

Done.
