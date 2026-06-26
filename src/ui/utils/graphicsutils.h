#ifndef GRAPHICSUTILS_H
#define GRAPHICSUTILS_H

#include <QByteArray>
#include <QString>
#include <QColor>

class GraphicsUtils {
public:
    static QByteArray makeSvg(const QString& paths, const QColor& stroke);
};

#endif // GRAPHICSUTILS_H