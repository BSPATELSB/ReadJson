#include "colormanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

ColorManager::ColorManager(QObject *parent) : QObject(parent), m_filePath("color.json") {
    connect(&m_watcher, &QFileSystemWatcher::fileChanged, this, &ColorManager::readColorFromFile);
    m_watcher.addPath(m_filePath);
    readColorFromFile();
}

QColor ColorManager::color() const {
    return m_color;
}

void ColorManager::readColorFromFile() {
    QFile file("/home/nxon/colour.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Cannot open file for reading: " << file.errorString();
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    if (!document.isObject()) {
        qWarning() << "Invalid JSON format";
        return;
    }

    QJsonObject jsonObject = document.object();
    if (jsonObject.contains("color") && jsonObject["color"].isString()) {
        QString colorString = jsonObject["color"].toString();
        QColor newColor(colorString);
        if (newColor.isValid() && newColor != m_color) {
            m_color = newColor;
            emit colorChanged();
        }
    } else {
        qWarning() << "JSON does not contain a valid color string";
    }
}
