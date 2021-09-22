#include "headers/data/response.h"

Response::Response(const QString &text, int id, int questionID, QObject *parent)
    : QObject(parent), text_(text), id_(id), questiondID_(questionID) {}

QString Response::text() const { return text_; }

int Response::id() const { return id_; }

int Response::questionID() const { return questiondID_; }
