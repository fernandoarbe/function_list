/*==========================================================================
|  Program: javascript_functions.exe
|  Author:  Fernando Arbe Revoredo
|
|  Purpose:
|      List javascript functions with line numbers to guide a developer
|      throught his own code.
|
|  Initial parameters:
|      (none)
|
|  Inputs:
|      File fullpath, not need to write, could be dragging file to the console
|
|  Outputs:
|      LineNo: Line string of function
|
|  Required Features Not Included:
|
|  Known Bugs:
|      - Program do not validate if file exists.
|
|
*===========================================================================*/

#include <windows.h>

#include <iostream>
#include <string>
#include <fstream>



using namespace std;


struct StringFx {
    string replaceStr(string myString, const string& strFind, const string& strReplaceWith) {
        size_t start_pos = 0;
        size_t strFind_lenght = strFind.length();
        while ((start_pos = myString.find(strFind, start_pos)) != string::npos) {
            myString.replace(start_pos, strFind_lenght, strReplaceWith);
            start_pos += strFind_lenght;
        }
        return myString;
    }
    string toLower2(string myString) {
        short int nPosition;

        for (nPosition = 0; nPosition < myString.length(); nPosition++) {
            myString[nPosition] = tolower(myString[nPosition] );
        }
        return myString;
    }
    string lpad(string myString, unsigned short int resultLength, const char padchar = '0') {
        return myString.insert(0, resultLength - myString.length(), padchar);
    }

    string ltrim(string myString, const string& chars = "\t\n\v\f\r "){
        //http://www.martinbroadhurst.com/how-to-trim-a-stdstring.html
        myString.find_first_not_of(chars);
        myString.erase(0, myString.find_first_not_of(chars));
        return myString;
    }
    string rtrim(string myString, const string& chars = "\t\n\v\f\r "){
        myString.erase(0, myString.find_last_not_of(chars));
        return myString;
    }

    string trim(string myString, const string& chars = "\t\n\v\f\r "){
        return ltrim(rtrim(myString, chars), chars);
    }
    string firstWord(string myString, const string chars = " ") {
        StringFx stringFx;
        unsigned short int nPos;

        myString = stringFx.ltrim(myString);
        nPos = myString.find_first_of(chars);
        myString = myString.substr(0,nPos);
        return myString;
    }
    unsigned short int count_chars(string myString, const char findChar) {
        unsigned short int nPosition = 0;
        unsigned short int nFounded = 0;

        for (nPosition = 0; nPosition < myString.length(); nPosition++) {
            if (myString[nPosition] == findChar){
                nFounded++;
            }
        }
        return nFounded;
    }
    bool isFunctionDeclaration (string myString) {
        unsigned short int nCount1;
        unsigned short int nCount2;
        unsigned short int nCount3;
        StringFx stringFx;
        nCount1 = stringFx.count_chars(myString, '}');

        if (nCount1 > 0) {
            return false;
        }
        nCount1 = stringFx.count_chars(myString, '(');
        if (stringFx.isFunctionDeclaration2(myString) == false) {
            return false;
        }
        if (nCount1 == 0) {
            return false;
        }
        nCount2 = stringFx.count_chars(myString, ')');
        if (nCount2 == 0) {
            return false;
        }
        if (nCount1 != nCount2) {
            return false;
        }
        myString.erase(0, myString.find_last_of(')'));

        nCount3 = stringFx.count_chars(myString, '{');
        if (nCount3 == 1) {
            return true;
        } else {
            return false;
        }
    }
    bool isFunctionDeclaration2 (string myString) {
        StringFx stringFx;
        string reservedList[] = {"switch", "if", "for", "else", "}", "while"};
        string reservedWord;
        myString = stringFx.firstWord(myString);
        for (int i = 0; i < 6; i++) {
            reservedWord = reservedList[i];
            if (reservedWord.find(myString) != string::npos){
                return false;
            }
        }
        //cout << myString;
        return true;
    }
    bool has_includeMe_word (string myString) {
        StringFx stringFx;
        string includeMe_words[] = {"//watch", "/*watch"};
        string includeMe_word;
        //myString = stringFx.firstWord(myString);
        myString = stringFx.toLower2(myString);
        for (short int i=0; i < 2; i++){
            includeMe_word = includeMe_words[i];
            if (myString.find(includeMe_word) != string::npos) {
                return true;
            }
        }
    }
};

int main()
{
    string strFilePath;
    string strFilePath2;
    string strFileName;
    string strCurrentLine;
    string strConsoleTitle;

    string texto1;
    short int nLastFunctionLine1;
    short int nLastFunctionLine2;
    short int nLastFunctionLine3;
    short int nRefreshes;

    unsigned short int nLinea = 0;
    StringFx stringFx;

    texto1 = "HOLA MUNdito";
    cout << stringFx.toLower2(texto1) << endl;
    cout << "Ingrese la ruta del archivo a analizar: ";
    cin >> strFilePath;
    cout << endl;
    strFileName = strFilePath;
    strFileName = strFileName .erase(0, strFileName.find_last_of("\\") + 1 );
    strConsoleTitle = "functions of " + strFileName;
    SetConsoleTitle(strConsoleTitle.c_str());
    nLastFunctionLine1 = 0;
    nLastFunctionLine2 = 10000;
    nLastFunctionLine3 = 0;
    nRefreshes = 0;

    while (true) {

        if ((nLastFunctionLine1 != nLastFunctionLine2)) {

            system("CLS");
            cout << "File: " << strFilePath << endl ;
            cout << "refreshes: " << nRefreshes << endl;
            cout << "****************************************";
            cout << endl << endl << endl;
            nRefreshes++;
        }

        nLinea = 0;
        ifstream srcFile(strFilePath);
        while (getline (srcFile, strCurrentLine)){
            strCurrentLine = stringFx.ltrim(strCurrentLine);
            nLinea ++;
            if ((stringFx.isFunctionDeclaration(strCurrentLine) == true) ||
                (stringFx.has_includeMe_word(strCurrentLine) == true)){
                nLastFunctionLine3 = nLinea;
                if (nLastFunctionLine1 != nLastFunctionLine2) {
                    cout << stringFx.lpad(to_string(nLinea), 4) << ": " << strCurrentLine << endl;
                }

            }
        } //while
        nLastFunctionLine1 = nLastFunctionLine2;
        nLastFunctionLine2 = nLastFunctionLine3;
        srcFile.close();
        Sleep(3000);
    }

    return 0;
}


