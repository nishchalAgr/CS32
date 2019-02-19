
class Landmark {

public:
	Landmark(string name, string icon, string color);

	virtual ~Landmark() = 0;

	string name() const{
		return m_name;
	};

	virtual string icon() const{
		return m_icon;
	};

	string color() const{
		return m_color;
	};

private:

	string m_name;
	string m_icon;
	string m_color;
};

Landmark::~Landmark() {}

Landmark::Landmark(string name, string icon, string color) {
	m_name = name;
	m_icon = icon;
	m_color = color;
}

class Hotel : public Landmark {

public:
	Hotel(string name);
	
	~Hotel() {
		cout << "Destroying the " << this->name() << endl;
	};

};

//hotel constructor
Hotel::Hotel(string name)
	:Landmark(name, "bed", "yellow") {}


class Hospital : public Landmark {

public:
	Hospital(string name);

	~Hospital() {
		cout << "Destroying the hospital " << this->name() << endl;
	};

};

//Hospital Constructor
Hospital::Hospital(string name)
	:Landmark(name, "H", "blue") {}


class Restaurant : public Landmark {

public:
	Restaurant(string name, int cap);

	~Restaurant() {
	
		cout << "Destroying the restaurant " << this->name() << endl;
	
	}

	string icon() const {
	
		return m_icon;
	
	}

private:
	string m_icon;
};

Restaurant::Restaurant(string name, int cap)
	:Landmark(name, "", "blue") {

	if (cap >= 40) m_icon = "large fork/knife icon";
	else if (cap < 40) m_icon = "small fork/knife icon";

}
