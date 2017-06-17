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
    QAction *newAction = fileMenu->addAction("New");
    QAction *openAction = fileMenu->addAction("Open");
    QAction *saveAction = fileMenu->addAction("Save");
    QAction *saveAsAction = fileMenu->addAction("Save As");
    fileMenu->addSeparator();
    QAction *exitAction = fileMenu->addAction("Exit");

    connect(newAction, &QAction::triggered, this, &notepad::newDocument);
    connect(openAction, &QAction::triggered, this, &notepad::openDocument);
    connect(saveAction, &QAction::triggered, this, &notepad::saveDocument);
    connect(saveAsAction, &QAction::triggered, this, &notepad::saveDocumentAs);
    connect(exitAction, &QAction::triggered, this, &QCoreApplication::exit);

    QMenu *editMenu = menuBar->addMenu("Edit");
    QAction *undoAction = editMenu->addAction("Undo");
    QAction *redoAction = editMenu->addAction("Redo");
    editMenu->addSeparator();
    QAction *cutAction = editMenu->addAction("Cut");
    QAction *copyAction = editMenu->addAction("Copy");
    QAction *pasteAction = editMenu->addAction("Paste");
    QAction *deleteAction = editMenu->addAction("Delete");
    editMenu->addSeparator();
    QAction *timeAction = editMenu->addAction("Time and Date");

    connect(undoAction, &QAction::triggered, this, &notepad::undo);
    connect(redoAction, &QAction::triggered, this, &notepad::redo);
    connect(cutAction, &QAction::triggered, this, &notepad::cut);
    connect(copyAction, &QAction::triggered, this, &notepad::copy);
    connect(pasteAction, &QAction::triggered, this, &notepad::paste);
    connect(deleteAction, &QAction::triggered, this, &notepad::deleteSelection);
    connect(timeAction, &QAction::triggered, this, &notepad::timeAndDate);

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
        file.close();
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
        file.close();
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

    file.close();
}

void  notepad::undo()
{
    documentArea->undo();
}

void notepad::redo()
{
    documentArea->redo();
}

void notepad::cut()
{
    documentArea->cut();
}

void notepad::copy()
{
    documentArea->copy();
}

void notepad::paste()
{
    const QClipboard *clipboard = QGuiApplication::clipboard();
    const QMimeData *mimeData = clipboard->mimeData();
    documentArea->insertPlainText(mimeData->text());
}

void notepad::deleteSelection()
{
    documentArea->textCursor().removeSelectedText();
}

void notepad::timeAndDate()
{
    QDateTime time = QDateTime::currentDateTime();

    documentArea->append(time.toString("h:mm AP M/d/yy"));
}