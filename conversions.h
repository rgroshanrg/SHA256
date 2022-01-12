#pragma once

#include<bitset>
#include<unordered_map>


class Conversion {
    public :
        static std::string strToBin(std::string);
        static std::string hexToBin(std::string);
        static std::string binToHex(std::string);
};

std::string Conversion::strToBin(std::string message) {

    int len = message.length();

    std::string binary_form = "";

    for(int i = 0; i < len; ++i) {
        binary_form += std::bitset<8>(message.c_str()[i]).to_string();
    }
    
    return binary_form;
}

std::string Conversion::hexToBin(std::string hexadecimal_string) {

    if(hexadecimal_string.length() > 2) {
        if(hexadecimal_string[0] == '0' && hexadecimal_string[1] == 'x') {
            hexadecimal_string.erase(0, 2);
        }
    }

	long int i = 0;

    std::string binary_string = "";

	while (hexadecimal_string[i]) {

		switch (hexadecimal_string[i]) {
		case '0':
			binary_string += "0000";
			break;
		case '1':
			binary_string += "0001";
			break;
		case '2':
			binary_string += "0010";
			break;
		case '3':
			binary_string += "0011";
			break;
		case '4':
			binary_string += "0100";
			break;
		case '5':
			binary_string += "0101";
			break;
		case '6':
			binary_string += "0110";
			break;
		case '7':
			binary_string += "0111";
			break;
		case '8':
			binary_string += "1000";
			break;
		case '9':
			binary_string += "1001";
			break;
		case 'A':
		case 'a':
			binary_string += "1010";
			break;
		case 'B':
		case 'b':
			binary_string += "1011";
			break;
		case 'C':
		case 'c':
			binary_string += "1100";
			break;
		case 'D':
		case 'd':
			binary_string += "1101";
			break;
		case 'E':
		case 'e':
			binary_string += "1110";
			break;
		case 'F':
		case 'f':
			binary_string += "1111";
			break;
		default:
			std::cout << "\nInvalid hexadecimal digit "
				<< hexadecimal_string[i];
		}
		i++;
	}
    return binary_string;
}

std::string Conversion::binToHex(std::string binary_string) {
    int len = binary_string.length();
    if(len % 4 != 0) {
        int resd = 4 - (len % 4);
        len += resd;
        while(resd--)   binary_string.insert(binary_string.begin(), '0');
    }
    // std::cout << binary_string << "\n";
    std::unordered_map<std::string, char> bin_hex_map;
    
    bin_hex_map["0000"] = '0';
    bin_hex_map["0001"] = '1';
    bin_hex_map["0010"] = '2';
    bin_hex_map["0011"] = '3';
    bin_hex_map["0100"] = '4';
    bin_hex_map["0101"] = '5';
    bin_hex_map["0110"] = '6';
    bin_hex_map["0111"] = '7';
    bin_hex_map["1000"] = '8';
    bin_hex_map["1001"] = '9';
    bin_hex_map["1010"] = 'A';
    bin_hex_map["1011"] = 'B';
    bin_hex_map["1100"] = 'C';
    bin_hex_map["1101"] = 'D';
    bin_hex_map["1110"] = 'E';
    bin_hex_map["1111"] = 'F';

    std::string hex = "";
    
    for(int i = 0; i < len; i += 4) {
        hex += bin_hex_map[binary_string.substr(i, 4)];
    }
    return hex;
}
