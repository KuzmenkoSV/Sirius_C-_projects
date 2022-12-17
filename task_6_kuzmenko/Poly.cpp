#include "Poly.h"
#include <ostream>

using namespace std;

Poly::Poly(string s) {

    while(s[0] == '[' || s[0] == ' ')
        s.erase(0, 1);

    while(s[s.size() - 1] == ']' || s[s.size() - 1] == ' ')
        s.erase(s.size() - 1, 1);

    string delimiter = " ";

    int pos = 0;
    string str_coeff;

    while ((pos = s.find(delimiter)) != string::npos)
    {
        str_coeff = s.substr(0, pos);
        coef.push_back(stod(str_coeff));
        s.erase(0, pos + delimiter.length());
    }
    coef.push_back(stod(s));
}

Poly::Poly(std::vector<double> a, int len) {
    coef = a;
    coef.resize(len, 0);
}

Poly::Poly(int len) {
    coef.resize(len, 0);
}

Poly Poly::operator + (Poly a) {

    Poly ans = Poly(coef, max(coef.size(), a.coef.size()));
    for(int i = 0; i < a.coef.size(); i++)
        ans.coef[i] += a.coef[i];
    return ans;
}

Poly Poly::operator - (Poly a) {
    Poly ans = Poly(coef, max(coef.size(), a.coef.size()));
    for(int i = 0; i < a.coef.size(); i++)
        ans.coef[i] -= a.coef[i];
    return ans;
}

Poly Poly::operator*(Poly a) {
    int len_ans = (coef.size() - 1) + (a.coef.size() - 1) + 1;
    Poly ans = Poly(len_ans);
    for(int i = 0; i < coef.size(); i++)
        for(int j = 0; j < a.coef.size(); j++)
            ans.coef[i + j] += coef[i] * a.coef[j];
    return ans;
}

Poly Poly::integral() {
    Poly ans = Poly(coef.size() + 1);
    for(int i = 1; i <= coef.size(); i++)
        ans.coef[i] = coef[i - 1] / i;
    return ans;
}

Poly Poly::der() {
    Poly ans = Poly(coef.size() - 1);
    for(int i = 1; i < coef.size(); i++)
        ans.coef[i - 1] = i * coef[i];
    return ans;
}
