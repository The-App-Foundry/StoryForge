#ifndef META_H
#define META_H

#include <QStringList>

struct SectionMeta {
    const char* name;       // as emitted by NavRail
    int         stackPage;  // index into m_stack
};

struct StageMeta {
    const char* stage;
    int         stageLevel;
};

static constexpr StageMeta kStages[] = {
    { "CONCEPT",  0 },
    { "DRAFT",    1 },
    { "EDITING",  2 },
    { "REVISION", 3 },
    { "FINAL",    4 },
    { "PUBLISH",  5 },
};

static constexpr SectionMeta kSections[] = {
    { "DRAFT",  0 },
    { "CAST",   1 },
    { "SCENES", 2 },
    { "PLACES", 3 },
    { "PROPS",  4 },
    { "NOTES",  5 },
};

const QStringList phases = {
    QStringLiteral("CONCEPT"),
    QStringLiteral("DRAFT"),
    QStringLiteral("EDITING"),
    QStringLiteral("REVISION"),
    QStringLiteral("FINAL"),
    QStringLiteral("PUBLISH"),
};

#endif // META_H
