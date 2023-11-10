#pragma once

#include <QObject>

class Keyboard : public QObject {
	Q_OBJECT
	Q_PROPERTY(QString full READ full WRITE setFull NOTIFY fullChanged)
	Q_PROPERTY(QString abbrev READ abbrev WRITE setAbbrev NOTIFY abbrevChanged)

	public:
		explicit Keyboard(QObject* parent = nullptr);

		QString full();
		QString abbrev();

	public slots:
		void setFull(QString full);
		void setAbbrev(QString abbrev);

	signals:
		void fullChanged();
		void abbrevChanged();

	private:
		QString m_full;
		QString m_abbrev;
};
