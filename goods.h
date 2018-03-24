#ifndef GOODS_H
#define GOODS_H

#include <QString>
#include <QjsonObject>

class goods
{
public:
    goods();
    goods(const QString &name, int quantity);

    void set_name(const QString &name);
    QString name();
    void set_quantity(int quantity);
    int quantity();

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
private:
    QString mname;
    int mquantity;
};

#endif // GOODS_H
