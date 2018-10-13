#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QLayout>

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , m_cpuWidget(this)
  , m_memoryWidget(this)
{
  ui->setupUi(this);
  ui->centralWidget->layout()->addWidget(&m_cpuWidget);
  ui->centralWidget->layout()->addWidget(&m_memoryWidget);
}

MainWindow::~MainWindow()
{
  delete ui;
}
