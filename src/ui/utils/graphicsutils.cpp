#include "graphicsutils.h"

QByteArray GraphicsUtils::makeSvg(const QString& paths, const QColor& stroke)
{
    return QString(
               "<svg xmlns='http://www.w3.org/2000/svg' "
               "width='18' height='18' viewBox='0 0 24 24' "
               "fill='none' stroke='%1' stroke-width='1.6' "
               "stroke-linecap='round' stroke-linejoin='round'>%2</svg>"
               ).arg(stroke.name(), paths).toUtf8();
}