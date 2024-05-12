#include <iostream> 
#include <cmath> 
#include <iomanip> 
#include <fstream> 

using namespace std;

double firstFragm(double x) {
    double res = -sqrt(9-(x+6)*(x+6));
    if (abs(res) < 0.000001) {
        res = 0.0;
    }
    return res;
}

double secondFragm(double x) {
    double res = x+3;
    return res;
}

double thirdFragm(double x) {
    double res = sqrt(9-x*x);
    if (abs(res) < 0.000001) { 
        res = 0.0; 
    }
    return res;
}

double fourthFragm(double x) {
    double res = -x+3;
    return res;
}

double fifthFragm(double x) {
    double res = x/2.0-3.0/2.0;
    return res;
}

int main() {
    double xStart = -9.0;
    double xEnd = 9.0;
    double dx = 1.0;

    ofstream outfile("test_c.txt");
    if (!outfile.is_open()) {
        cout << "При открытии файла произошла ошибка" << endl;
        return 1;
    }
    outfile << setw(10) << "x" << setw(10) << "y" << endl;
    for (double x = xStart; x <= xEnd; x += dx) {
        if (abs(x) < 0.000001) {
            x = 0.0;
        }

        if (x >= -9.0 && x < -6.0) {
            outfile << setw(10) << x << setw(10) << firstFragm(x) << endl;
        }
        if (x >= -6.0 && x < -3.0) {
            outfile << setw(10) << x << setw(10) << secondFragm(x) << endl;
        }
        if (x >= -3.0 && x < 0.0) {
            outfile << setw(10) << x << setw(10) << thirdFragm(x) << endl;
        }
        if (x >= 0.0 && x < 3.0) {
            outfile << setw(10) << x << setw(10) << fourthFragm(x) << endl;
        }
        if (x >= 3.0 && x <= 9.0) {
            outfile << setw(10) << x << setw(10) << fifthFragm(x) << endl;
        }
    }
}
