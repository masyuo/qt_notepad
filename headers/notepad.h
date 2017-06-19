//
// Created by Aaron on 6/15/2017.
//

#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QTextEdit>
#include <QCoreApplication>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QClipboard>
#include <QMimeData>
#include <QDateTime>
#include <QShortcut>

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
    void undo();
    void cut();
    void copy();
    void paste();
    void deleteSelection();
    void timeAndDate();
private:
    void createMenuBar();
    void createShortcuts();
    void setCurrentFile(QString file);
    void save();
    QMenuBar *menuBar;
    QTextEdit *documentArea;

    QString currentFile;
};

#endif //NOTEPAD_H
