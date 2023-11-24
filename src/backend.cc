#include <backend.hh>
#include <regex>
#include <string>

Backend::Backend() {
    reader = builder.newCharReader();
}

void Backend::retrieveCycles(CycleList &cycleList, std::string path) {
    Json::Value root;

    file.open(path.c_str(), std::ios::in);

    std::string errs;
    if(!Json::parseFromStream(builder, file, &root, &errs)) {
        std::cerr << "Failed to parse JSON: " << errs << std::endl;
        return;
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
        cyc->setCurrent(raw_cycles[i]["current"].asInt());
        cycleList.addCycle(cyc);
    }
    cycleList.setCurrent(root["current"].asInt());

    file.close();
}

void Backend::saveCycles(CycleList &cycleList, std::string path) {
    Json::Value root;
    root["current"] = cycleList.current();

    Json::Value cycles(Json::arrayValue);
    for(int i = 0; i < cycleList.getCycleListSize(); ++i) {
        Json::Value j_cyc;
        Cycle* p_cyc = cycleList.getCycle(i);

        Json::Value kbs(Json::arrayValue);
        j_cyc["current"] = p_cyc->current();
        for(int j = 0; j < p_cyc->getCycleSize(); ++j) {
            Json::Value j_kb;
            Keyboard* p_kb = p_cyc->getKb(j);

            j_kb["full"] = p_kb->full().toLocal8Bit().data();
            j_kb["abbrev"] = p_kb->abbrev().toLocal8Bit().data();

            kbs.append(j_kb);
        }
        j_cyc["keyboards"] = kbs;

        cycles.append(j_cyc);
    }
    root["cycles"] = cycles;

    file.open(path, std::ios_base::out | std::ios_base::trunc);
    file.clear();

    std::string j_root = root.toStyledString();
    file.write(j_root.c_str(), j_root.size());

    file.close();
}


void Backend::retrieveKbLayouts(Cycle& masterCycle, std::string path) {
    bool reachedLayouts = false;
    file.open(path);

    std::string line;

    std::regex kb_desc(R"(^\s{2}([a-zA-Z]+)\s+(.+)$)");
    while(std::getline(file, line)) {
        if (line == "! layout") {
            reachedLayouts = true;
            continue;
        }
        if (reachedLayouts && line == "! variant")
            break;
        if (!reachedLayouts)
            continue;

        std::smatch match;
        if(std::regex_match(line, match, kb_desc)) {
            if(match.size() == 3) {
                std::string abbrev = match[1].str();
                std::string full = match[2].str();
                Keyboard* kb = new Keyboard();
                kb->setAbbrev(QString::fromStdString(abbrev));
                kb->setFull(QString::fromStdString(full));

                masterCycle.addKb(kb);
            }
        }
    }
    file.close();
}

bool Backend::exists(std::string path) {
    file.open(path.c_str());
    bool result = file.is_open();
    file.close();
    return result;
}
