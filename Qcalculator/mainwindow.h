#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QChar>
#include <QStack>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButtonDot_released();

    void on_pushButton_0_released();

    void on_pushButton_1_released();

    void on_pushButton_2_released();

    void on_pushButton_3_released();

    void on_pushButton_4_released();

    void on_pushButton_5_released();

    void on_pushButton_6_released();

    void on_pushButton_7_released();

    void on_pushButton_8_released();

    void on_pushButton_9_released();

    void on_pushButtonC_released();

    void on_pushButtonDot_Plus_released();

    void on_pushButtonDot_Minus_released();

    void on_pushButtonDot_Multi_released();

    void on_pushButtonDot_Division_released();

    void on_pushButtonDot_Equal_released();

    QString change(const QString & s_mid);

    void repairExpress(QString & express);

    void rettifyExpress(QString & express);
    double CalExp(const QStringList & express);

    void on_pushButtonLeft_released();

    void on_pushButtonRight_released();

    void on_pushButtonDelete_released();

private:
    Ui::MainWindow *ui;
    QString symbol;
    int leftBracket;
    int rightBracket;
};
#endif // MAINWINDOW_H
