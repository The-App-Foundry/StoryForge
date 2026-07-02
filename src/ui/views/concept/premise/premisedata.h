#ifndef PREMISEDATA_H
#define PREMISEDATA_H

#include <QString>
#include <qobject.h>

struct PremiseData {
    QString logLine;
    QString ctlQuestion;
    QString ctlConflict;
    QString tone;
    QString themes;
};

Q_DECLARE_METATYPE(PremiseData);

#endif // PREMISEDATA_H
