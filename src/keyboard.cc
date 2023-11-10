#include <keyboard.hh>

Keyboard::Keyboard(QObject* parent) : QObject(parent) {}

QString Keyboard::full() {
    return m_full;
}
QString Keyboard::abbrev() {
    return m_abbrev;
}

void Keyboard::setFull(QString full) {
    m_full = full;
}
void Keyboard::setAbbrev(QString abbrev) {
    m_abbrev = abbrev;
}

void Keyboard::fullChanged() {};
void Keyboard::abbrevChanged() {};
