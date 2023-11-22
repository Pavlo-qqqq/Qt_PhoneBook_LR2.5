#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->addContactButton, &QPushButton::clicked, this, &MainWindow::onAddContactButtonClicked);
    connect(ui->deleteContactButton, &QPushButton::clicked, this, &MainWindow::onDeleteContactButtonClicked);
    connect(ui->editContactButton, &QPushButton::clicked, this, &MainWindow::onEditContactButtonClicked);
    connect(ui->searchContactButton, &QPushButton::clicked, this, &MainWindow::onSearchContactButtonClicked);
    connect(ui->addNoteButton, &QPushButton::clicked, this, &MainWindow::onAddNoteToContactButtonClicked);
    connect(ui->deleteNoteButton, &QPushButton::clicked, this, &MainWindow::onDeleteNoteButtonClicked);
    connect(ui->loadFromFileButton, &QPushButton::clicked, this, &MainWindow::onLoadFromFileButtonClicked);
    connect(ui->saveToFileButton, &QPushButton::clicked, this, &MainWindow::onSaveToFileButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddContactButtonClicked()
{
    QString name = QInputDialog::getText(this, "Enter Name", "Enter contact name:");
    QString number = QInputDialog::getText(this, "Enter Number", "Enter contact number:");
    phoneBook.addContact(name, number);
    updateTable();
}

void MainWindow::onDeleteContactButtonClicked()
{
    QString name = QInputDialog::getText(this, "Enter Name", "Enter contact name to delete:");
    phoneBook.deleteContact(name);
    updateTable();
}

void MainWindow::onEditContactButtonClicked()
{
    QString name = QInputDialog::getText(this, "Enter Name", "Enter contact name to edit:");
    phoneBook.editContact(this, name);
    updateTable();
}

void MainWindow::onSearchContactButtonClicked()
{
    QString name = QInputDialog::getText(this, "Enter Name", "Enter contact name to search:");
    QString result = phoneBook.searchContact(name);
    QMessageBox::information(this, "Search Result", result);
    updateTable();
}

void MainWindow::onAddNoteToContactButtonClicked()
{
    QString name = QInputDialog::getText(this, "Enter Name", "Enter contact name to add note:");
    phoneBook.addNoteToContact(this, name);
    updateTable();
}

void MainWindow::onDeleteNoteButtonClicked()
{
    QString name = QInputDialog::getText(this, "Enter Name", "Enter contact name to delete note from:");
    phoneBook.deleteNoteFromContact(name);
    updateTable();
}

void MainWindow::onLoadFromFileButtonClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Phone Book"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (!fileName.isEmpty()) {
        phoneBook.loadFromFile(fileName);
        updateTable();
    }
}

void MainWindow::onSaveToFileButtonClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Phone Book"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (!fileName.isEmpty()) {
        phoneBook.saveToFile(fileName);
    }
}

void MainWindow::updateTable() {
    ui->tableWidget->clear();

    QStringList phoneBookList = phoneBook.displayPhoneBook();

    ui->tableWidget->setRowCount(phoneBookList.size());

    ui->tableWidget->setColumnCount(3);

    for (int i = 0; i < phoneBookList.size(); ++i) {
        QStringList rowData = phoneBookList.at(i).split(": ");
        if (rowData.size() >= 2) {
            QTableWidgetItem *nameItem = new QTableWidgetItem(rowData.at(0));

            QString numbersString = rowData.at(1);
            QStringList numbersAndNotes = numbersString.split(" - ");

            QTableWidgetItem *numberItem = nullptr;
            QTableWidgetItem *notesItem = nullptr;

            if (!numbersAndNotes.isEmpty()) {
                numberItem = new QTableWidgetItem(numbersAndNotes.first());

                if (numbersAndNotes.size() > 1) {
                    numbersAndNotes.removeFirst();

                    QString notesString = numbersAndNotes.join("\n");
                    notesItem = new QTableWidgetItem(notesString);
                }
            }

            ui->tableWidget->setItem(i, 0, nameItem);
            ui->tableWidget->setItem(i, 1, numberItem);

            if (notesItem != nullptr) {
                ui->tableWidget->setItem(i, 2, notesItem);
            }
        }
    }
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Name" << "Number" << "Notes");
    ui->tableWidget->resizeColumnToContents(0);
    ui->tableWidget->resizeColumnToContents(1);
    ui->tableWidget->resizeColumnToContents(2);
}
