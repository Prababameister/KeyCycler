#include <cycle_list.hh>
#include <QObject>

CycleList::CycleList(QObject* parent) : QObject(parent) {}

// Retrieve data
int CycleList::current() {
    return m_current;
}
const QList<Cycle*>& CycleList::cycleList() {
    return m_cycleList;
}

int CycleList::getCycleListSize() {
    return m_cycleList.size();
}
Cycle* CycleList::getCycle(int index) {
    return m_cycleList[index];
}

// Modify data
void CycleList::setCurrent(int current) {
    m_current = current;
}
void CycleList::setCycleList(QList<Cycle*> &cycleList) {
    m_cycleList = cycleList;
}

void CycleList::addCycle(Cycle* cycle) {
    m_cycleList.push_back(cycle);
}
void CycleList::removeCycle(int index) {
    m_cycleList.removeAt(index);
}
