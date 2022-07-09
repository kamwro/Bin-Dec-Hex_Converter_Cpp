#include <iostream>
#include <string>
#include <cmath>


using std::string; using std::cout; using std::cin;

class Number
{
public:
    virtual void enter_number() {}
    virtual bool is_the_number_correct() {}
    virtual string to_binary () {}
    virtual string to_decimal () {}
    virtual string to_hexadecimal () {}
};


class Binary: public Number
{
    string binary_number;

public:
    virtual void enter_number(bool we_have_number = false, string we_have_binary = "no") {
        if (!(we_have_number)) {
            cout << "Please enter your binary number:" << '\n';
            cin >> binary_number;
        } else binary_number = we_have_binary;
    };
    virtual bool is_the_number_correct(int num_of_digits) {
        for (int i = 0; i < num_of_digits; i++)
        {
            if (binary_number[i] != '1' && binary_number[i] != '0') return false;
        }
        return true;
    };
    virtual string to_decimal () {
        int num_of_digits = binary_number.size();
        if (!is_the_number_correct(num_of_digits)) return "the binary number is not correct";
        // I thought it was less complex approach to include function for checking if number is
        // correct inside every conversion function than checking it in Calculator class
        // because in that case we would need to check number of digits in more places
        // not sure if that would be less code
        int new_number = 0;
        for (int i = num_of_digits-1, j = 0; i >= 0; i--, j++)
        {
            if (binary_number[i] == '1') new_number += pow(2, j);
        }
        return std::to_string(new_number);
    }

    // we don't need a function for direct converting binary to hexadecimal, because
    // we can just first convert binary to decimal, and then decimal to hex
    // I think direct approach in that case would be just unnecessary lines of code
};

class Decimal: public Number {
    string decimal_number;
public:
    // because we are using Decimal class enter_number function for binary to hex conversion
    // we need additional parameter to specify which case we're at the moment
    // moreover if we have decimal after binary conversion we don't need the user to write down number
    // because I chose decimal_number to be Decimal private variable, I did this like that
    virtual void enter_number(bool bin_to_hex_or_hex_to_bin = false, string we_have_decimal = "no") {
        if (!(bin_to_hex_or_hex_to_bin)) {
            cout << "Please enter your decimal number:" << '\n';
            cin >> decimal_number;
        } else decimal_number = we_have_decimal;
    };

    virtual bool is_the_number_correct(bool* is_the_number_negative) { // checking and if correct preparing number
                                        // by erasing - and + symbols
                                        // and moreover checking if number is negative

        int num_of_digits = decimal_number.length();
        for (int i = 0; i < num_of_digits; i++)
        {
            if (decimal_number[i] == '-') {
                * is_the_number_negative = true;
                decimal_number.erase(i, 1);
                num_of_digits--;
            }
            else if (decimal_number[i] == '+') {
                decimal_number.erase(i, 1);
                num_of_digits--;
            }
            else if (isdigit(decimal_number[i]) == false) return false;
        }
        return true;
    };


    virtual string to_binary(bool is_decimal_negative = false, bool first_usage = true) {

        if (first_usage) if (!(is_the_number_correct(&is_decimal_negative))) return "the decimal number is not correct";
        //this function includes both positive and negative decimal number case
        int true_decimal = std::stoi(decimal_number);
        string storage_for_later = decimal_number;
        if (true_decimal == 0) return "0";
        if (true_decimal == 1 && !(is_decimal_negative)) return "1";
        string new_number;
        while (true_decimal != 0) {
                if (true_decimal % 2 == 1) new_number.append("1");
                else new_number.append("0");
                true_decimal = true_decimal / 2;
            }
            std::reverse(new_number.begin(), new_number.end());
      if (is_decimal_negative)
        {
          return "\nPositive number("+ storage_for_later + "): 0" + new_number +
                    "\n1's complement: " + get_complement("0"+new_number, "1s_bin") +
                    "\n2's complement: " + get_complement("0"+new_number, "2s_bin");
          // get_complement() is Decimal class method that returns each binary complement

        }
        return new_number;
    }

    string get_complement (string binary_or_hex_positive, string which_one)
    {
        int num_of_digits = binary_or_hex_positive.size();
        string complement_result;
        if ("1s_bin" == which_one)
        {
            for (int i = 0; i < num_of_digits; i++) // to get 1's complement we simply
                                                    // need to switch each one to zero and likewise
                                                    // including sign char 0 in binary positive number
            {
                if (binary_or_hex_positive[i] == '0') complement_result.append("1");
                else complement_result.append("0");
            }
        }
        else if ("2s_bin" == which_one)
        { // to get 2's complement we need to binary add 1 to the 1's complement
            // to binary add we would like to switch to decimal first, add 1 decimal
            // and switch back to binary
            complement_result = get_complement(binary_or_hex_positive, "1s_bin");
            Binary bin;
            bin.enter_number(true, complement_result);
            decimal_number = bin.to_decimal();
            decimal_number = std::to_string(std::stoi(decimal_number)+1);
            complement_result = to_binary(false, false);
        }
        else if ("1s_hex" == which_one)
        {
            for (int i = 0; i < num_of_digits; i ++)
            {
                if (binary_or_hex_positive[i] == '0') binary_or_hex_positive[i] = 'F';
                else if (binary_or_hex_positive[i] == '1') binary_or_hex_positive[i] = 'E';
                else if (binary_or_hex_positive[i] == '2') binary_or_hex_positive[i] = 'D';
                else if (binary_or_hex_positive[i] == '3') binary_or_hex_positive[i] = 'C';
                else if (binary_or_hex_positive[i] == '4') binary_or_hex_positive[i] = 'B';
                else if (binary_or_hex_positive[i] == '5') binary_or_hex_positive[i] = 'A';
                else if (binary_or_hex_positive[i] == '6') binary_or_hex_positive[i] = '9';
                else if (binary_or_hex_positive[i] == '7') binary_or_hex_positive[i] = '8';
                else if (binary_or_hex_positive[i] == '8') binary_or_hex_positive[i] = '7';
                else if (binary_or_hex_positive[i] == '9') binary_or_hex_positive[i] = '6';
                else if (binary_or_hex_positive[i] == 'A') binary_or_hex_positive[i] = '5';
                else if (binary_or_hex_positive[i] == 'B') binary_or_hex_positive[i] = '4';
                else if (binary_or_hex_positive[i] == 'C') binary_or_hex_positive[i] = '3';
                else if (binary_or_hex_positive[i] == 'D') binary_or_hex_positive[i] = '2';
                else if (binary_or_hex_positive[i] == 'E') binary_or_hex_positive[i] = '1';
                else if (binary_or_hex_positive[i] == '-');
                else binary_or_hex_positive[i] = '0';
            }
            complement_result = binary_or_hex_positive;
        }
        else return "";

        return complement_result;
    }

    void get_16_lowest_divider(int decimal_number, string new_number) {
        // this recursion function we need for dec to hex conversion
        // it goes to the lowest possible divider of dec/16
        // and ofc writes it in hexadecimal language
        // we would like to call this function multiply times with consequently lower value each time
        // there's loop for that in to_hexadecimal func

            if (decimal_number > 9 && decimal_number < 16) {
                switch (decimal_number) {
                    case 10:
                        new_number.append("A");
                        break;
                    case 11:
                        new_number.append("B");
                        break;
                    case 12:
                        new_number.append("C");
                        break;
                    case 13:
                        new_number.append("D");
                        break;
                    case 14:
                        new_number.append("E");
                        break;
                    case 15:
                        new_number.append("F");
                        break;
                }
                get_16_lowest_divider(decimal_number/16, new_number);
            }
            else if (decimal_number > 0) {
                new_number.append(std::to_string(decimal_number));
                get_16_lowest_divider(decimal_number/16, new_number);
            }
    }

    virtual string to_hexadecimal(){
        bool is_the_number_negative;
        if (!is_the_number_correct(&is_the_number_negative)) return "the decimal number is not correct";
        int true_decimal = std::stoi(decimal_number);
        if (true_decimal == 0) return "0";
        string new_number;

            while (true_decimal > 0) { // it uses recursion function (check few lines above)
                                        // to find all the dividers of dec/16 and writes
                                        // them in hex language
                get_16_lowest_divider(true_decimal, new_number);
                int division_rest = true_decimal % 16;

                if (division_rest > 9) { // we also need to write down the rest from the division
                    switch (division_rest) {
                        case 10:
                            new_number.append("A");
                            break;
                        case 11:
                            new_number.append("B");
                            break;
                        case 12:
                            new_number.append("C");
                            break;
                        case 13:
                            new_number.append("D");
                            break;
                        case 14:
                            new_number.append("E");
                            break;
                        case 15:
                            new_number.append("F");
                            break;
                    }
                } else new_number.append(std::to_string(division_rest));
                true_decimal = true_decimal/16;
            }
            if (is_the_number_negative) new_number.append("-");
        std::reverse(new_number.begin(), new_number.end()); // because we wrote them right-to-left
        return new_number;
    }


};

class Hexadecimal: public Number {
    string hex_number;

public:
    virtual void enter_number(bool we_have_string = false, string what_we_have = "nothing") {
       if (!we_have_string){
           cout << "Please enter your hexadecimal number:" << '\n';
           cin >> hex_number;
       }
       else hex_number = what_we_have;
    };

    virtual bool is_the_number_correct(int num_of_digits) {

        for (int i = 0; i < num_of_digits; i++)
        {
            if (isxdigit(hex_number[i]) == false) return false;
        }

        return true;
    };
    // don't have to_binary function since its hex->dec->bin

    virtual string to_decimal() {
        int num_of_digits = hex_number.size();
        if (!is_the_number_correct(num_of_digits)) return "the hexadecimal number is not correct";
        int new_number = 0;
        std::reverse(hex_number.begin(), hex_number.end());
        for (int i = 0; i < num_of_digits; i++)
        {
            if (hex_number[i] == 'a' || hex_number[i] == 'A') new_number += 10*pow(16, i);
            else if (hex_number[i] == 'b' || hex_number[i] == 'B') new_number += 11*pow(16, i);
            else if (hex_number[i] == 'c' || hex_number[i] == 'C') new_number += 12*pow(16, i);
            else if (hex_number[i] == 'd' || hex_number[i] == 'D') new_number += 13*pow(16, i);
            else if (hex_number[i] == 'e' || hex_number[i] == 'E') new_number += 14*pow(16, i);
            else if (hex_number[i] == 'f' || hex_number[i] == 'F') new_number += 15*pow(16, i);
            else  {
                int dec_digit = hex_number[i] - '0'; // casting char value to an int like '1' -> 1
                new_number += dec_digit*pow(16, i);
            }
        }
        return std::to_string(new_number);
    }
};

class Calculator
{
    string conversion_type = "none";
    Binary bin;
    Decimal dec;
    Hexadecimal hex;
    bool in_game = true;
    bool first_game = true;
public:
    void which_conversion() { // recursive
        if (first_game) cout << "Hello! This is bin to dec and dec to bin number converter." << '\n';
        first_game = false;
        cout << "Please choose desired conversion type: (enter number)" << '\n';
        cout << "1. Binary to decimal\n"
                "2. Decimal to binary\n"
                "3. Binary to hexadecimal\n"
                "4. Decimal to hexadecimal\n"
                "5. Hexadecimal to binary\n"
                "6. Hexadecimal to decimal\n"
                "0. Leave" << std::endl;
        int choice = -1;
        cin >> choice;
        switch (choice)
        {
            case 0:
                in_game = false; break;
            case 1:
                conversion_type = "bin_dec"; break;
            case 2:
                conversion_type = "dec_bin"; break;
            case 3:
                conversion_type = "bin_hex"; break;
            case 4:
                conversion_type = "dec_hex"; break;
            case 5:
                conversion_type = "hex_bin"; break;
            case 6:
                conversion_type = "hex_dec"; break;
            default: which_conversion();
        }
    }

    Calculator() {
        while (in_game) {
            which_conversion();
            if (!(conversion_type == "none")) menu();
            else break;
            repeat_the_program();
        }
        goodbye();
        }
    void menu()
    {
        if (conversion_type == "bin_dec") {
            string to_dec;
            bin.enter_number();
            to_dec = bin.to_decimal();
            cout << "Your decimal number: " << to_dec << '\n';
        }
        else if (conversion_type == "dec_bin") {
            string to_bin;
            dec.enter_number();
            to_bin = dec.to_binary();
            cout << "Your binary number: " << to_bin << '\n';

        }
        else if (conversion_type == "bin_hex") {
            string to_dec, to_hex;
            bin.enter_number();
            to_dec = bin.to_decimal();
            dec.enter_number(true, to_dec);
            to_hex = dec.to_hexadecimal();
            cout << "Your hexadecimal number: " << to_hex << '\n';

        }
        else if (conversion_type == "dec_hex") {
            string to_hex;
            dec.enter_number();
            bool decimal_negative;
            dec.is_the_number_correct(&decimal_negative);
            to_hex = dec.to_hexadecimal();
            cout << "Your hexadecimal number: " << to_hex << '\n';
            if (decimal_negative) { // getting 1's and 2's complement of hexadecimal number
                to_hex.erase(0,1); // getting rid of the minus
                string one_s_hex = dec.get_complement(to_hex, "1s_hex");
                cout << "1's complement: " << one_s_hex << '\n';
                hex.enter_number(true, one_s_hex);
                string to_dec = std::to_string(std::stoi(hex.to_decimal())+1);
                dec.enter_number(true, to_dec);
                string two_s_hex = dec.to_hexadecimal();
                cout << "2's complement: " << two_s_hex << '\n';

            }

        }
        else if (conversion_type == "hex_bin") {
            hex.enter_number();
            string decimal_number = hex.to_decimal();
            dec.enter_number(true, decimal_number);
            string to_bin;
            to_bin = dec.to_binary();
            cout << "Your binary number: " << to_bin << '\n';

        }
        else if (conversion_type == "hex_dec") {
            string to_dec;
            hex.enter_number();
            to_dec = hex.to_decimal();
            cout << "Your decimal number: " << to_dec << '\n';

        }


    }
    void repeat_the_program() // recursive
    {
        int repeat_choice;
        cout <<"\nWant do you want to do (enter number): \n"
               "1. Convert another number\n"
               "2. Switch conversion\n"
               "0. Leave" << std::endl;
        cin >> repeat_choice;
        switch (repeat_choice)
        {
            case 0:
                in_game = false; break;
            case 1:
                menu(); repeat_the_program();
            case 2:
                break;
            default: repeat_the_program();
        }
    }
    void goodbye ()
    {
        cout << "\nThank you for using my program.\nPlease leave your feedback "
                "on my github in case you want to help me improve my programming "
                "skills:\n"
                "https://github.com/kamwro" <<std::endl;
    }
};

int main() {
    Calculator();
    return 0;
}
