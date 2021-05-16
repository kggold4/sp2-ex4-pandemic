/**
 * 
 * Assignment #4
 * COURSE:   Systems Programming 2 Ariel University
 * AUTHORS:  Kfir Goldfarb
 * https://www.github.com/kggold4
 * YEAR: 2021
 * 
 * */

#pragma once

#include <set>
#include <map>
#include "Board.hpp"
#include "Color.hpp"
#include "City.hpp"

using namespace pandemic;

const static unsigned int MAX_CITIES = 48;

namespace pandemic {
    class Player {

        private:

            // player board
            Board board;

            // player current city
            City current_city;

            // player set of cards
            set<City> player_cards;

        public:

            // constructor
            Player(Board& board, const City city);

            // de-constructor
            ~Player();

            // drive to given near city (if not near throw exception)
            virtual Player& drive(const City city);

            // fly to another city
            virtual Player& fly_direct(const City city);
            virtual Player& fly_charter(const City city);
            virtual Player& fly_shuttle(const City city);
            virtual Player& build();
            virtual Player& discover_cure(const Color color);
            virtual Player& treat(const City city);
            virtual Player& take_card(const City city);
            virtual Player& remove_cards();
            string role() const;

            // return true if color has curve
            bool has_cure(const Color color) { return this->board.has_cure(color); }
            void set_cure(const Color color) { this->board.set_cure(color); }
            void del_cure(const Color color) { this->board.del_cure(color); }
            set<City> get_player_cards() const { return this->player_cards; };
            void erase_card(City card) { this->player_cards.erase(card); }
            City get_current_city() const { return this->current_city; }
            void set_current_city(const City city) { this->current_city = city; };
            int get_city_cubes(City city) const  { return this->board.get_city_cubes(city); }

            // return true if the player have the given city card
            bool has_card(City city) {
                if(cards_is_empty()) { throw invalid_argument("player do not have cards"); }
                return this->player_cards.find(city) != this->player_cards.end();
            }

            // remove card from player cards
            void remove_card(City city) {

                // if card not found
                if(!has_card(city)) { throw invalid_argument("player does not gave the given city card"); }
                this->player_cards.erase(city);
            }

            // check if city is valid
            bool valid_city(const City city) const {
                if(city < 0 || city >= MAX_CITIES) { return false; }
                return true;
            }

            bool cards_is_empty() const {
                return this->player_cards.empty();
            }

            void remove_all_city_cubes() {
                int number_of_city_cubes = this->board.get_city_cubes(this->current_city);
                while(number_of_city_cubes > 0) {
                    decrease_city_cubes();
                    number_of_city_cubes--;
                }
            }

            void decrease_city_cubes() {
                this->board.decrease_city_cubes(this->current_city);
            }

            // return true of if the given city has a research station
            bool has_research_station(const City city) { return this->board.has_research_station(city); }
            void set_research_station(const City city) { this->board.set_research_station(city); }
    };
}
