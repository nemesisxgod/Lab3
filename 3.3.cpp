#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<pair<double, double>> cofe(double Ts, double T, double kOst, int t){ //Функция cofe - высчитывает координаты x и y графика остывания кофе
    vector<pair<double, double>> cofeNow; 

    for (int i = 0; i < t; ++i){
        cofeNow.emplace_back(i, T); 
        T -= (kOst * (T - Ts));
    }

    return cofeNow; 
}


pair<double, double> aprox(const vector<pair<double, double>> & cofeNow){ //Функция aprox - высчитывает значения аппроксимирующей прямой
    double sumXY = 0;
    double sumX = 0;
    double sumY = 0;
    double sumSqrX = 0;
    size_t n = cofeNow.size();

    for (auto koord : cofeNow){
        double x = koord.first;
        double y = koord.second;
        sumXY += (x * y);       //Σ xi*yi
        sumX += x;              //Σ xi
        sumY += y;              //Σ yi
        sumSqrX += pow(x, 2);   //(Σ xi)^2
    }

    double a = (n * sumXY - sumX * sumY) / (n * sumSqrX - pow(sumX, 2));
    double b = (sumY - a * sumX) / n;

    return make_pair(a, b);
}


double korrel(const vector<pair<double, double>>& cofeNow){               //Функция korrel - высчитывает значения коэффициента корреляции и значимости
    double mediumX = 0;
    double mediumY = 0;

    for (auto koord : cofeNow){
        double x = koord.first;
        double y = koord.second;
        mediumX += x;
        mediumY += y;
    }

    mediumX /= cofeNow.size();
    mediumY /= cofeNow.size();                                          //Считаем средние икс и игрик

    double sumDxDy = 0;
    double sumSqrDx = 0;
    double sumSqrDy = 0;

    for (auto koord : cofeNow){
        double x = koord.first;
        double y = koord.second;
        sumDxDy += ((x - mediumX) * (y - mediumY));
        sumSqrDx += pow(x - mediumX, 2);
        sumSqrDy += pow(y - mediumY, 2);
    }

    return sumDxDy / sqrt(sumSqrDx * sumSqrDy);
}


int main(){
    system("chcp 1251");
    int t;                                      // время остывания
    double T, Ts, kOst;                         // T кофе, Т окр ср, коэф остывания
    cin >> Ts >> T >> kOst >> t;

    auto cofeNow = cofe(Ts, T, kOst, t);
    auto para = aprox(cofeNow);
    double a = para.first;
    double b = para.second;

    double k = korrel(cofeNow);


    cout << "Время" << "\t" << "Температура кофе" << endl;

    for (auto tempOtTime : cofeNow){
        double time = tempOtTime.first;
        double temperature = tempOtTime.second;

        cout << time << "\t" << temperature << endl;
    }

    cout << "\nЛиния апроксимации: " << "T = " << a << " * t + " << b << endl;
    cout << "\nКоэффициент корреляции " << k << endl;
}