//============================================================================
// Name        : Base64.cpp
// Author      : rohit
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>
using namespace std;

char encode_dict[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

void encodeBase64(string& a_input, string& ar_output)
{
	ar_output.clear();
	uint32_t l_size = a_input.length();

	uint8_t l_octet_group[3];
	uint8_t l_needle;
	uint16_t l_index = 0;
	while(l_size >= 3)
	{
		l_octet_group[0]=static_cast<uint8_t>(a_input.at(l_index++));
		l_octet_group[1]=static_cast<uint8_t>(a_input.at(l_index++));
		l_octet_group[2]=static_cast<uint8_t>(a_input.at(l_index++));

		l_needle = l_octet_group[0] & 0xfc;
		l_needle = l_needle >> 2;
		ar_output.push_back(encode_dict[l_needle]);

		l_needle = ((l_octet_group[0] & 0x03) << 4) | ((l_octet_group[1] & 0xf0) >> 4);

		ar_output.push_back(encode_dict[l_needle]);

		l_needle = ((l_octet_group[1] & 0x0f) << 2) | ((l_octet_group[2] & 0xc0) >> 6);

		ar_output.push_back(encode_dict[l_needle]);

		l_needle = (l_octet_group[2] & 0x3f);

		ar_output.push_back(encode_dict[l_needle]);

		if(l_size >= 3)
		{
			l_size -= 3;
		}
		else
		{
			break;
		}
	}

	if(l_size == 0)
	{
		return;
	}
	if(l_size == 1)
	{
		l_octet_group[0] = a_input.at(l_index);
		l_needle = (l_octet_group[0] & 0xfc) >> 2;

		ar_output.push_back(encode_dict[l_needle]);

		l_needle = (l_octet_group[0] & 0x03) << 4;

		ar_output.push_back(encode_dict[l_needle]);
		ar_output.append("==");

	}
	if(l_size == 2)
	{
		l_octet_group[0]=static_cast<uint8_t>(a_input.at(l_index++));
		l_octet_group[1]=static_cast<uint8_t>(a_input.at(l_index));

		l_needle = l_octet_group[0] & 0xfc;
		l_needle = l_needle >> 2;
		ar_output.push_back(encode_dict[l_needle]);

		l_needle = ((l_octet_group[0] & 0x03) << 4) | ((l_octet_group[1] & 0xf0) >> 4);

		ar_output.push_back(encode_dict[l_needle]);

		l_needle = (l_octet_group[1] & 0x0f) << 2;
		ar_output.push_back(encode_dict[l_needle]);

		ar_output.push_back('=');

	}
}


uint8_t getDecodeDictVal(uint8_t a_input)
{
	static const uint8_t decode_dict_upper_case[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
	static const uint8_t decode_dict_lower_case[]={26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51};
	static const uint8_t decode_dict_integer[]={52,53,54,55,56,57,58,59,60,61};

	uint8_t l_ret_val = 0;
	if((a_input >= static_cast<uint8_t>('A')) && (a_input <= static_cast<uint8_t>('Z')))
	{
		l_ret_val = decode_dict_upper_case[a_input - 'A'];
	}
	else if((a_input >= static_cast<uint8_t>('a')) && (a_input <= static_cast<uint8_t>('z')))
	{
		l_ret_val = decode_dict_lower_case[a_input - 'a'];
	}
	else if((a_input >= static_cast<uint8_t>('0')) && (a_input <= static_cast<uint8_t>('9')))
	{
		l_ret_val = decode_dict_integer[a_input - '0'];
	}
	else if(a_input == static_cast<uint8_t>('+'))
	{
		l_ret_val = 62;
	}
	else if(a_input == static_cast<uint8_t>('/'))
	{
		l_ret_val = 63;
	}
	return l_ret_val;
}
void decodeBase64(string& a_input, string& ar_output)
{
	uint32_t l_size = a_input.length();
	ar_output.clear();
	char l_octet_group[4];
	uint8_t l_needle;
	uint8_t l_next_val;
	uint16_t l_index = 0;

	while(l_size >= 4)
	{
		l_octet_group[0]=static_cast<uint8_t>(a_input.at(l_index++));
		l_octet_group[1]=static_cast<uint8_t>(a_input.at(l_index++));
		l_octet_group[2]=static_cast<uint8_t>(a_input.at(l_index++));
		l_octet_group[3]=static_cast<uint8_t>(a_input.at(l_index++));

		l_needle = (getDecodeDictVal(l_octet_group[0]) & 0x3f) << 2;
		l_next_val = getDecodeDictVal(l_octet_group[1]);

		l_needle = l_needle | ((l_next_val & 0x3f) >> 4);
		ar_output.push_back(static_cast<char>(l_needle));


		if(l_octet_group[2] == static_cast<uint8_t>('='))
		{
			return;
		}
		l_needle = l_next_val; //[1]
		l_next_val = getDecodeDictVal(l_octet_group[2]);

		l_needle = ((l_needle & 0x0f) << 4) | ((l_next_val & 0x3f) >> 2);
		ar_output.push_back(static_cast<char>(l_needle));

		if(l_octet_group[3] == static_cast<uint8_t>('='))
		{
			return;
		}

		l_needle = l_next_val; //[2]
		l_next_val = getDecodeDictVal(l_octet_group[3]);

		l_needle = ((l_needle & 0x03) << 6)  | (l_next_val & 0x3f);
		ar_output.push_back(static_cast<char>(l_needle));

		if(l_size >= 4)
		{
			l_size -= 4;
		}
		else
		{
			break;
		}
	}

	if(l_size == 3)
	{
		l_octet_group[0]=static_cast<uint8_t>(a_input.at(l_index++));
		l_octet_group[1]=static_cast<uint8_t>(a_input.at(l_index++));
		l_octet_group[2]=static_cast<uint8_t>(a_input.at(l_index++));

		if(l_octet_group[1] == static_cast<uint8_t>('='))
		{
			cout << "This should not happen";
			return;
		}

		l_needle = getDecodeDictVal(l_octet_group[0]);
		l_next_val = getDecodeDictVal(l_octet_group[1]);

		l_needle = ((l_needle & 0x3f) << 2) | ((l_next_val & 0x3f) >> 4);
		ar_output.push_back(static_cast<char>(l_needle));
		if(l_octet_group[2] == static_cast<uint8_t>('='))
		{
			return;
		}

		l_needle = l_next_val; //[1]
		l_next_val = getDecodeDictVal(l_octet_group[2]);

		l_needle = ((l_needle & 0x0f) << 4) | ((l_next_val & 0x3f) >> 2);

		ar_output.push_back(static_cast<char>(l_needle));

		return;

	}
	else if (l_size == 2)
	{
		l_octet_group[0]=static_cast<uint8_t>(a_input.at(l_index++));
		l_octet_group[1]=static_cast<uint8_t>(a_input.at(l_index++));

		if(l_octet_group[1] == static_cast<uint8_t>('='))
		{
			cout << "This should not happen";
			return;
		}
		l_needle = getDecodeDictVal(l_octet_group[0]);
		l_next_val = getDecodeDictVal(l_octet_group[1]);

		l_needle = ((l_needle & 0x3f) << 2) | ((l_next_val & 0x3f) >> 4);
		ar_output.push_back(static_cast<char>(l_needle));
	}

}

void convertToBinary(string& input, string& output)
{
	uint8_t l_byte;
	uint16_t l_index = 0;
	uint8_t l_bit_count;
	uint8_t l_bit_mask = 0x80;

	while(l_index < input.size())
	{
		l_bit_count = 0;
		l_byte = input.at(l_index);
		while(l_bit_count < 8)
		{
			if(l_byte & l_bit_mask)
			{
				output.push_back('1');
			}
			else
			{
				output.push_back('0');
			}

			l_bit_count++;
			l_byte <<= 1;
		}
		l_index++;
	}
}

void convertBase64ToBinary(string& input, string& output)
{
	uint8_t l_byte;
	uint16_t l_index = 0;
	uint8_t l_bit_count;
	uint8_t l_bit_mask = 0x20;

	while(l_index < input.size())
	{
		l_bit_count = 0;
		if(input.at(l_index) == '=')
			break;
		l_byte = getDecodeDictVal(static_cast<uint8_t>(input.at(l_index)));
		while(l_bit_count < 6)
		{
			if(l_byte & l_bit_mask)
			{
				output.push_back('1');
			}
			else
			{
				output.push_back('0');
			}

			l_bit_count++;
			l_byte <<= 1;
		}
		l_index++;
	}
}

int main() {
	string input;
	string output;

	getline(cin, input);
	encodeBase64(input, output);

	cout << output << endl;

	decodeBase64(output, input);

	cout << input << endl;

	return 0;
}
