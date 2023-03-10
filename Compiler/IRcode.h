/*
Semantic
ToDO
update to new grammer

Optizer
ToDo
bump to IR code gen, not post gen
Add at least 1 more optizer
update to new grammer

*/


#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "ctype.h"
using namespace std;

ofstream myfile;

void openIRFile(){
    myfile.open ("IRcode.txt");
}

void closeIRFile(){
    myfile.close();
}

void IRLargestVar(int i){
    //myfile << "!LargestVar," << i << "\n";
}

void varEqVar(int id1, int id2){
    string tId1 = "T" + to_string(id1 + 1);
    string tId2 = "T" + to_string(id2 + 1);
    myfile << tId1 << " = " << tId2 << "\n";
    /*
    myfile << tId1 << " = " << data1 << "\n";
    myfile << tId2 << " = " << data2 << "\n";
    myfile << tId2 << " = " << tId1 << "\n";
    
    //fprintf(IRcode, "%s = %s\n", tId1, data1);
    //fprintf(IRcode, "%s = %s\n", tId2, data2);
    //fprintf(IRcode, "%s = %s\n", tId2, tId1);
    */
}

string isRecur(int r){
    if(r == 0){
        return "";
    }
    return "R" + to_string(r);
}

string setParReg(int i){
    return "a" + to_string(i);
}

string setReg(int i){
    if(i >= 9){
        return "s" + to_string(i-9);
    }
    return  "T" + to_string(i+1);
}

void varEqNum(int id1, string data){
    myfile << setReg(id1) << " = " << data << "\n";
}

void IRBinOpStart(int id1, int id2){
    myfile << "\n" << setReg(id1) << " = " << setReg(id2);
}

void IRBinOpStart(int id1, string data){
    myfile << "\n" << setReg(id1) << " = " << data;
}

void IRBinOpAdd(string bin, int id1, int id2, int id3){
    myfile << " " << bin << " " << setReg(id1) << "\n";
    myfile << setReg(id2) << " = " << setReg(id3);
}

void IRBinOpAdd(string bin, string data, int id2, int id3){
    myfile << " " << bin << " " << data << "\n";
    myfile << setReg(id2) << " = " << setReg(id3);
}

void IRBinOpEnd(string bin, int id1, int id2, int id3){
    myfile << " " << bin << " " << setReg(id1) << "\n";
    myfile << setReg(id2) << " = " << setReg(id3) << "\n";
}

void IRBinOpEnd(string bin, string data, int id2, int id3){
    myfile << " " << bin << " " << data << "\n";
    myfile << setReg(id2) << " = " << setReg(id3) << "\n\n";
}

void IRWrite(int id1){
        myfile << "WRITE " << setReg(id1) << "\n";
}

void IRWriteString(string data){
        myfile << "!" << data << "\n";
}

void IRWriteStr(string id1){
        myfile << "WRITE " << id1 << "\n";
}

void IRReturn(int id1){
        myfile << "RETURN " << setReg(id1) << "\n\n";
}

void IRWriteLn(){
    myfile << "WRITELN\n\n";
}

void IRStartFunc(string func){
    myfile << "\n" << func << ":\n";
}

void IRSetParam(int i){
    myfile << setReg(i) << " = " << setParReg(i) << "\n";
}

void IRJal(string func){
    myfile << "jal " << func << "\n";
}

void IRJalReturn(int a){
    myfile << setReg(a) << " = v0\n";
}

void IRIfEqVar(int id1, int id2, int f, int r){
    myfile << "beq " << setReg(id1) << ", " << setReg(id2) << ", if" << f << isRecur(r) << "\n";
}

void IRIfEqNum(int id1, string data, int f, int r){
    myfile << "beq " << setReg(id1) << ", " << data << ", if" << f << isRecur(r) << "\n";
}

void IRIfGrVar(int id1, int id2, int f, int r){
    myfile << "bgt " << setReg(id1) << ", " << setReg(id2) << ", if" << f << isRecur(r) << "\n";
}

void IRIfGrNum(int id1, string data, int f, int r){
    myfile << "bgt " << setReg(id1) << ", " << data << ", if" << f << isRecur(r) << "\n";
}

void IRIfLeVar(int id1, int id2, int f, int r){
    myfile << "blt " << setReg(id1) << ", " << setReg(id2) << ", if" << f << isRecur(r) << "\n";
}

void IRIfLeNum(int id1, string data, int f, int r){
    myfile << "blt " << setReg(id1) << ", " << data << ", if" << f << isRecur(r) << "\n";
}

void IRIfGrEqVar(int id1, int id2, int f, int r){
    myfile << "bge " << setReg(id1) << ", " << setReg(id2) << ", if" << f << isRecur(r) << "\n";
}

void IRIfGrEqNum(int id1, string data, int f, int r){
    myfile << "bge " << setReg(id1) << ", " << data << ", if" << f << isRecur(r) << "\n";
}

void IRIfLeEqVar(int id1, int id2, int f, int r){
    myfile << "ble " << setReg(id1) << ", " << setReg(id2) << ", if" << f << isRecur(r) << "\n";
}

void IRIfLeEqNum(int id1, string data, int f, int r){
    myfile << "ble " << setReg(id1) << ", " << data << ", if" << f << isRecur(r) << "\n";
}




void IRIfEndGoto(int f, int r){
    myfile << "b ifEnd" << f << isRecur(r) << "\n";
}

void IRIfDecl(int f, int r){
    myfile << "if" << f << isRecur(r) << ":\n";
}

void IRElseEndGoto(int f, int r){
    cout << "IR: b elseEnd" << f << isRecur(r) << "\n";
    myfile << "b elseEnd" << f << isRecur(r) << "\n";
}

void IRElseEndDecl(int f, int r){
    cout << "IR: elseEnd" << f << isRecur(r) << ":\n";
    myfile << "elseEnd" << f << isRecur(r) << ":\n";
}

void IRIfEndDecl(int f, int r){
    cout << "IR: ifEnd" << f << isRecur(r) << ":\n";
    myfile << "ifEnd" << f << isRecur(r) << ":\n";
}

void IRJalInput(int a, int in){
    myfile << setParReg(a) << " = " << setReg(in) << "\n";
}

//while stuff
void IRWhileStart(int a){
    myfile << "whileStart" << a << ":\n";
}

void IRWhileEnd(int a){
    myfile << "whileEnd" << a << ":\n";
}

void IRWhileStartGoTo(int a){
    myfile << "b whileStart" << a << "\n";
}

void IRWhileEndGoTo(int a){
    myfile << "b whileEnd" << a << "\n";
}

void IRWhileCode(int a){
    myfile << "whileCode" << a << ":\n";
}

void IRWhileEqVar(int id1, int id2, int f){
    myfile << "beq " << setReg(id1) << ", " << setReg(id2) << ", whileCode" << f<< "\n";
}

void IRWhileEqNum(int id1, string data, int f){
    myfile << "beq " << setReg(id1) << ", " << data << ", whileCode" << f << "\n";
}

void IRWhileGrVar(int id1, int id2, int f){
    myfile << "bgt " << setReg(id1) << ", " << setReg(id2) << ", whileCode" << f << "\n";
}

void IRWhileGrNum(int id1, string data, int f){
    myfile << "bgt " << setReg(id1) << ", " << data << ", whileCode" << f << "\n";
}

void IRWhileLeVar(int id1, int id2, int f){
    myfile << "blt " << setReg(id1) << ", " << setReg(id2) << ", whileCode" << f << "\n";
}

void IRWhileLeNum(int id1, string data, int f){
    myfile << "blt " << setReg(id1) << ", " << data << ", whileCode" << f << "\n";
}

void IRWhileGrEqVar(int id1, int id2, int f){
    myfile << "bge " << setReg(id1) << ", " << setReg(id2) << ", whileCode" << f << "\n";
}

void IRWhileGrEqNum(int id1, string data, int f){
    myfile << "bge " << setReg(id1) << ", " << data << ", whileCode" << f << "\n";
}

void IRWhileLeEqVar(int id1, int id2, int f){
    myfile << "ble " << setReg(id1) << ", " << setReg(id2) << ", whileCode" << f << "\n";
}

void IRWhileLeEqNum(int id1, string data, int f){
    myfile << "ble " << setReg(id1) << ", " << data << ", whileCode" << f << "\n";
}


//==============================================================================================================

void optimizeIR()
{
    ifstream ifs;

    ifs.open("IRcode.txt");
    
    

    // Variables for line construction
    const int linesize = 100;
    char line[linesize];
    int linecounter = 50; // For furture dynamic allocation
    bool flag[linecounter];
    int counter = 0;
    
    //2D Array to store all lines

    char lines[linecounter][linesize];

    // For constant folding
    char remainder1[linesize];
    char remainder2[linesize];
    char newstring[linesize];
    char newvalue[linesize];
    int value1;
    int value2;

    //// For strength reduction
    int count;
    char linesave[100];

    // For dead code elim
    char elimvar[2];

    // For constant prop
    int maxnumsize = 10;
    

    // Fill "lines" array with lines
    while (ifs.getline(line, linesize, '\n'))
    {
        for (int i = 0; i < linecounter; i++)
        {
            for (int j = 0; j < linesize; j++)
            {
                lines[i][j] = line[j];
            }
            
        }
        counter++;
    }

    // Constant propogation
    counter = 0;
    for (int i = 0; i < linecounter; i++)
    {
        // Find if a function declaration is set to an integer
        if (isdigit(lines[i][5]))
        {
            // Integer found
            elimvar[0] = lines[i][0];
            elimvar[1] = lines[i][1];
            
            // Replace all future instances with integer
            // Since integers can have more than 1 character, we have to transfer all characters over
            for (int j = 5; j < linesize; j++)
            {
                remainder1[j] = lines[i][j];
            }

            //Find instance of usage of this variable after first one
            for (int j = i+1; j < linecounter; j++)
            {
                for (int k = 0; k < linesize; k++)
                {
                    if(lines[j][k] == elimvar[0] && lines[j][k+1] == elimvar[1])
                    {
                        // Bump all variables out
                        for (int l = k; l < linesize; l++)
                        {
                            lines[j][l + maxnumsize] = lines[j][l];
                            lines[j][l] = ' ';
                            for (int m = 0; m < maxnumsize; m++)
                            {
                                lines[j][l] = remainder1[l];
                            }
                        }
                    }
                }
            }

            
        }
        
        
    }



    // Constant folding
    // Nested to mark which lines have + signs
    for (int i = 0; i < linecounter; i++)
    {
        for (int j = 0; i < linesize; i++)
        {
            if (lines[i][j] == '+')
            {
                flag[i] = true;
            }
        }
    }
    
    // Combine lines
    for (int i = 0; i < linecounter; i++)
    {
       
        // Current line and next line both have a + 
        if (flag[i] == flag[i + 1])
        {
            

            // Check if both lines have a constant
            if (isdigit(lines[i][10]) && isdigit(lines[i + 1][10]))
            {
                // Since integers can have more than 1 character, we have to transfer all characters over
                for (int j = 10; j < linesize; j++)
                {
                    remainder1[j] = lines[i][j];
                    remainder2[j] = lines[i + 1][j];
                }
                // Convert cstrings to int
                value1 = atoi(remainder1);
                value2 = atoi(remainder2);

                //Store the sum
                value1 = value1 + value2;

                // Convert back to string
                sprintf(newstring, "%d", value1);

                // Put the number back in the line
                for (int j = 10; j < linesize; j++)
                {
                    lines[i + 1][j] = newstring[j];
                }

                // Replace the first entry with spaces
                for (int j = 0; j < linesize; j++)
                {
                    lines[i][j] = ' ';
                }
            }
        }
        
        // Set current line to false 
        flag[i] = 0;
    }

     //Strength reduction
     //Nested loop to mark which lines have * signs
    for (int i = 0; i < linecounter; i++)
    {
        for (int j = 0; i < linesize; i++)
        {
            if (lines[i][j] == '*')
            {
                flag[i] = true;
            }
        }
    }

    // Loop to split up the equation into more lines
    for (int i = 0; i < linecounter; i++)
    {
        if (flag[i] == true)
        {
            
            // Check if line has a constant
            if (isdigit(lines[i][10]))
            {
                // Since integers can have more than 1 character, we have to transfer all characters over
                for (int j = 10; j < linesize; j++)
                {
                    remainder1[j] = lines[i][j];
                }
                // Convert cstrings to int
                count = atoi(remainder1);

                // Save line that's getting broken up
                for (int j = 0; j < linesize; j++)
                {
                    linesave[j] = lines[i][j];
                }

                // Check if split is too large
                if (count >= linecounter - i - 1)
                {
                    //remainder1 = count - (linecounter + i) - 1;
                    
                    // Bump all array values out
                    for (int j = i; j < linecounter; j++)
                    {
                        for (int k = 0; k < linesize; k++)
                        {
                          //  lines[j + remainder1][k] = lines[j][k];
                            
                            // Delete current line
                            lines[j][k] = ' ';
                        }
                    }

                    // Change linesave to have a +
                    linesave[10] = '+';

                    // Copy and paste linesave for all remaining lines except the last one
                    for (int j = i; j < linecounter; j++)
                    {

                    }

                }
            }
        }


    }


    // 


    // Dead code elimination
    // Search through list of lines for a var declaration
    counter = 0;
    for (int i = 0; i < linecounter; i++)
    {
        // Set our variable to check to the first two characters of the line (the variable declaration)
        elimvar[0] = lines[i][0];
        elimvar[1] = lines[i][1];

        // Search for instances of line
        for (int j = 0; j < linecounter; j++)
        {
            if (lines[i][j] == elimvar[0] && lines[i][j+1] == elimvar[1])
            {
                // instance found
                counter++;
            }
        }

        if (counter > 1)
        {
            // Not dead code (used more than once)
            counter = 0;
        }
        else if (counter == 1)
        {
            // Code only appears once 
            // Empty the line
            for (int j = 0; j < linesize; j++)
            {
                lines[i][j] = ' ';
            }
            counter = 0;
        }
    }

    // Write lines to file
    ifs.close();
    
    openIRFile();

    for (int i = 0; i < linecounter; i++)
    {
        for (int j = 0; j < linesize; j++)
        {
            myfile << lines[i][j];
        }
        myfile << "\n";
    }

    closeIRFile();
}
