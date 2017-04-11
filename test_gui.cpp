#include <QDebug>
#include <QtTest/QtTest>
#include <QtWidgets>

#include "canvas_widget.hpp"
#include "main_window.hpp"
#include "message_widget.hpp"
#include "repl_widget.hpp"
#include <QList>
#include <iterator>
#include <QDebug>
#include <QTest>
// ADD YOUR TESTS TO THIS CLASS !!!!!!!
class TestGUI : public QObject {
  Q_OBJECT

public:
private slots:

  void initTestCase();
  void testREPLGood();
  void testREPLBad();
  void testREPLBad2Good();
  void testPoint();
  void testLine();
  void testArc();
  void test_define_point();
  void test_define_line();
  void test_define_arc();
  void test_repeat_repl_num();
  void test_repeat_repl_bool();
  void testEnvRestore();

private:
  MainWindow w;

  REPLWidget *repl;
  QLineEdit *replEdit;
  MessageWidget *message;
  QLineEdit *messageEdit;
  CanvasWidget *canvas;
  QGraphicsScene *scene;
};

void TestGUI::initTestCase() {

  repl = w.findChild<REPLWidget *>();
 QVERIFY2(repl, "Could not find REPLWidget instance in MainWindow instance.");

  replEdit = repl->findChild<QLineEdit *>();
  QVERIFY2(replEdit,
           "Could not find QLineEdit instance in REPLWidget instance.");

  message = w.findChild<MessageWidget *>();
  QVERIFY2(message,
           "Could not find MessageWidget instance in MainWindow instance.");

  messageEdit = message->findChild<QLineEdit *>();
  QVERIFY2(messageEdit,
           "Could not find QLineEdit instance in MessageWidget instance.");

  canvas = w.findChild<CanvasWidget *>();
  QVERIFY2(canvas,
           "Could not find CanvasWidget instance in MainWindow instance.");

  scene = canvas->findChild<QGraphicsScene *>();
  QVERIFY2(scene,
           "Could not find QGraphicsScene instance in CanvasWidget instance.");
    w.show();
}

void TestGUI::testREPLGood() {

  QVERIFY(repl && replEdit);
  QVERIFY(message && messageEdit);

  // send a string to the repl widget
  QTest::keyClicks(replEdit, "(define a 1)");
  QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);

  // check message
  QVERIFY2(messageEdit->isReadOnly(),
           "Expected QLineEdit inside MessageWidget to be read-only.");
  QCOMPARE(messageEdit->text(), QString("(1)"));
}

void TestGUI::testREPLBad() {

  QVERIFY(repl && replEdit);
  QVERIFY(message && messageEdit);

  // send a string to the repl widget
  QTest::keyClicks(replEdit, "(foo)");
  QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);
// check message
  QVERIFY2(messageEdit->isReadOnly(),
           "Expected QLineEdit inside MessageWidget to be read-only.");
  QVERIFY2(messageEdit->text().startsWith("Error"), "Expected error message.");

  // check background color and selection
  QPalette p = messageEdit->palette();
  QCOMPARE(p.highlight().color(), QColor(Qt::red));
  QVERIFY2(messageEdit->selectedText().startsWith("Error"),
           "Expected error to be selected.");
}

void TestGUI::testREPLBad2Good() {

  QVERIFY(repl && replEdit);
  QVERIFY(message && messageEdit);

  // send a string to the repl widget
  QTest::keyClicks(replEdit, "(foo)");
  QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);

  // check message
  QVERIFY2(messageEdit->isReadOnly(),
           "Expected QLineEdit inside MessageWidget to be read-only.");
  QVERIFY2(messageEdit->text().startsWith("Error"), "Expected error message.");

  // check background color and selection
  QPalette p = messageEdit->palette();
  QCOMPARE(p.highlight().color(), QColor(Qt::red));
  QVERIFY2(messageEdit->selectedText().startsWith("Error"),
           "Expected error to be selected.");

  // send a string to the repl widget
  QTest::keyClicks(replEdit, "(define value 100)");
  QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);

  // check message
  QVERIFY2(messageEdit->isReadOnly(),
           "Expected QLineEdit inside MessageWidget to be read-only.");
  QCOMPARE(messageEdit->text(), QString("(100)"));

  // check background color and selection
  p = messageEdit->palette();
  QVERIFY2(p.highlight().color() != QColor(Qt::red),
           "Did not expect red highlight on successful eval.");
  QVERIFY2(messageEdit->selectedText() == "",
           "Expected no selcted text on successful eval.");
}

void TestGUI::testLine() {
    
    QVERIFY(repl && replEdit);
    QVERIFY(canvas && scene);
    
    // send a string to the repl widget
    QTest::keyClicks(replEdit, "(draw (line (point 10 0) (point 0 10)))");
    QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);
    
    // check canvas
    QVERIFY2(scene->itemAt(QPointF(10, 0), QTransform()) != 0,
             "Expected a line in the scene. Not found.");
    QVERIFY2(scene->itemAt(QPointF(0, 10), QTransform()) != 0,
             "Expected a line in the scene. Not found.");
}


void TestGUI::testPoint() {
    
    QVERIFY(repl && replEdit);
    QVERIFY(canvas && scene);
    // send a string to the repl widget
    QTest::keyClicks(replEdit, "(draw (point 0 0))");
    QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);
    // check canvas
    QVERIFY2(scene->itemAt(QPointF(0, 0), QTransform()) != 0,
             "Expected a point in the scene. Not found.");
}


void TestGUI::testArc() {
    
    QVERIFY(repl && replEdit);
    QVERIFY(canvas && scene);
    
    // send a string to the repl widget
    QTest::keyClicks(replEdit, "(draw (arc (point 0 0) (point 100 0) pi))");
    QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);
    
    // check canvas
    QVERIFY2(scene->itemAt(QPointF(100, 0), QTransform()) != 0,
             "Expected a point on the arc in the scene. Not found.");
    QVERIFY2(scene->itemAt(QPointF(-100, 0), QTransform()) != 0,
             "Expected a point on the arc in the scene. Not found.");
}




void TestGUI::testEnvRestore() {

  QVERIFY(repl && replEdit);
  QVERIFY(canvas && scene);

  // send a string to the repl widget
  QTest::keyClicks(replEdit, "(begin (draw (point -20 0)) (define pi 3))");
  QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);

    QGraphicsItem * temp = scene->itemAt(QPointF(-20, 0), QTransform());

    // check canvas
  QVERIFY2(scene->itemAt(QPointF(-20, 0), QTransform()) == 0,
           "Did not expected a point in the scene. One found.");
}




void TestGUI::test_define_point() {
    
    QVERIFY(repl && replEdit);
    QVERIFY(canvas && scene);
    // send a string to the repl widget
    QTest::keyClicks(replEdit, "(define a (point 3 3))");
    QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);
    QTest::keyClicks(replEdit, "(draw a)");
    QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);
    
    // check canvas
    QVERIFY2(scene->itemAt(QPointF(3, 3), QTransform()) != 0,
             "Expected a point in the scene. Not found.");
}

void TestGUI::test_define_line() {
    
    QVERIFY(repl && replEdit);
    QVERIFY(canvas && scene);
    // send a string to the repl widget
    QTest::keyClicks(replEdit, "(define b (line (point 15 -15) (point 0 30)))");
    QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);
    QTest::keyClicks(replEdit, "(draw b)");
    QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);
    // check canvas
    QVERIFY2(scene->itemAt(QPointF(15, -15), QTransform()) != 0,
             "Expected a line in the scene. Not found.");
    QVERIFY2(scene->itemAt(QPointF(0, 30), QTransform()) != 0,
             "Expected a line in the scene. Not found.");
}

void TestGUI::test_define_arc() {
    QVERIFY(repl && replEdit);
    QVERIFY(canvas && scene);
    
    // send a string to the repl widget
    QTest::keyClicks(replEdit, "(define c (arc (point 0 0) (point 200 0) pi))");
    QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);
    QTest::keyClicks(replEdit, "(draw c)");
    QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);
    // check canvas
    QVERIFY2(scene->itemAt(QPointF(200, 0), QTransform()) != 0,
             "Expected a point on the arc in the scene. Not found.");
    QVERIFY2(scene->itemAt(QPointF(-200, 0), QTransform()) != 0,
             "Expected a point on the arc in the scene. Not found.");
   
}


void TestGUI::test_repeat_repl_num() {
    
    QVERIFY(repl && replEdit);
    QVERIFY(message && messageEdit);
    
    // send a string to the repl widget
    QTest::keyClicks(replEdit, "(define d 1)");
    QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);
    QTest::keyClicks(replEdit, "(define d 3)");
    QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);
    
    // check message
    QVERIFY2(messageEdit->isReadOnly(),
             "Expected QLineEdit inside MessageWidget to be read-only.");
      QVERIFY2(messageEdit->text().startsWith("Error"), "Expected error message.");
}


void TestGUI::test_repeat_repl_bool() {
    
    QVERIFY(repl && replEdit);
    QVERIFY(message && messageEdit);
    
    // send a string to the repl widget
    QTest::keyClicks(replEdit, "(define d True)");
    QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);
    QTest::keyClicks(replEdit, "(define d False)");
    QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);
    // check message
    QVERIFY2(messageEdit->isReadOnly(),
             "Expected QLineEdit inside MessageWidget to be read-only.");
    QVERIFY2(messageEdit->text().startsWith("Error"), "Expected error message.");
}











QTEST_MAIN(TestGUI)
#include "test_gui.moc"
