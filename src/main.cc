#include "keyboard.hh"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <json/json.h>
#include <json/reader.h>
#include <json/value.h>

#include <iostream>
#include <fstream>
#include <filesystem>

#include <cycle_list.hh>

CycleList cycleList;

int init_backend() {
    std::ifstream file(CONFIG_DIR "/cycles.json");
    if(!file.is_open()) {
        try {
            std::filesystem::copy_file(PROJECT_HEAD "/resources/cycles.scaffold.json",
                                       CONFIG_DIR "/cycles.json",
                                       std::filesystem::copy_options::overwrite_existing);
        } catch (std::exception& e) {
            std::cout << e.what();
        }

        file.open(CONFIG_DIR "/cycles.json");
    }

    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();
    Json::Value root;

    std::string errs;
    if(!Json::parseFromStream(builder, file, &root, &errs)) {
        std::cerr << "Failed to parse JSON: " << errs << std::endl;
        return 1;
    }

    Json::Value raw_cycles = root["cycles"];
    for (int i = 0; i < raw_cycles.size(); ++i) {
        int kbListSize = raw_cycles[i]["keyboards"].size();

        Cycle* cyc = new Cycle{};
        for (int j = 0; j < kbListSize; ++j) {
            Json::Value& raw_kb = raw_cycles[i]["keyboards"][j];
            Keyboard* kb = new Keyboard{};
            kb->setFull(QString::fromStdString(raw_kb["full"].asString()));
            kb->setAbbrev(QString::fromStdString(raw_kb["abbrev"].asString()));
            cyc->addKb(kb);
        }
        cyc->setCurrent(raw_cycles[i]["current_kb"].asInt());
        cycleList.addCycle(cyc);
    }

    return 0;
}

int main(int argc, char *argv[]) {
    // Init sequence
    std::cout << init_backend();

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("cycleList", &cycleList);

    const QUrl url(QStringLiteral(PROJECT_HEAD "/qml/main.qml"));
    engine.load(url);

    return app.exec();
}
