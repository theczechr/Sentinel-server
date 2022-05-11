#include <functional>
#include <math.h>
#include "hashing.h"
size_t hash(std::string to_hash)
{
    std::size_t str_hash = std::hash<std::string>{}(to_hash);
    return str_hash;
}

size_t client_id(std::string email) {
    size_t user_id = 0;
    int number = 5;
    //need to do some bitwise calculations
    // nebudu delat zadne calculations zde jiz na to jebu, bro ... :D =]
    // neni na to sila:D =[
    for (size_t i = 0; i < email.length(); i++) {
        user_id = user_id + (pow(number, i) * sqrt(size_t(email[i])) );
    }
    return user_id;
}