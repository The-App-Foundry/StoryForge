#ifndef STORYMENUROW_H
#define STORYMENUROW_H

#include <QWidget>

class QLabel;
class QHBoxLayout;

class StoryMenuRow : public QWidget
{
    Q_OBJECT
public:
    explicit StoryMenuRow(QWidget *parent = nullptr);

    void setStoryData(const QString& name, const QString& meta, const QString& badge, const bool& isActive = false);

private:
    QLabel* m_dotLabel   = nullptr;
    QLabel* m_nameLabel  = nullptr;
    QLabel* m_metaLabel  = nullptr;
    QLabel* m_badgeLabel = nullptr;
};

#endif // STORYMENUROW_H
