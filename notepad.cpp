#include "notepad.h"
#include "ui_notepad.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFont>
#include <QFontDialog>
#include <QColor>
#include <QColorDialog>
#include <QPrinter>
#include <QPrintDialog>

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

Notepad::~Notepad()
{
    delete ui;
}


void Notepad::on_actionNew_triggered()
{
    file_path = "";
    ui->textEdit->setText("");
}

void Notepad::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Open File");
    QFile file(file_name);
    file_path = file_name;
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"..","File Not Opened!");
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void Notepad::on_actionSave_triggered()
{
    QFile file(file_path);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        //QMessageBox::warning(this,"..","File Not Opened!");
        //return;
        Notepad::on_actionSave_As_triggered();
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void Notepad::on_actionSave_As_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this,"Open File");
    QFile file(file_name);
    file_path = file_name;
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,"..","File Not Opened!");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void Notepad::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void Notepad::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void Notepad::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void Notepad::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void Notepad::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void Notepad::on_actionAbout_Notepad_triggered()
{
    QString about_text;
    about_text = "Author: Basillica \n";
    about_text += "Date: 01.06.2020 \n";
    about_text += "Email: etienneceasar@gmail.com";
    QMessageBox::about(this,"About Notepad ",about_text);
}

void Notepad::on_actionFont_triggered()
{
    bool is_font;
    QFont font = QFontDialog::getFont(&is_font,this);
    if (is_font)
    {
        ui->textEdit->setFont(font);
        ui->statusbar->showMessage("Done!",4000);
    }
    else return;
}

void Notepad::on_actionColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"Choose your color!");
    if (color.isValid())
    {
        ui->textEdit->setTextColor(color);
    }
}

void Notepad::on_actionBackground_Color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"Choose your color!");
    if (color.isValid())
    {
        ui->textEdit->setTextBackgroundColor(color);
    }
}

void Notepad::on_actionWindow_Background_Color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"Choose your color!");
    if (color.isValid())
    {
        ui->textEdit->setPalette(QPalette(color));
    }
}

void Notepad::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("My Printer");
    QPrintDialog dialog(&printer,this);
    if (dialog.exec() == QDialog::Rejected) return;
    ui->textEdit->print(&printer);
}

void Notepad::on_actionQuit_triggered()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,
                                        "Quit Dialog","Do you want to quit?",
                                        QMessageBox::Yes |QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QApplication::quit();
    }
    else
    {
        return;
    }
}
