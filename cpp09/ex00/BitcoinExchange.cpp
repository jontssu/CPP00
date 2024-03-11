#include "BitcoinExchange.hpp"

// BitcoinExchange::BitcoinExchange() {}

int convertDateToNumeric(const std::string& dateString) {
    std::smatch match;
    std::regex dateRegex("([0-9]{4})-([0-9]{2})-([0-9]{2})");

    if (std::regex_search(dateString, match, dateRegex)) {
        try {
            int year = std::stoi(match[1]);
            int month = std::stoi(match[2]);
            int day = std::stoi(match[3]);

            return year * 10000 + month * 100 + day;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error converting numeric value from date string: " << dateString << std::endl;
            throw;
        }
    } else {
        throw std::invalid_argument("Invalid date string format");
    }
}

BitcoinExchange::BitcoinExchange(std::string const &data, std::string const &input) {
	std::ifstream inputFile;
	std::vector<std::string> inputVec;
	std::string line;;
	std::regex regex_basic("[0-9]{4}-[0-9]{2}-[0-9]{2} \\| [0-9]+.?[0-9]*");
	std::regex regex_negative("[0-9]{4}-[0-9]{2}-[0-9]{2} \\| -[0-9]+.?[0-9]*");
	std::regex regex_day("[1-2][0|9][0-9][0-9]-[0-3][0-9]-[0-1][0-9].*");

	inputFile.open(input);
	if (!inputFile.is_open()) {
		std::cout << "Error: could not open file.\n";
		return;
	}

	getline(inputFile, line);
	if (line != "date | value")
		return;

	while (std::getline(inputFile, line)) {
		if (regex_match(line, regex_basic)) {
			size_t pos = line.find("|");	
			std::string tmp = line.substr(pos + 1);
			if (std::stof(tmp) > 1000)
				inputVec.emplace_back("Error: too large a number.");
			else
				if (regex_match(line, regex_day)) 
					inputVec.emplace_back(line);
				else
					inputVec.emplace_back("Error: date is not valid.");
		}
		else if (regex_match(line, regex_negative))
			inputVec.emplace_back("Error: not a positive number.");
		else
			inputVec.emplace_back("Error: bad input => " + line);
	}
	inputFile.close();

	std::ifstream dataFile;
	std::vector<std::string> datesToSearch;
	
	dataFile.open(data);
	if (!dataFile.is_open()) {
		std::cout << "Error: could not open file.\n";
		return;
	}

	if (std::getline(dataFile, line)) {
		while (std::getline(dataFile, line)) {
			if (!line.empty())
				datesToSearch.emplace_back(line);
		}
	}
	dataFile.close();

	for (const auto &dateToSearch : inputVec) {
		if (dateToSearch.front() == 'E') {
			std::cout << dateToSearch << '\n';
			continue;
		}
		try {
			int numericDate = convertDateToNumeric(dateToSearch);

			auto it = std::lower_bound(datesToSearch.begin(), datesToSearch.end(), numericDate, 
				[](const std::string& date, int numericValue) {
					return convertDateToNumeric(date) < numericValue;
				});

			float value = std::stof(dateToSearch.substr(dateToSearch.find("|") + 1));
			float value2;
			std::string date = dateToSearch.substr(0, dateToSearch.find("|") - 1);
			std::string str;

			(void)value;

			if (it == datesToSearch.end()) {
				auto lastDate = std::prev(datesToSearch.end());
				str = *lastDate;
				// std::cout << "closest date: " << *lastDate << '\n';
				value2 = std::stof(str.substr(str.find(",") + 1)); 
				std::cout << date << " => " << value << " = " << value * value2 << std::endl;
			} else {
				auto prevDate = std::prev(it);
				int numericPrev = convertDateToNumeric(*prevDate);
				int numericCurr = convertDateToNumeric(*it);

				if (std::abs(numericDate - numericPrev) < std::abs(numericDate - numericCurr)) {
					str = *prevDate;
					// std::cout << "closest date: " << *prevDate << '\n';
					value2 = std::stof(str.substr(str.find(",") + 1)); 
					std::cout << date << " => " << value << " = " << value * value2 << std::endl;
				} else {
					str = *it;
					value2 = std::stof(str.substr(str.find(",") + 1)); 
					// std::cout << "closest date: " << *it << '\n';
					std::cout << date << " => " << value << " = " << value * value2 << std::endl;
				}
			}
		} catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
}

// BitcoinExchange::BitcoinExchange(BitcoinExchange const &other) {

// }

// BitcoinExchange& BitcoinExchange::operator=(BitcoinExchange const &other) {
// 	if (this != &other) {

// 	}
// 	return (*this);
// }

BitcoinExchange::~BitcoinExchange() {}