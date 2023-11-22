#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <map>
#include <vector>
#include <QString>
#include <QWidget>

class PhoneBook {
private:
    typedef std::vector<QString> Vectype;
    typedef std::map<QString, Vectype, std::less<QString>> Maptype;

    Maptype phoneBook;

public:
    void addContact(const QString& name, const QString& number);
    void deleteContact(const QString& name);
    void editContact(QWidget* parent, const QString& name);
    QStringList displayPhoneBook() const;
    QString searchContact(const QString& name) const;
    void addNoteToContact(QWidget* parent, const QString& name);
    void deleteNoteFromContact(const QString& name);
    void loadFromFile(const QString& filename);
    void saveToFile(const QString& filename);
};

#endif // PHONEBOOK_H
