#include "hotel.h"
#include <iostream>

using namespace hotelSystem;
using namespace std;

namespace hotelSystem {

	void printHotel(Hotel &hotel) {
		cout << "Hotel " << hotel.getName() << " " << hotel.getStars() << " stars" << endl;
		cout << "Location: " << hotel.getAddress() << ", " << hotel.getCity() << ", " << hotel.getCountry() << endl;
        if (!hotel.getContactName().empty()) {
            cout << "Contact: " << hotel.getContactName() << " " << hotel.getContactPatronymic() << " " << hotel.getContactSurname()
                 << ", phone: " << hotel.getContactPhone() << endl;
        }
		cout << endl;
	}

}

