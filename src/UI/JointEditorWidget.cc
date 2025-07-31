#include "JointEditorWidget.h"
#include <QHeaderView>
#include <sstream>
#include "RobotMath.h"
JointEditorWidget::JointEditorWidget(QWidget* parent) : QWidget(parent) {
  SetupUI();
  SetupConnects();
  std::vector<Joint> defaultJoints = {{15.0, 0.0, 0.213, M_PI / 2}, {-50.0, -0.8, 0.193, 0.0},    {-60.0, -0.59, -0.16, 0.0},

                                      {95.0, 0.0, 0.25, M_PI / 2},  {50.0, 0.0, 0.28, -M_PI / 2}, {0.0, 0.0, 0.25, 0.0}};

  for (const auto& j : defaultJoints) {
    int row = table->rowCount();
    table->insertRow(row);
    table->setItem(row, 0, new QTableWidgetItem(QString::number(j.theta)));
    table->setItem(row, 1, new QTableWidgetItem(QString::number(j.a)));
    table->setItem(row, 2, new QTableWidgetItem(QString::number(j.d)));
    table->setItem(row, 3, new QTableWidgetItem(QString::number(j.alpha)));
  }

  computeForwardKinematics();
}

void JointEditorWidget::SetupConnects() {
  connect(addButton, &QPushButton::clicked, this, &JointEditorWidget::addJoint);
  connect(removeButton, &QPushButton::clicked, this, &JointEditorWidget::removeSelectedJoint);
  connect(computeButton, &QPushButton::clicked, this, &JointEditorWidget::computeForwardKinematics);
}

void JointEditorWidget::SetupUI() {
  table = new QTableWidget(this);
  table->setColumnCount(4);
  table->setHorizontalHeaderLabels({"θ (deg)", "a (m)", "d (m)", "α (rad)"});
  table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  table->verticalHeader()->setDefaultSectionSize(30);
  table->setStyleSheet("QTableWidget { font-size: 14px; }");

  addButton = new QPushButton("+", this);
  removeButton = new QPushButton("-", this);
  computeButton = new QPushButton("Вычислить", this);
  resultLabel = new QLabel("Результат: x=0 y=0 z=0", this);

  auto* buttonLayout = new QHBoxLayout;
  buttonLayout->addWidget(addButton);
  buttonLayout->addWidget(removeButton);
  buttonLayout->addWidget(computeButton);

  auto* mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(table);
  mainLayout->addLayout(buttonLayout);
  mainLayout->addWidget(resultLabel);
  setLayout(mainLayout);
}

void JointEditorWidget::addJoint() {
  int row = table->rowCount();
  table->insertRow(row);
  for (int col = 0; col < 4; ++col)
    table->setItem(row, col, new QTableWidgetItem("0.0"));
}

void JointEditorWidget::removeSelectedJoint() {
  int row = table->currentRow();
  if (row >= 0)
    table->removeRow(row);
}

bool JointEditorWidget::validateRow(int row, double& theta, double& a, double& d, double& alpha) {
  bool ok[4];
  theta = table->item(row, 0)->text().toDouble(&ok[0]);
  a = table->item(row, 1)->text().toDouble(&ok[1]);
  d = table->item(row, 2)->text().toDouble(&ok[2]);
  alpha = table->item(row, 3)->text().toDouble(&ok[3]);

  for (int i = 0; i < 4; ++i) {
    if (!ok[i]) {
      QMessageBox::critical(this, "Ошибка ввода", QString("Неверное значение в строке %1, столбце %2").arg(row + 1).arg(i + 1));
      return false;
    }
  }
  return true;
}

void JointEditorWidget::computeForwardKinematics() {
  RobotMath rm;
  int rows = table->rowCount();

  for (int row = 0; row < rows; ++row) {
    double theta;
    double a;
    double d;
    double alpha;
    if (!validateRow(row, theta, a, d, alpha))
      return;

    rm.AddJoint(Joint{theta, a, d, alpha});
  }

  auto result = rm.ComputeForwardKinematics();
  std::ostringstream oss;
  oss << "Результат: x=" << result.x << " y=" << result.y << " z=" << result.z;
  resultLabel->setText(QString::fromStdString(oss.str()));
}
