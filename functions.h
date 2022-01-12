#pragma once

#include <iostream>

class Function {
    public :

        static std::string XoR(std::string X, std::string Y) {
            std::string Z;
            int len = X.length();
            for(int i = 0; i < len; ++i) {
                if(X[i] != Y[i])
                    Z.push_back('1');
                else
                    Z.push_back('0');
            }
            return Z;
        }

        static std::string AnD(std::string X, std::string Y) {
            std::string Z;
            int len = X.length();
            for(int i = 0; i < len; ++i) {
                if(X[i] == '1' && Y[i] == '1')
                    Z.push_back('1');
                else
                    Z.push_back('0');
            }
            return Z;
        }

        static std::string ADD(std::string X, std::string Y) {
            std::bitset<32> const x(X);
            std::bitset<32> const y(Y);
            std::bitset<32> const m("1");

            std::bitset<32> result;
            for (auto i = 0; i < result.size(); ++i) {
                std::bitset<32> const diff(((x >> i)&m).to_ullong() + ((y >> i)&m).to_ullong() + (result >> i).to_ullong());
                result ^= (diff ^ (result >> i)) << i;
            }

            std::string sum = result.to_string();
            if(sum.length() > 32)
                sum.erase(0, sum.length()-32);
            return sum;
        }


        static std::string rotateRight(std::string X, int n) {
            int len = X.length();
            char ch;
            while(n--) {
                ch = X[len-1];
                X.pop_back();
                X.insert(X.begin(), ch);
            }
            return X;
        }

        static std::string shiftRight(std::string X, int n) {
            int nn = n;
            while(n--) {
                X.pop_back();
            }
            std::string zeros = "";
            while(nn--) zeros.push_back('0');
            X = zeros + X;
            return X;
        }

        static std::string majority(std::string X, std::string Y, std::string Z) {
            return XoR(AnD(X, Y), XoR(AnD(Y, Z), AnD(Y, Z)) );
        }

        static std::string choice(std::string X, std::string Y, std::string Z) {
            return XoR(AnD(X, Y), AnD(X, Z));
        }

        static std::string summation0(std::string X) {
            return XoR(rotateRight(X, 2), XoR(rotateRight(X, 13), rotateRight(X, 22)));
        }

        static std::string summation1(std::string X) {
            return XoR(rotateRight(X, 6), XoR(rotateRight(X, 11), rotateRight(X, 25)));
        }

        static std::string sigma0(std::string X) {
            return XoR(rotateRight(X, 7), XoR(rotateRight(X, 18), shiftRight(X, 3)));
        }

        static std::string sigma1(std::string X) {
            return XoR(rotateRight(X, 17), XoR(rotateRight(X, 19), shiftRight(X, 10)));
        }
};