#include "editorlayout.h"

EditorLayout::EditorLayout(QWidget *parent)
    : QWidget{parent}
{
    setObjectName("editorLayout");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

}
