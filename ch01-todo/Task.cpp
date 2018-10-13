#include "Task.h"
#include "ui_Task.h"

#include <QDebug>
#include <QInputDialog>

Task::Task(const QString& name, QWidget* parent)
  : QWidget(parent)
  , ui(new Ui::Task)
{
  ui->setupUi(this);
  setName(name);
  connect(ui->editButton, &QPushButton::clicked, this, &Task::rename);
  connect(ui->removeButton, &QPushButton::clicked, this, [this, name] {
    qDebug() << "Trying to remove" << name;
    emit removed(this);
  });
  connect(ui->checkbox, &QCheckBox::toggled, this, &Task::checked);
}

Task::~Task()
{
  delete ui;
}

void
Task::setName(const QString& name)
{
  ui->checkbox->setText(name);
}

QString
Task::name() const
{
  return ui->checkbox->text();
}

bool
Task::isCompleted() const
{
  return ui->checkbox->isChecked();
}

void
Task::rename()
{
  bool ok;
  QString value = QInputDialog::getText(this,
                                        tr("Edit task"),
                                        tr("Task name"),
                                        QLineEdit::Normal,
                                        this->name(),
                                        &ok);
  if (ok && !value.isEmpty()) {
    setName(value);
  }
}

void
Task::checked(bool checked)
{
  QFont font(ui->checkbox->font());
  font.setItalic(checked);
  font.setStrikeOut(checked);
  ui->checkbox->setFont(font);
  emit statusChanged(this);
}
