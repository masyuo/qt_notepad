//
// Created by Aaron on 6/15/2017.
//
#include <QtCore/QTextStream>
#include "notepad.h"

notepad::notepad()
{
    createMenuBar();

    documentArea = new QTextEdit;
    setCentralWidget(documentArea);

    connect(documentArea, &QTextEdit::textChanged, this, &notepad::textChanged);

    setCurrentFile("");
    resize(1280, 720);
}

void notepad::createMenuBar()
{
    menuBar = new QMenuBar();

    QMenu *fileMenu = menuBar->addMenu("File");
    QAction *newDoc = fileMenu->addAction("New");
    QAction *openDoc = fileMenu->addAction("Open");
    QAction *saveDoc = fileMenu->addAction("Save");
    QAction *saveDocAs = fileMenu->addAction("Save As");
    fileMenu->addSeparator();
    QAction *exit = fileMenu->addAction("Exit");

    connect(newDoc, &QAction::triggered, this, &notepad::newDocument);
    connect(openDoc, &QAction::triggered, this, &notepad::openDocument);
    connect(saveDoc, &QAction::triggered, this, &notepad::saveDocument);
    connect(saveDocAs, &QAction::triggered, this, &notepad::saveDocumentAs);
    connect(exit, &QAction::triggered, this, &QCoreApplication::exit);

    setMenuBar(menuBar);
}

void notepad::setCurrentFile(QString file)
{
    QFileInfo info(file);
    currentFile = file;

    setWindowTitle((currentFile.isEmpty() ? "Untitled" : info.fileName()) + "[*] - " + QCoreApplication::applicationName());

    setWindowModified(false);
}

void notepad::textChanged()
{
    setWindowModified(true);
}

void notepad::newDocument()
{
    documentArea->clear();
    setCurrentFile("");
}

void notepad::openDocument()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open document", "", "Text files (*.txt);;All files (*)");

    if(!fileName.isEmpty())
    {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, "Unable to open file.", file.errorString());
            return;
        }

        QTextStream in(&file);
        QString line;

        while((line = in.readLine()) != NULL)
        {
            documentArea->append(line);
        }

        setCurrentFile(fileName);
    }
}

void notepad::saveDocument()
{
    save();
    setWindowModified(false);
}

void notepad::saveDocumentAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Open document", "", "Text files (*.txt);;All files (*)");

    if(!fileName.isEmpty())
    {
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, "Unable to open file.", file.errorString());
            return;
        }

        setCurrentFile(fileName);
        save();
    }
}

void notepad::save()
{
    QFile file(currentFile);

    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, "Unable to open file.", file.errorString());
        return;
    }

    QTextStream out(&file);
    out << documentArea->toPlainText();


}
