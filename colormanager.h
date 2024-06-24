#ifndef COLORMANAGER_H
#define COLORMANAGER_H

#include <QObject>
#include <QColor>
#include <QFileSystemWatcher>

class ColorManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QColor color READ color NOTIFY colorChanged)

public:
    explicit ColorManager(QObject *parent = nullptr);

    QColor color() const;
    void checkTimer();

signals:
    void colorChanged();

public slots:
    void readColorFromFile();

private:
    QColor m_color;
    QFileSystemWatcher m_watcher;
    QString m_filePath;
};

#endif // COLORMANAGER_H
