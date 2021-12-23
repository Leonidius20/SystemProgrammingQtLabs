#include<string>

namespace hotelSystem {

	class Hotel {
	public:
		Hotel(int code, std::string name, std::string country, std::string city, std::string address, int stars);
		

		int getCode() { return code; }
		void setCode(int code) { this->code = code; }


		int getStars() { return stars; }
		void setStars(int stars) { this->stars = stars; }
		
		std::string getName() { return name; }
		void setName(std::string name) { this->name = name; }


		std::string getCountry() { return country; }
		void setCountry(std::string country) { this->country = country; }

		std::string getCity() { return city; }
		void setCity(std::string city) { this->city = city; }

		std::string getAddress() { return address; }
		void setAddress(std::string address) { this->address = address; }

		std::string getContactName() { return contactName; }
		void setContactName(std::string contactName) { this->contactName = contactName; }

		std::string getContactPatronymic() { return contactPatronymic; }
		void setContactPatronymic(std::string contactPatronymic) { this->contactPatronymic = contactPatronymic; }

		std::string getContactSurname() { return contactSurname; }
		void setContactSurname(std::string contactSurname) { this->contactSurname = contactSurname; }

		std::string getContactPhone() { return contactPhone; }
		void setContactPhone(std::string contactPhone) { this->contactPhone = contactPhone; }

		int compareWith(Hotel *other);


	private:
		int code;
		std::string name;
		std::string country, city, address;
		int stars;
		std::string contactName, contactPatronymic, contactSurname, contactPhone;

	};

	void printHotel(Hotel &hotel);

}
