#include <fstream>

class Printable {
public:
	virtual ~Printable() = default;

	virtual std::string print() = 0;
};


class Data {
public:
	Data(std::string&& data) : _data_(std::move(data)) {}
protected:
	std::string _data_{};
};

class TextWork : public Printable, public Data {
public:
	TextWork(std::string&& data) : Data(std::move(data)) {}

	std::string print() override {
		return _data_;
	}
};

class HTMLWork : public Printable, public Data {
public:
	HTMLWork(std::string&& data) : Data(std::move(data)) {}

	std::string print() override {
		return "<html>" + _data_ + "<html/>";
	}
};

class JSONWork : public Printable, public Data {
public:
	JSONWork(std::string&& data) : Data(std::move(data)) {}

	std::string print() override {
		return "{ \"data\": \"" + _data_ + "\"}";
	}
};

void saveTo(std::ofstream& file, Printable& pr) {
	file << pr.print();
}

int main() {

	std::ofstream text_file("text.txt");
	std::ofstream html_file("html.txt");
	std::ofstream json_file("json.txt");

	TextWork t_data("This is a TEXT test data.");
	HTMLWork h_data("This is a HTML test data.");
	JSONWork j_data("This is a JSON test data.");

	saveTo(text_file, t_data);
	saveTo(html_file, h_data);
	saveTo(json_file, j_data);

	return 0;
}