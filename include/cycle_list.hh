#pragma once

#include <iostream>

#include <QObject>
#include <QList>

#include <cycle.hh>

class CycleList : public QObject {
	Q_OBJECT
	Q_PROPERTY(int current READ current WRITE setCurrent NOTIFY currentChanged)
	Q_PROPERTY(QList<Cycle*> cycleList READ cycleList WRITE setCycleList NOTIFY cycleListChanged)

    public:
        explicit CycleList(QObject* parent = nullptr);

        int current();
        const QList<Cycle*>& cycleList();

        Q_INVOKABLE int getCycleListSize();
        Q_INVOKABLE Cycle* getCycle(int index);

    public slots:
        void setCurrent(int current);
        void setCycleList(QList<Cycle*>& kbList);

        Q_INVOKABLE void addCycle();
        Q_INVOKABLE void addCycle(Cycle* cycle);
        Q_INVOKABLE void removeCycle(int index);

    signals:
        void currentChanged();
        void cycleListChanged();

    private:
        int m_current = -1;
        QList<Cycle*> m_cycleList;
};
