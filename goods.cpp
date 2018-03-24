#include "goods.h"

goods::goods() {
    mname = ""; mquantity = 0;
}
goods::goods(const QString &name, int quantity) {
    mname = name; mquantity = quantity;
}

void goods::set_name(const QString &name) {
    mname = name;
}
QString goods::name() {
    return mname;
}
void goods::set_quantity(int quantity) {
    mquantity = quantity;
}
int goods::quantity() {
    return mquantity;
}

void goods::read(const QJsonObject &json) {
    if (json.contains("name") && json["name"].isString()) {
        mname = json["name"].toString();
    }
    if (json.contains("quantity") && json["quantity"].isDouble()) {
        mquantity = json["quantity"].toInt();
    }
}

void goods::write(QJsonObject &json) const {
    json["name"] = mname;
    json["quantity"] = mquantity;
}
