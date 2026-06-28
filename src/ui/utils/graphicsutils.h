#ifndef GRAPHICSUTILS_H
#define GRAPHICSUTILS_H

#include <QByteArray>
#include <QString>
#include <QColor>

class GraphicsUtils {
public:
    static QByteArray makeSvg(const QString& paths, const QColor& stroke);

    static QByteArray loadSvg(const QString& path);

    static QByteArray loadSvg(const QString& path,
                              const QColor& stroke,
                              const QColor& fill);

    static QByteArray loadSvg(const QString& path,
                              const QString& stroke,
                              const QString& fill);

    static QByteArray loadSvg(const QString& path,
                              const QColor& stroke);

    static QByteArray loadSvg(const QString& path,
                              const QString& stroke);

private:
    static QString transform(const QString& value);
    static QString transform(const QColor& color);
};

#endif // GRAPHICSUTILS_H