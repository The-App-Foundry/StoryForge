#ifndef STORYMENU_H
#define STORYMENU_H

#include <QPushButton>

class QLabel;
class QMenu;

struct StoryData {
    QString name;
    QString meta;
    QString badge;
    bool isActive = false;
};

class StoryMenu : public QPushButton
{
    Q_OBJECT
public:
    explicit StoryMenu(QWidget *parent = nullptr);

    void populateStories(const QList<StoryData>& stories);

private:
    void addStoryToMenu(const QString& name, const QString& meta);

    QLabel* m_currentTitleLbl = nullptr;
    QLabel* m_currentGenreLbl = nullptr;
    QMenu*  m_dropdown        = nullptr;
};

#endif // STORYMENU_H
