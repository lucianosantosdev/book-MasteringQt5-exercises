#include "MainWindow.h"
#include "Task.h"
#include "ui_MainWindow.h"

#include <QInputDialog>
#include <QObject>
#include <QtDebug>

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , m_tasks()
{
  ui->setupUi(this);
  connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::addTask);
  updateStatus();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void
MainWindow::updateStatus()
{
  int completedCount = 0;
  for (auto t : m_tasks) {
    completedCount += t->isCompleted();
  }
  int todoCount = m_tasks.count() - completedCount;

  ui->statusLabel->setText(QString("Status: %1 todo / %2 completed")
                             .arg(todoCount)
                             .arg(completedCount));
}

void
MainWindow::addTask()
{
  bool ok;
  QString name = QInputDialog::getText(this,
                                       tr("Add task"),
                                       tr("Task name"),
                                       QLineEdit::Normal,
                                       tr("Untitled task"),
                                       &ok);
  if (ok && !name.isEmpty()) {
    Task* task = new Task(name);
    m_tasks.append(task);
    ui->tasksLayout->addWidget(task);
    connect(task, &Task::removed, this, &MainWindow::removeTask);
    connect(task, &Task::statusChanged, this, &MainWindow::updateStatus);
  }
  updateStatus();
}

void
MainWindow::removeTask(Task* task)
{
  m_tasks.removeOne(task);
  ui->tasksLayout->removeWidget(task);
  task->setParent(nullptr);
  delete task;
  updateStatus();
}

void
MainWindow::taskStatusChanged(Task* task)
{}
