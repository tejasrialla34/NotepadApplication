#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include<QFileDialog>
#include<QFontDialog>
#include<QFontInfo>
#include<QFont>
#include<QtPrintSupport/QPrinter>
#include<QtPrintSupport/QPrintDialog>
#include<QColor>
#include<QColorDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionNew_triggered()
{
    file_path=" ";
       ui->textEdit->setText(" ");
}

void MainWindow::on_actionOpen_triggered()
{
    QString file_name=QFileDialog::getOpenFileName(this,"Open the File");
       QFile file(file_name);
       file_path=file_name;
       if(!file.open(QFile::ReadOnly|QFile::Text))
       {
           QMessageBox::warning(this,"..","File not open");
           return;
       }
       QTextStream in(&file);
       QString text=in.readAll();
       ui->textEdit->setText(text);
       file.close();
}

void MainWindow::on_actionSave_triggered()
{

    QFile file(file_path);
       if(!file.open(QFile::WriteOnly|QFile::Text))
       {
           QMessageBox::warning(this,"..","File not open");
           return;
       }
       QTextStream out(&file);
       QString text=ui->textEdit->toPlainText();
       out<<text;
       file.flush();
       file.close();
}

void MainWindow::on_actionSave_As_triggered()
{
    QString file_name=QFileDialog::getSaveFileName(this,"Save the File");
        QFile file(file_path);
        file_path=file_name;
        if(!file.open(QFile::WriteOnly|QFile::Text))
        {
            QMessageBox::warning(this,"..","File not open");
            return;
        }
        QTextStream out(&file);
        QString text=ui->textEdit->toPlainText();
        out<<text;
        file.flush();
        file.close();
}

void MainWindow::on_actionAbout_Qt_triggered()
{
     QMessageBox::information(this,"ABOUT QT","Qt is a cross-platform application development framework for desktop, embedded and mobile");
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionSelectFont_triggered()
{
    bool fontselected;
        QFont font=QFontDialog::getFont(&fontselected,this);
        if(fontselected)
        {
            ui->textEdit->setFont(font);
        }
}


void MainWindow::on_actionBold_triggered()
{
    ui->textEdit->setFontWeight(QFont::Bold);
}

void MainWindow::on_actionUnderline_triggered()
{
     ui->textEdit->setFontUnderline(true);
}

void MainWindow::on_actionItalic_triggered()
{
    ui->textEdit->setFontItalic(true);
}

void MainWindow::on_actionFontcolor_triggered()
{
    QColor fc=QColorDialog::getColor(Qt::white,this,"Choose a Fontcolor");
        if(fc.isValid())
        {
            ui->textEdit->setTextColor(fc);
        }
}

void MainWindow::on_actionFont_Backgroundcolor_triggered()
{
    QColor fc=QColorDialog::getColor(Qt::white,this,"Choose a background color");
       if(fc.isValid())
       {
           ui->textEdit->setTextBackgroundColor(fc);
       }
}



void MainWindow::on_actionPrint_triggered()
{
    QPrinter p;
        p.setPrinterName("HP Laser Jet");
        QPrintDialog pd(&p,this);
        if(pd.exec()==QDialog::Rejected)
        {
            QMessageBox::warning(this,"Error","Can't access printer");
            return;
        }
        ui->textEdit->print(&p);
}
