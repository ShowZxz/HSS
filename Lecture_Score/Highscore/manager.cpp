#include "manager.h"

Manager::Manager() {}

QString Manager::formatStringWithSpaces(const QString &input){
    QString formattedString;
    if(input.isEmpty()){
        return "None";
    } else{
        int count = 0;

        for (int i = input.length() - 1; i >= 0; --i) {
            formattedString.prepend(input.at(i));
            count++;

            if (count == 3 && i != 0) {
                formattedString.prepend(" ");
                count = 0;
            }
        }

        return formattedString;
    }
}

QString Manager::Manager::setZeroToOne(const QString &input){
    if(input=="-1"){
        return "";
    }
    if(input=="0"){
        return "";
    }
    if (input=="1"){
        return "";
    }
    return input;

}



