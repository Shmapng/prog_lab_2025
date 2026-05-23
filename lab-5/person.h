#ifndef PERSON_H
#define PERSON_H

#include <QString>

struct Date
{
    int day;
    int month;
    int year;
};

class Person
{
public:
    QString surname;
    QString name;
    Date birth;

    virtual QString Craft() = 0;

    virtual ~Person() {}
};

class ParentPerson : public Person
{
public:
    QString father;

    QString Craft() override
    {
        return
            "Фамилия: " + surname + "\n" +
            "Имя: " + name + "\n" +
            "Отчество: " + father + "\n" +
            "Дата: " +
            QString("%1.%2.%3")
                .arg(birth.day,2,10,QChar('0'))
                .arg(birth.month,2,10,QChar('0'))
                .arg(birth.year);
    }
};

class ChildPerson : public Person
{
public:
    QString secondName;

    QString Craft() override
    {
        return
            "Имя: " + name + "\n" +
            "Второе имя: " + secondName + "\n" +
            "Фамилия: " + surname + "\n" +
            "Дата: " +
            QString("%1-%2-%3")
                .arg(birth.month,2,10,QChar('0'))
                .arg(birth.day,2,10,QChar('0'))
                .arg(birth.year);
    }
};

#endif
