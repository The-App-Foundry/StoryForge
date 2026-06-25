#ifndef SCENEDATA_H
#define SCENEDATA_H

#include <QString>
#include <QColor>

// ============================================================
// SceneStatus — color-coded workflow state for a single scene
// ============================================================
enum class SceneStatus {
    NotStarted, // #556071 — placeholder, no prose written
    Drafted,    // #7bf0db — first pass complete
    Revised,    // #f5a623 — revision pass complete
    Final,      // #4ade80 — locked
    NeedsWork   // #f87171 — flagged for rework
};

inline QColor sceneStatusColor(SceneStatus s)
{
    switch (s) {
    case SceneStatus::NotStarted: return QColor(0x55, 0x60, 0x71);
    case SceneStatus::Drafted:    return QColor(0x7b, 0xf0, 0xdb);
    case SceneStatus::Revised:    return QColor(0xf5, 0xa6, 0x23);
    case SceneStatus::Final:      return QColor(0x4a, 0xde, 0x80);
    case SceneStatus::NeedsWork:  return QColor(0xf8, 0x71, 0x71);
    }
    return QColor(0x55, 0x60, 0x71);
}

inline QString sceneStatusLabel(SceneStatus s)
{
    switch (s) {
    case SceneStatus::NotStarted: return QStringLiteral("—");
    case SceneStatus::Drafted:    return QStringLiteral("DRAFT");
    case SceneStatus::Revised:    return QStringLiteral("REVISED");
    case SceneStatus::Final:      return QStringLiteral("FINAL");
    case SceneStatus::NeedsWork:  return QStringLiteral("REWORK");
    }
    return {};
}

struct SceneData {
    int         number;
    QString     title;
    QString     povCharacter;
    int         wordCount;
    SceneStatus status;
};

struct ActData {
    QString           title;
    QList<SceneData>  scenes;
};

#endif // SCENEDATA_H