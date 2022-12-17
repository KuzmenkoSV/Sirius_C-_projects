#include <iostream>
#include "Poly.h"
#include <regex>

using namespace std;

int main(int argc, char ** argv)
{
    cout << "Введите выражение:" << endl;
    vector<string> operators;
    vector<Poly> pol;
    string start;
    Poly pol_i, a, b;

    getline(cin, start);

    regex regular ("(\\[[0-9 ]*\\])");
    cmatch ans;
    int pos;

   while (std::regex_search(start.c_str(), ans, regular))
   {
       pol_i = Poly(ans[0]);
       pos = start.find(ans[0]);
       start.erase(pos, ans[0].length());
       pol.push_back(pol_i);
   }

    reverse(pol.begin(), pol.end());
   for(int i = start.length() - 1; i >= 0; i--)
   {

       if(start[i] == ' ') continue;
       a = pol[pol.size() - 1];
       pol.pop_back();
       if(start[i] == '+')
       {
           b = pol[pol.size() - 1];
           pol.pop_back();
           pol.push_back(a + b);
           continue;
       }
       if(start[i] == '-')
       {
           b = pol[pol.size() - 1];
           pol.pop_back();
           pol.push_back(a - b);
           continue;
       }
       if(start[i] == '*')
       {
           b = pol[pol.size() - 1];
           pol.pop_back();
           pol.push_back(a * b);
           continue;
       }
       if(start[i] == 't' && start[i - 1] == 'n' && start[i - 2] == 'i') {
           pol.push_back(a.integral());
           i-= 2;
           continue;
       }
       if(start[i] == 'r' && start[i - 1] == 'e' && start[i - 2] == 'd') {
           pol.push_back(a.der());
           i -= 2;
           continue;
       }
   }
   vector <double> ans_pol = pol[0].setCoeff();
   cout << " Ответ:"<< endl;
   cout << "[ ";
   for (int i = 0; i < ans_pol.size(); i++)
       cout << ans_pol[i] << " ";
   cout << "]" << endl;
   return 0;
}