#ifndef MANAGER_H
#define MANAGER_H
#include <QString>

class Manager
{
public:
    Manager();
    void setModel(QString model){
        this->model = model;
    }

    void setSerial(QString serial){
        this->serial = serial;
    }
    void setManufacturer(QString manu){
        this->manu = manu;
    }


    QString getSerial(){return serial;};
    QString getModel(){return model;}
    QString getManufacturer(){return manu;}



    QString formatStringWithSpaces(const QString &input);
    long long recupererMeilleurScore(const QString &file);

private:
    QString model;
    QString serial;
    QString manu;

};

#endif // MANAGER_H
