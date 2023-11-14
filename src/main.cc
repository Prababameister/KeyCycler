#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <fstream>
#include <iostream>

#include <json/json.h>
#include <json/reader.h>
#include <json/value.h>

#include <backend.hh>
#include <cycle_list.hh>

CycleList cycleList;
Backend back;

int main(int argc, char *argv[]) {
    // Init sequence
    if(back.exists(CONFIG_DIR "/cycles.json")) {
        std::ofstream file(CONFIG_DIR "/cycles.json");
        file << "{}";
    }

    back.retrieveCycles(cycleList, CONFIG_DIR "/.cycles.json");

    for(int i = 0; i < cycleList.getCycleListSize(); ++i) {
        Cycle* cyc = cycleList.getCycle(i);
        std::cout << "Cycle: " << i << "\n";
        for(int j = 0 ; j < cyc->getCycleSize(); ++j) {
            std::cout << "KB " << j << "\n";
            Keyboard* kb = cyc->getKb(j);
            std::cout << kb->abbrev().toStdString() << "\n";
            std::cout << kb->full().toStdString() << "\n";
        }
    }

    Cycle* cyc = new Cycle();
    Keyboard* kb = new Keyboard();

    kb->setFull("fuck");
    kb->setAbbrev("shit");
    cyc->addKb(kb);

    cycleList.addCycle(cyc);

    back.saveCycles(cycleList, CONFIG_DIR "/cycles.json");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("cycleList", &cycleList);

    const QUrl url(QStringLiteral(PROJECT_HEAD "/qml/main.qml"));
    engine.load(url);

    return app.exec();
}
