#ifndef CARD_HPP
#define CARD_HPP

#include <string>
namespace ariel{

    class Card
    {

    public:
    std::string name;

    };

    class DevelopmentCard:public Card{
        public:
            DevelopmentCard(const std::string& name);

    };

    class ResourceCard : public Card {
        public:
            ResourceCard(const std::string& name);

    };

}
#endif