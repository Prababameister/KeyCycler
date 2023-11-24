#pragma once

#include <QObject>
#include <QList>

#include <keyboard.hh>

class Cycle : public QObject {
	Q_OBJECT
	Q_PROPERTY(int current READ current WRITE setCurrent NOTIFY currentChanged)
	Q_PROPERTY(QList<Keyboard*> kbList READ kbList WRITE setKbList NOTIFY kbListChanged)

    public:
        explicit Cycle(QObject* parent = nullptr);

        int current();
        const QList<Keyboard*>& kbList();

        Q_INVOKABLE int getCycleSize();
        Q_INVOKABLE Keyboard* getKb(int index);

    public slots:
        void setCurrent(int current);
        void setKbList(QList<Keyboard*>& kbList);

        Q_INVOKABLE void addKb(Keyboard* kb);
        Q_INVOKABLE void removeKb(int index);

        Q_INVOKABLE void applyCurrent();

    signals:
        void currentChanged();
        void kbListChanged();

    private:
        int m_current = -1;
        QList<Keyboard*> m_kbList;
};
