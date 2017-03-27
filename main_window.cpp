#include "main_window.hpp"

#include <QtWidgets>

MainWindow::MainWindow()
{
    init();
}

// Default construct a MainWidow, using filename as the script file to attempt to preload
MainWindow::MainWindow(std::string filename, QWidget * parent)
{
    init();
    QFile file("in.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray line;
        while (!file.atEnd())
        {
            line.append(file.readLine());
        }

        this->render(QString::fromStdString(line.toStdString()));
    }
}

void MainWindow::init()
{
    qtInterpreter = new QtInterpreter;
    messageLabel = new QLabel(tr("message:"));
    scriptLabel = new QLabel(tr("vtscript>"));
    canvas = new CanvasWidget;
    msg = new MessageWidget;
    repl = new REPLWidget;

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(messageLabel, 0, 0, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(msg->value, 0, 1, 1, 5);
    mainLayout->addWidget(canvas->view, 1, 0, 6, 6);
    mainLayout->addWidget(scriptLabel, 8, 0, Qt::AlignLeft);
    mainLayout->addWidget(repl->lineEdit, 8, 1, 1, 5);
    setLayout(mainLayout);
    //setWindowTitle(tr("vtdrawer"));

    connect(repl->lineEdit, SIGNAL(returnPressed()), this, SLOT(scriptChanged()));
    connect(qtInterpreter, SIGNAL(info(QString)), msg, SLOT(info(QString)));
    connect(qtInterpreter, SIGNAL(error(QString)), msg, SLOT(error(QString)));
    connect(qtInterpreter, SIGNAL(drawGraphic(QGraphicsItem*)), canvas, SLOT(addGraphic(QGraphicsItem*)));
}


void MainWindow::render(QString qstr)
{
    canvas->scene->clear();
    qtInterpreter->parseAndEvaluate(qstr);
}

void MainWindow::scriptChanged()
{
    this->render(repl->lineEdit->text());
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    auto size = event->size();

    //msg->value->setText(QString(size.height()));
    //canvas->scene->setSceneRect(0, 0, size.width(), size.height());
    //canvas->view->setSceneRect(0, 0, size.width(), size.height());
}
