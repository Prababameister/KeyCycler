#include <cycle.hh>

Cycle::Cycle(QObject* parent) : QObject(parent) {};

// Retrieve data
int Cycle::current() {
    return m_current;
}
const QList<Keyboard*>& Cycle::kbList() {
    return m_kbList;
}

int Cycle::getCycleSize() {
    return m_kbList.size();
}
Keyboard* Cycle::getKb(int index) {
    return m_kbList[index];
}

// Modify data
void Cycle::setCurrent(int current) {
    m_current = current;
}
void Cycle::setKbList(QList<Keyboard*>& kbList) {
    m_kbList.clear();
    m_kbList.append(kbList);
}

void Cycle::addKb(Keyboard* kb) {
    m_kbList.append(kb);
    emit kbListChanged();
}
void Cycle::removeKb(int index) {
    m_kbList.removeAt(index);
}

void Cycle::applyCurrent() {
    std::string command = "setxkbmap " + m_kbList[m_current]->abbrev().toStdString();
    system(command.c_str());
}
