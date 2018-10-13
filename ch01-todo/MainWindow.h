#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

namespace Ui {
class MainWindow;
}

class Task;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

private slots:
  void addTask();
  void removeTask(Task* task);
  void taskStatusChanged(Task* task);

private:
  void updateStatus();

  Ui::MainWindow* ui;
  QVector<Task*> m_tasks;
};

#endif // MAINWINDOW_H
