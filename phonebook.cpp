#include "PhoneBook.h"
#include <fstream>
#include <QStringList>
#include <QInputDialog>
#include <QMessageBox>

void PhoneBook::addContact(const QString& name, const QString& number) {
    phoneBook[name].push_back(number);
}

void PhoneBook::deleteContact(const QString& name) {
    auto it = phoneBook.find(name);
    if (it != phoneBook.end()) {
        phoneBook.erase(it);
    }
    else {
        QMessageBox::information(nullptr, "Contact Not Found", "The contact was not found.");
    }
}

void PhoneBook::editContact(QWidget* parent, const QString& name) {
    auto it = phoneBook.find(name);

    if (it != phoneBook.end()) {
        int choice = QInputDialog::getInt(parent, "Edit Contact",
                                          "Select what to edit:\n"
                                          "1. Name\n"
                                          "2. Number\n", 1, 1, 2, 1);
        if (choice == 1) {
            QString newName = QInputDialog::getText(parent, "Enter New Name", "Enter new name:");
            phoneBook[newName] = it->second;
            phoneBook.erase(it);
        } else if (choice == 2) {
            QString newNumber = QInputDialog::getText(parent, "Enter New Number", "Enter new number:");
            it->second[0] = newNumber;
        }
    }
    else {
        QMessageBox::information(nullptr, "Contact Not Found", "The contact was not found.");
    }
}


QStringList PhoneBook::displayPhoneBook() const {
    QStringList phoneBookList;
    for (const auto& record : phoneBook) {
        QString contactInfo = record.first + ": ";
        int i = 0;
        for (const auto& number : record.second) {
            if (i == 0) {
                contactInfo += number + " - ";
                i++;
            }
            else {
                contactInfo += QString::number(i) + ". " + number + "; ";
                i++;
            }
        }
        phoneBookList << contactInfo;
    }
    return phoneBookList;
}


QString PhoneBook::searchContact(const QString& name) const {
    auto it = phoneBook.find(name);
    if (it != phoneBook.end()) {
        QString contactInfo = "Contact found: " + it->first + ": ";
        bool isFirst = true;
        for (const auto& number : it->second) {
            if (isFirst) {
                contactInfo += number + " - ";
                isFirst = false;
            }
            else
                contactInfo += number + "; ";
        }
        return contactInfo;
    }
    else {
        return "Contact not found.";
    }
}

void PhoneBook::addNoteToContact(QWidget* parent, const QString& name){
    auto it = phoneBook.find(name);
    if (it != phoneBook.end()) {
        QString note = QInputDialog::getText(parent, "Enter Note", "Enter note:");
        it->second.push_back(note);
    }
    else {
        QMessageBox::information(nullptr, "Contact Not Found", "The contact was not found.");
    }
}

void PhoneBook::deleteNoteFromContact(const QString& name) {
    auto it = phoneBook.find(name);
    if (it != phoneBook.end()) {
        QString notes;
        int i = 0;
        for (const auto& note : it->second) {
            if(i>0)
                notes += QString::number(i) + ". " + note + "; \n";
            i++;
        }

        int noteIndex = QInputDialog::getInt(nullptr, "Delete Note", "Current notes:\n" + notes +
                                                                         "\nEnter the note index to delete (starting from 1):",
                                             1, 1, it->second.size() - 1, 1);

            it->second.erase(it->second.begin() + (noteIndex));
    }
    else {
            QMessageBox::information(nullptr, "Contact Not Found", "The contact was not found.");
    }
}




void PhoneBook::loadFromFile(const QString& filename) {
    phoneBook.clear();
    std::ifstream file(filename.toStdString());
    if (file.is_open()) {
        std::string line;
        std::string name, number, note;
        bool i = true;

        while (std::getline(file, line)) {
            if (line == ".") {
                i = true;
                continue;
            }
            if (i == true) {
                name = line;
                i = false;
            }
            else {
                phoneBook[QString::fromStdString(name)].push_back(QString::fromStdString(line));
            }
        }
        file.close();
    }
    else {
         QMessageBox::information(nullptr, "Error File", "Unable to open file.");
    }
}

void PhoneBook::saveToFile(const QString& filename) {
    std::ofstream file(filename.toStdString());
    if (file.is_open()) {
        for (const auto& record : phoneBook) {
            file << record.first.toStdString() << std::endl;
            file << record.second[0].toStdString() << std::endl;
            for (int i = 1; i < record.second.size(); ++i) {
                file << record.second[i].toStdString() << std::endl;
            }
            file << "." << std::endl;
        }
        file.close();
        QMessageBox::information(nullptr, "File saved", "File saved successfully.");
    }
    else {
        QMessageBox::information(nullptr, "Error File", "Unable to open file.");
    }
}
