#pragma once

#include "Player.hpp"
#include "Board.hpp"
#include "City.hpp"

using namespace pandemic;

namespace pandemic {
    class OperationsExpert : public Player {
        public:
            OperationsExpert(Board& board, const int city);
    };
}