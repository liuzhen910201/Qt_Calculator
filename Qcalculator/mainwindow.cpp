#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    symbol="+-*/.";
    leftBracket=0;
    rightBracket=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonDot_released()
{//输入.
    int indexOfDot=ui->lineEditNumber->text().lastIndexOf(".");
    int indexOfPlus=ui->lineEditNumber->text().lastIndexOf("+");
    int indexOfMinus=ui->lineEditNumber->text().lastIndexOf("-");
    int indexOfMuilti=ui->lineEditNumber->text().lastIndexOf("*");
    int indexOfDivision=ui->lineEditNumber->text().lastIndexOf("/");

    QString lastStr=ui->lineEditNumber->text().right(1);//最后一位
    bool isContains=symbol.contains(lastStr,Qt::CaseSensitive);//最后一位是+-*/.中任意一个

    if((!isContains)&&((indexOfDot<=indexOfPlus)||(indexOfDot<=indexOfMinus)||(indexOfDot<=indexOfMuilti)||(indexOfDot<=indexOfDivision))){
        //避免出现类似1.1.2 小数点下标不大于符号
        ui->lineEditNumber->setText(ui->lineEditNumber->text()+".");
    }
}


void MainWindow::on_pushButton_0_released()
{//输入0
    ui->lineEditNumber->setText(ui->lineEditNumber->text()+"0");
}

void MainWindow::on_pushButton_1_released()
{//输入1
    ui->lineEditNumber->setText(ui->lineEditNumber->text()+"1");
}


void MainWindow::on_pushButton_2_released()
{//输入2
    ui->lineEditNumber->setText(ui->lineEditNumber->text()+"2");
}

void MainWindow::on_pushButton_3_released()
{//输入3
    ui->lineEditNumber->setText(ui->lineEditNumber->text()+"3");
}


void MainWindow::on_pushButton_4_released()
{//输入4
    ui->lineEditNumber->setText(ui->lineEditNumber->text()+"4");
}


void MainWindow::on_pushButton_5_released()
{//输入5
    ui->lineEditNumber->setText(ui->lineEditNumber->text()+"5");
}


void MainWindow::on_pushButton_6_released()
{//输入6
    ui->lineEditNumber->setText(ui->lineEditNumber->text()+"6");
}


void MainWindow::on_pushButton_7_released()
{//输入7
    ui->lineEditNumber->setText(ui->lineEditNumber->text()+"7");
}


void MainWindow::on_pushButton_8_released()
{//输入8
    ui->lineEditNumber->setText(ui->lineEditNumber->text()+"8");
}


void MainWindow::on_pushButton_9_released()
{//输入9
    ui->lineEditNumber->setText(ui->lineEditNumber->text()+"9");
}



void MainWindow::on_pushButtonC_released()
{//清除
    ui->lineEditNumber->setText("");
}


void MainWindow::on_pushButtonDot_Plus_released()
{//输入+
    QString lastStr=ui->lineEditNumber->text().right(1);
    bool isContains=symbol.contains(lastStr,Qt::CaseSensitive);
    if(!isContains){
        ui->lineEditNumber->setText(ui->lineEditNumber->text()+"+");
    }
}


void MainWindow::on_pushButtonDot_Minus_released()
{//输入-
    if(ui->lineEditNumber->text()==""){//bug（强制退出）预防
        ui->lineEditNumber->setText(ui->lineEditNumber->text()+"-");
    }else{
        QString lastStr=ui->lineEditNumber->text().right(1);//最后一位
        QString lastSecStr=ui->lineEditNumber->text().right(2).at(0);//倒数第二位
        bool isContains=symbol.contains(lastStr,Qt::CaseSensitive);//最后一位为符号
        bool isContainsSec=symbol.contains(lastSecStr,Qt::CaseSensitive);
        if((lastStr!=".")&&(!(isContains&&isContainsSec))){//最后一位不是小数点 且 最后两位不都是符号
            if(isContains){
                ui->lineEditNumber->setText(ui->lineEditNumber->text()+"(-");
            }else{
                ui->lineEditNumber->setText(ui->lineEditNumber->text()+"-");
            }
        }
    }
}


void MainWindow::on_pushButtonDot_Multi_released()
{//输入*
    QString lastStr=ui->lineEditNumber->text().right(1);
    bool isContains=symbol.contains(lastStr,Qt::CaseSensitive);
    if(!isContains){
        ui->lineEditNumber->setText(ui->lineEditNumber->text()+"*");
    }
}


void MainWindow::on_pushButtonDot_Division_released()
{//输入/
    QString lastStr=ui->lineEditNumber->text().right(1);
    bool isContains=symbol.contains(lastStr,Qt::CaseSensitive);
    if(!isContains){
        ui->lineEditNumber->setText(ui->lineEditNumber->text()+"/");
    }
}


void MainWindow::on_pushButtonDot_Equal_released()
{//= 算式计算
    QString equation = ui->lineEditNumber->text();
    if(leftBracket!=rightBracket){//括号对应
        ui->lineEditNumber->setText("error input!");
    }else{
        repairExpress(equation);
        QString result=change(equation);
        //qDebug() << CalExp(result.split(' ', QString::SkipEmptyParts));//debug
        ui->lineEditNumber->setText(QString::number(CalExp(result.split(' ', QString::SkipEmptyParts))));//输出结果
    }
    //括号归零
    leftBracket=0;
    rightBracket=0;
}

//针对负号进行字符串修复 例如:-1*-3+2*(3+3) -> (0-1)*(0-3)+2*(3+3)
void MainWindow::repairExpress(QString & express)
{
    bool repair = false;
    int lpos = -1, rpos = -1;
    QString result;
    for(int i = 0; i < express.size(); ++i)
    {
        QChar c = express[i];
        if (c == '+' || c == '-' || c == '*' || c == '/')//出现符号时记录
        {
            if (repair)
            {
                result.append(')');
                lpos = -1;
                repair = false;
            }

            if (c == '-'&&
                (i == 0  || lpos != -1 && lpos == i - 1))
            {
                result.append('(');
                repair = true;
            }

            lpos = i;
        }

        result.append(c);
    }

    express = result;
    //ui->label->setText(express);
}

//数字和负号之间插入空格， 方便后续计算时分割
void MainWindow::rettifyExpress(QString & express)
{
    if (express.endsWith(' ') == false)
    {
        express.append(' ');
    }
}

//中缀表达式转后缀表达式
QString MainWindow::change(const QString & s_mid)
{
    QString result;
    QStack<QChar> stk;

    QMap<QChar, int> op;//利用map来实现运算符对应其优先级
    op['(']=0;
    op[')']=0;
    op['+']=1;
    op['-']=1;
    op['*']=2;
    op['/']=2;
    auto iter = s_mid.begin();
    for(int i = 0; i < s_mid.size(); ++i)
    {
        QChar c = s_mid[i];
        if (c == ' ')
        {
            continue;
        }
        if (c == '-' &&
            (i == 0 || op.contains(s_mid[i-1])))//可能为负号
        {
            result.append('0');
        }
        if(op.contains(c))//判断该元素是否为运算符
        {
            if(c == ')')//情况2
            {
                while(stk.top() != '(')
                {
                    rettifyExpress(result);
                    result.append(stk.top());
                    stk.pop();
                }
                stk.pop();
            }
            else if(stk.empty() || c == '(' || op[c] > op[stk.top()])//情况1、情况3
            {
                stk.push(c);
            }
            else if(op[c] <= op[stk.top()])//情况3
            {
                while(op[c] <= op[stk.top()] && (!stk.empty()))
                {
                    rettifyExpress(result);
                    result.append(stk.top());
                    stk.pop();
                    if(stk.empty()) break;
                }
                stk.push(c);
            }

            rettifyExpress(result);
        }
        else
        {
            result.append(c);
        }
    }

    while(stk.empty() == false)//当中缀表达式输出完成，所有元素出栈
    {
        rettifyExpress(result);
        result.append(stk.top());
        stk.pop();
    }

    return result;
}

//计算表达式值
double MainWindow::CalExp(const QStringList & express)
{
    double result;
    QStack<QString> stk;
    for (int i = 0; i < express.size(); ++i)
    {
        QString item = express[i];
        if (item.size() == 1 &&
            (item.at(0) == "+" || item.at(0) == "-" || item.at(0) == "*" || item.at(0) == "/"))
        {
            double r = stk.pop().toDouble();
            double l = stk.pop().toDouble();
            switch(item.at(0).toLatin1())
            {
            case '+':
                result = l + r;break;
            case '-':
                result = l - r;break;
            case '*':
                result = l * r;break;
            case '/':
                result = l / r;break;
            }

            stk.push_back(QString::number(result));
        }
        else
        {
            stk.push_back(item);
        }
    }

    return result;
}

void MainWindow::on_pushButtonLeft_released()
{//输入(
    leftBracket+=1;//左括号个数
    ui->lineEditNumber->setText(ui->lineEditNumber->text()+"(");
}


void MainWindow::on_pushButtonRight_released()
{//输入)
    rightBracket+=1;//右括号个数
    ui->lineEditNumber->setText(ui->lineEditNumber->text()+")");
}


void MainWindow::on_pushButtonDelete_released()
{//删除最后一位
    QString equation = ui->lineEditNumber->text();
    int length=equation.length();
    ui->lineEditNumber->setText(equation.mid(0,length-1));
}

