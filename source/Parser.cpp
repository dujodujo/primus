#include "Parser.h"

Parser* Parser::parser = NULL;

Parser::Parser() {}

Parser::~Parser() {}

Parser* Parser::instance() {
	return Parser::parser;
}

void Parser::init() {
	Parser::parser = new Parser();
}

void Parser::stripWhitespaces(std::string& s) {
	if(!s.empty()) {
		unsigned int begin = s.find_first_not_of(" ");
		unsigned int end = s.find_last_not_of(" ");
		s = s.substr(begin, end - begin + 1);
	}
}

void Parser::getStringValues(std::vector<std::string>& values, std::string buffer) {
	std::string value;
	unsigned int end = 0;

	while(!buffer.empty()) {
		end = buffer.find_first_of(";");
		if(end < buffer.size()) {
			value = buffer.substr(0, end);
			buffer = buffer.substr(end + 1);
		} else {
			value = buffer;
			buffer.clear();
		}

		stripWhitespaces(value);

		if(!value.empty()) {
			values.push_back(value);
		}
	}
}

void Parser::getIntPairValues(std::vector<std::pair<int, int>>& values, std::string buffer) {
	std::vector<std::string> vals;
	getStringValues(vals, buffer);
	
	for(unsigned int i = 0; i < vals.size(); i++) {
		std::pair<unsigned int, unsigned int> pairs;
		pairs.first = toInt(vals[i]);
		++i;
		pairs.second = toInt(vals[i]);
		values.push_back(pairs);
	}
}

template<typename T>
void Parser::getIntValues(std::vector<T>& values, std::string buffer) {
	std::string value;
	unsigned int end = 0;

	stripWhitespaces(buffer);

	while(!buffer.empty()) {
		end = buffer.find_first_of(";");
		if(end < buffer.size()) {
			value = buffer.substr(0, end);
			buffer = buffer.substr(end + 1);
		} else {
			value = buffer;
			buffer.clear();
		}
		if(!value.empty()) {
			values.push_back(value);
		}
	}
}

void Parser::getColorValues(std::vector<Ogre::ColourValue>& values, std::string buffer) {
	std::vector<std::string> vals;
	Parser::getStringValues(vals, buffer);
	for(unsigned int i = 0; i < vals.size() - 2; ++i) {
        Ogre::Real r = toReal(vals[i]) / 255;
        ++i;
        Ogre::Real g = toReal(vals[i]) / 255;
        ++i;
        Ogre::Real b = toReal(vals[i]) / 255;
        values.push_back(Ogre::ColourValue(r, g, b));
    }
}

template<typename T>
void Parser::getEnumValues(std::vector<T>& values, std::string buffer) {
	std::vector<std::string> vals;
	Parser::getStringValues(vals, buffer);
	int size;
	for(unsigned int i = 0, size = string_array.size(); i < size; ++i) {
        values.push_back(static_cast<T>(getEnum(vals[i])));
    }
}

int Parser::toEnum(std::string s) {
	int result = -1;
	if (s.compare("left")) {
        result = 0;
	} else if(s.compare("center")) {
        result = 1;
	} else if (s.compare("right")) {
        result = 2;
	} else if(s.compare("top")) {
        result = 3;
	} else if (s.compare("bottom")) {
        result = 4;
	} else if (s.compare("hud_status")) {
        result = 5;
	} else if (s.compare("status")) {
        result = 6;
	} else if (s.compare("status_display")) {
        result = 7;
	}

	return result;
}

bool Parser::getPairValues(const std::string& fileName, std::map<std::string, std::string>& pairs) {
	std::string buffer;
    std::string key;
    std::string value;
    std::string end_value; //multiline result
    std::ifstream file;

	file.open(fileName.c_str());

    if(file.is_open()) {
		unsigned int begin;
		unsigned int end;
		while(!file.eof()) {
			std::getline(file, buffer);

            //check if a key, insde []
            begin = buffer.find_first_of("[");
            end = buffer.find_first_of("]");

			if (begin < buffer.size() && end < buffer.size() && end - begin > 1) {
                if(!key.empty() && !end_value.empty()) {
                    pairs[key] = end_value;
                }
                end_value.clear();

				key = buffer.substr(begin + 1, end - begin - 1);
				Parser::stripWhitespaces(key);
            } else {
				end = buffer.find_last_of("#");
                value = (end < buffer.size()) ? buffer.substr(0, end) : buffer;

                Parser::stripWhitespaces(value);
				if (!value.empty()) {
                    if (end_value.empty()) {
                        end_value = value;
                    } else {
                        //if not empty separate values with ';'
                        end_value += ";" + value;
                    }
                }
			}
		}
		//last flush after the file ends
        if (!key.empty() && !end_value.empty()) {
            pairs[key] = end_value;
        }
        //finished reading the file
        file.close();

    } else {
		std::stringstream stream;
		std::string message;
		stream << "error loading pairs";
		stream >> message;
		Game::log->logMessage(message);
	}
    return !pairs.empty();
}

template<typename M, typename N>
void Parser::getEnumPairValues(std::vector<std::pair<M, N>>& values, std::string buffer) {
	std::vector<std::string> vals;
	getStringValues(vals, buffer);

	for(unsigned int i = 0; i < vals.size(); i++) {
		std::pair<M, N> pairs;
		pairs.first = static_cast<M>(toEnum(vals[i]));
		++i;
		pairs.second = static_cast<N>(toEnum(vals[i]));
		values.push_back(pairs);
	}
}

void Parser::getRealValues(std::vector<Ogre::Real>& values, std::string buffer) {
	unsigned int end = 0;
    std::string value;
	Parser::stripWhitespaces(buffer);
    unsigned int open = buffer.find_first_of("(");
    unsigned int close = buffer.find_first_of(")");

    //check to see if we have '(' and ')' and anything inside them
    if (open < close - 1 && close < buffer.size()) {
        buffer = buffer.substr(open + 1, close - open - 1);
        while (!buffer.empty()) {
            //values are seperated with ,
            end = buffer.find_first_of(",");
			if (end < buffer.size()) {
                //take one value
                value = buffer.substr(0, end);
                //cut it from the buffer
                buffer = buffer.substr(end + 1);

            } else {
                //take the whole buffer as the last value
                value = buffer;
                buffer.clear();
            }
			Parser::stripWhitespaces(value);
            if (!value.empty()) {
                values.push_back(toReal(value));
            }
        }
    }
}

bool Parser::getHudDesign(const std::string& fileName, HudComponents& hudComponents) {
    std::map<std::string, std::string> pairs;

	Parser::getPairValues(fileName, pairs);
	hudComponents.name = fileName;
	hudComponents.fontName = pairs["hud_design.font_name"];
	Parser::getStringValues(hudComponents.areaTextures, pairs["hud_design.area_textures"]);
	Parser::getIntPairValues(hudComponents.positions, pairs["hud_design.positions"]);
	Parser::getIntPairValues(hudComponents.sizes, pairs["hud_design.sizes"]);

	int i = 0;
	while(pairs.find(std::string("hud_design.parts." + toString(i))) != pairs.end()) {
		HudParts hudPart;
		std::vector<std::string> values;
		Parser::getStringValues(values, pairs[std::string("hud_design.parts.") + toString(i)]);

		hudPart.area = HudArea(toEnum(values[0]));
		hudPart.name = values[1];
		hudPart.position.first = toInt(values[2]);
		hudPart.position.second = toInt(values[3]);
		hudPart.size.first = toInt(values[4]);
		hudPart.size.second = toInt(values[5]);
		hudComponents.parts.push_back(hudPart);
		++i;
	}
    return true;
}

bool Parser::getCollisionSpheres(const std::string& fileName, Sphere& boundingSphere) {
	return false;
}