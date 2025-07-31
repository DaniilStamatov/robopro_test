#include <QApplication>
#include "UI/JointEditorWidget.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  JointEditorWidget widget;
  widget.setWindowTitle("Joint Editor");
  widget.resize(400, 300);
  widget.show();
  return QApplication::exec();
}