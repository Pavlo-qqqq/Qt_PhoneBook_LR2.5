#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "PhoneBook.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddContactButtonClicked();
    void onDeleteContactButtonClicked();
    void onEditContactButtonClicked();
    void onSearchContactButtonClicked();
    void onAddNoteToContactButtonClicked();
    void onLoadFromFileButtonClicked();
    void onSaveToFileButtonClicked();
    void onDeleteNoteButtonClicked();

private:
    Ui::MainWindow *ui;
    PhoneBook phoneBook;
    void updateTable();
};

#endif // MAINWINDOW_H

