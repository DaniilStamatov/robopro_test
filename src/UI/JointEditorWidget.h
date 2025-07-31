#pragma once

#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>

class JointEditorWidget : public QWidget {
  Q_OBJECT

 public:
  JointEditorWidget(QWidget* parent = nullptr);

 private slots:
  void addJoint();
  void removeSelectedJoint();
  void computeForwardKinematics();

 private:
  void SetupUI();
  void SetupConnects();

 private:
  QTableWidget* table;
  QPushButton* addButton;
  QPushButton* removeButton;
  QPushButton* computeButton;
  QLabel* resultLabel;

  bool validateRow(int row, double& theta, double& a, double& d, double& alpha);
};
