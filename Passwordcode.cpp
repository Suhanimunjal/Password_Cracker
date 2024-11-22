#include <iostream>
#include <string>
#include <chrono>
#include<math.h>
using namespace std;

const int MAX_LENGTH = 6;
const string charset = "abcdefghijklmnopqrstuvwxyz";

void printProgressBar(int attempt, int total) {
    int barWidth = 50;
    float progress = (float)attempt / total;
    int pos = barWidth * progress;

    cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) cout << "=";
        else if (i == pos) cout << ">";
        else cout << " ";
    }
    cout << "] " << int(progress * 100) << " %\r";
    cout.flush();
}

bool bruteForceCrack(string password, string attempt, int index, int &attemptCount) {
    if (attempt == password) {
        return true;
    }

    if (index == MAX_LENGTH) {
        return false;
    }

    for (int i = 0; i < charset.size(); i++) {
        string newAttempt = attempt + charset[i];
        attemptCount++;
        printProgressBar(attemptCount, pow(charset.size(), MAX_LENGTH));
        if (bruteForceCrack(password, newAttempt, index + 1, attemptCount)) {
            cout << "\nPassword cracked: " << newAttempt << endl;
            return true;
        }
    }
    return false;
}

int main() {
    string password;
    cout << "***************************************\n";
    cout << "*                                     *\n";
    cout << "*  Brute-Force Password Cracker!      *\n";
    cout << "*                                     *\n";
    cout << "***************************************\n\n";

    cout << "Enter the password to crack (up to 6 characters, lowercase only): ";
    cin >> password;

    int attemptCount = 0;
    auto start = chrono::high_resolution_clock::now();

    cout << "\nStarting the brute-force attack...\n";
    
    if (!bruteForceCrack(password, "", 0, attemptCount)) {
        cout << "\nPassword not found within the limit.\n";
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Time taken: " << duration.count() << " seconds.\n";

    cout << "\n***************************************\n";
    cout << "*                                     *\n";
    cout << "*  Thank you for using the Password Cracker! *\n";
    cout << "*                                     *\n";
    cout << "***************************************\n";

    return 0;
}
