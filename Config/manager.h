#ifndef MANAGER_H
#define MANAGER_H
#include <QString>

// Class pour récupérer les varibles entre les fonctions
class Manager
{
public:
    Manager();

    //Set
    void setModel(QString model){
        this->model = model;
    }

    void setSerial(QString serial){
        this->serial = serial;
    }
    void setManufacturer(QString manu){
        this->manu = manu;
    }

    //Get
    QString getSerial(){return serial;};
    QString getModel(){return model;}
    QString getManufacturer(){return manu;}






private:
    QString model;
    QString serial;
    QString manu;

};

#endif // MANAGER_H
