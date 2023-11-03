#pragma once

#include <string>
#include <vector>

class Cycle {
    public:
        struct Keyboard {
            std::string full;
            std::string abbrev;
        };

        int get_cycle_size() {
            return keyboard_list.size();
        }

        Keyboard* get_keyboard_layout(int ind) {
            return &keyboard_list[ind];
        }

        void add_keyboard(std::string full, std::string abbrev) {
            keyboard_list.push_back(Keyboard{full, abbrev});
        }
        void remove_keyboard(int ind) {
            keyboard_list.erase(keyboard_list.begin() + ind);
        }

        // Setting current keyboard
        int get_current() {
            return current;
        }

        void set_current(int new_cur) {
            current = new_cur;
        }

        void apply_current() {
            std::string command = "setxkbmap -layout " + keyboard_list[current].abbrev;
            system(command.c_str());
        }

    private:
        int current = 0;
        std::vector<Keyboard> keyboard_list;
};
