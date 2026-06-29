#ifndef GRAPHICSUTILS_H
#define GRAPHICSUTILS_H

#include <QByteArray>
#include <QString>
#include <QColor>

class GraphicsUtils {
public:
    static QByteArray makeSvg(const QString& paths, const QColor& stroke); // TODO: add QSize param for changing size.

    static QByteArray loadSvg(const QString& path,
                              const QString& stroke);

private:
    static QString transform(const QString& value);
    static void readFile(QString path); // helper that takes path and reads/closes file from overloads.
};

#endif // GRAPHICSUTILS_H