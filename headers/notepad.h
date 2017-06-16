//
// Created by Aaron on 6/15/2017.
//

#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>
#include <QMenuBar>
#include <QTextEdit>
#include <QCoreApplication>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>

class notepad : public QMainWindow
{
    Q_OBJECT
public:
    notepad();
private slots:
    void textChanged();
    void newDocument();
    void openDocument();
    void saveDocument();
    void saveDocumentAs();
private:
    void createMenuBar();
    void setCurrentFile(QString file);
    void save();
    QMenuBar *menuBar;
    QTextEdit *documentArea;

    QString currentFile;
};

#endif //NOTEPAD_H
