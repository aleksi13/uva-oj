//---------------------------------------------------------------------------
#include <iostream>
#include <string.h>
#include <stdlib.h>

int main()
{
    using namespace std;
    int testsNumber;
    cin >> testsNumber;
    cin.ignore(2);
    for (int tests=0; tests<testsNumber; tests++)
    {
        char instruction[10];
        int instrNo = 0;
        int ram[1000];
        int i;
        for (i=0; i<1000; i++) ram[i] = 0;
        while ( true )
        {
            if (!( cin.getline(instruction, 10) )) break;
            if (strlen(instruction)==0) break;
            ram[ instrNo ] = atoi(instruction);
            instrNo+=1;
        }
        int regs[10];
        for (i=0; i<10; i++) regs[i] = 0;

        bool exit = false;
        int instrExec = 0;
        int currentInstr = 0;
        while ( !exit )
        {
            int hundreds = ram[currentInstr] / 100;
            int tens = (ram[currentInstr] - hundreds * 100) / 10;
            int units = ram[currentInstr] - hundreds * 100 - tens * 10;
            switch ( hundreds )
            {
                case 1:
                    if ( tens==0 && units==0 )
                    {
                        instrExec+=1;
                        cout << instrExec << endl;
                        if (tests<testsNumber-1) cout << endl; 
                        exit = true;
                    }
                    break;
                case 2:
                    regs[ tens ] = units;
                    instrExec+=1;
                    currentInstr+=1;
                    break;
                case 3:
                    regs[ tens ] += units;
                    regs[ tens ] = regs[ tens ] % 1000;
                    instrExec+=1;
                    currentInstr+=1;
                    break;
                case 4:
                    regs[ tens ] *= units;
                    regs[ tens ] = regs[ tens ] % 1000;
                    instrExec+=1;
                    currentInstr+=1;
                    break;
                case 5:
                    regs[ tens ] = regs[ units ];
                    instrExec+=1;
                    currentInstr+=1;
                    break;
                case 6:
                    regs[ tens ] += regs[ units ];
                    regs[ tens ] = regs[ tens ] % 1000;
                    instrExec+=1;
                    currentInstr+=1;
                    break;
                case 7:
                    regs[ tens ] *= regs[ units ];
                    regs[ tens ] = regs[ tens ] % 1000;
                    instrExec+=1;
                    currentInstr+=1;
                    break;
                case 8:
                    regs[ tens ] = ram[ regs[ units ] ];
                    instrExec+=1;
                    currentInstr+=1;
                    break;
                case 9:
                    ram[ regs[ units ] ] = regs[ tens ];
                    instrExec+=1;
                    currentInstr+=1;
                    break;
                case 0:
                    if ( regs[ units ]!=0 )
                        currentInstr = regs[ tens ];
                    else
                        currentInstr+=1;
                    instrExec+=1;
                    break;
            }
        }
    }
    return 0;
}
//---------------------------------------------------------------------------
 
