#ifndef MOVING_H
#define MOVING_H

#include <string>
#include <utility>

class DisplayedMap;
class Player;

std::pair<DisplayedMap*, Player*> move(const std::string& direction, DisplayedMap* displayed_map, Player* player);

#endif // MOVING_H 