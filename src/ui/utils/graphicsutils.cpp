#include "graphicsutils.h"
#include <QFile>
#include <qdebug.h>

QString GraphicsUtils::transform(const QString& string)
{
    if (string == "none") {
        return string;
    } else {
        return QColor(string).name();
    }
}

QString GraphicsUtils::transform(const QColor& color)
{
    if (color.isValid()) {
        return color.name();
    } else {
        return QString("none");
    }
}

QByteArray GraphicsUtils::loadSvg(const QString& resourcePath)
{
    QString svg;
    QFile svgFile(resourcePath);

    if(svgFile.open(QFile::ReadOnly | QFile::Text)) {
        svg = QString::fromLatin1(svgFile.readAll());
        svgFile.close();
    } else {
        qWarning();
    }

    return svg.toUtf8();
}

QByteArray GraphicsUtils::makeSvg(const QString& paths, const QColor& stroke)
{
    return QString(
               "<svg xmlns='http://www.w3.org/2000/svg' "
               "width='18' height='18' viewBox='0 0 24 24' "
               "fill='none' stroke='%1' stroke-width='1.6' "
               "stroke-linecap='round' stroke-linejoin='round'>%2</svg>"
               ).arg(stroke.name(), paths).toUtf8();
}

QByteArray GraphicsUtils::loadSvg(const QString& resourcePath,
                                  const QColor& stroke,
                                  const QColor& fill)
{
    QString svg;
    QFile svgFile(resourcePath);

    if(svgFile.open(QFile::ReadOnly | QFile::Text)) {
        svg = QString::fromLatin1(svgFile.readAll());
        svgFile.close();
    } else {
        qWarning();
    }

    svg.replace(QLatin1String("stroke=\"currentColor\""),
                QLatin1String("stroke=\"%1\"").arg(transform(stroke)));

    svg.replace(QLatin1String("fill=\"none\""),
                QLatin1String("fill=\"%1\"").arg(transform(fill)));

    return svg.toUtf8();
}

QByteArray GraphicsUtils::loadSvg(const QString& resourcePath,
                                  const QString& stroke,
                                  const QString& fill)
{
    QString svg;
    QFile svgFile(resourcePath);

    if(svgFile.open(QFile::ReadOnly | QFile::Text)) {
        svg = QString::fromLatin1(svgFile.readAll());
        svgFile.close();
    } else {
        qWarning();
    }


    svg.replace(QLatin1String("stroke=\"currentColor\""),
                QLatin1String("stroke=\"%1\"").arg(transform(stroke)));

    svg.replace(QLatin1String("fill=\"none\""),
                QLatin1String("fill=\"%1\"").arg(transform(fill)));

    return svg.toUtf8();
}

QByteArray GraphicsUtils::loadSvg(const QString& resourcePath,
                                  const QColor& stroke)
{
    QString svg;
    QFile svgFile(resourcePath);

    if(svgFile.open(QFile::ReadOnly | QFile::Text)) {
        svg = QString::fromLatin1(svgFile.readAll());
        svgFile.close();
    } else {
        qWarning();
    }

    svg.replace(QLatin1String("stroke=\"currentColor\""),
                QLatin1String("stroke=\"%1\"").arg(transform(stroke)));

    return svg.toUtf8();
}

QByteArray GraphicsUtils::loadSvg(const QString& resourcePath,
                                  const QString& stroke)
{
    QString svg;
    QFile svgFile(resourcePath);

    if(svgFile.open(QFile::ReadOnly | QFile::Text)) {
        svg = QString::fromLatin1(svgFile.readAll());
        svgFile.close();
    } else {
        qWarning();
    }

    svg.replace(QLatin1String("stroke=\"currentColor\""),
                QLatin1String("stroke=\"%1\"").arg(transform(stroke)));

    return svg.toUtf8();
}