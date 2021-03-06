//---------------------------------------------------------------------------
#include <iostream>

enum FIELDS { empty, wPawn, wKnight, wBishop, wRook, wQueen, wKing,
                     bPawn, bKnight, bBishop, bRook, bQueen, bKing, out };

FIELDS board[12][12];

FIELDS Piece(char l)
{
    switch ( l )
    {
        case 'P': return wPawn;
        case 'N': return wKnight;
        case 'B': return wBishop;
        case 'R': return wRook;
        case 'Q': return wQueen;
        case 'K': return wKing;
        case 'p': return bPawn;
        case 'n': return bKnight;
        case 'b': return bBishop;
        case 'r': return bRook;
        case 'q': return bQueen;
        case 'k': return bKing;
        case '.': return empty;
    }
}

bool isEmpty()
{
    for (int i=0; i<8; i++) for (int j=0; j<8; j++) if ( board[i+2][j+2] != empty ) return false;
    return true;
}

bool PawnChecks(int r, int c, bool WhiteKing)
{
    FIELDS king;
    int i, j;
    if (WhiteKing)
    {
        if (board[r+1][c-1]==wKing) return true;
        if (board[r+1][c+1]==wKing) return true;
    }
    else
    {
        if (board[r-1][c-1]==bKing) return true;
        if (board[r-1][c+1]==bKing) return true;
    }
    return false;
}

bool KnightChecks(int r, int c, bool WhiteKing)
{
    FIELDS king;
    if (WhiteKing) king = wKing; else king = bKing;
    int i, j;
    if (board[r-2][c-1]==king) return true;
    if (board[r-2][c+1]==king) return true;
    if (board[r+2][c-1]==king) return true;
    if (board[r+2][c+1]==king) return true;
    if (board[r-1][c-2]==king) return true;
    if (board[r-1][c+2]==king) return true;
    if (board[r+1][c-2]==king) return true;
    if (board[r+1][c+2]==king) return true;
    return false;
}

bool BishopChecks(int r, int c, bool WhiteKing)
{
    FIELDS king;
    if (WhiteKing) king = wKing; else king = bKing;
    int i, j;
    for (i=1; i<8; i++)
    {
        if (board[r-i][c-i]==king) return true;
        if (board[r-i][c-i]!=empty) break;
    }
    for (i=1; i<8; i++)
    {
        if (board[r-i][c+i]==king) return true;
        if (board[r-i][c+i]!=empty) break;
    }
    for (i=1; i<8; i++)
    {
        if (board[r+i][c-i]==king) return true;
        if (board[r+i][c-i]!=empty) break;
    }
    for (i=1; i<8; i++)
    {
        if (board[r+i][c+i]==king) return true;
        if (board[r+i][c+i]!=empty) break;
    }
    return false;
}

bool RookChecks(int r, int c, bool WhiteKing)
{
    FIELDS king;
    if (WhiteKing) king = wKing; else king = bKing;
    int i, j;
    for (i=1; i<8; i++)
    {
        if (board[r-i][c]==king) return true;
        if (board[r-i][c]!=empty) break;
    }
    for (i=1; i<8; i++)
    {
        if (board[r+i][c]==king) return true;
        if (board[r+i][c]!=empty) break;
    }
    for (i=1; i<8; i++)
    {
        if (board[r][c-i]==king) return true;
        if (board[r][c-i]!=empty) break;
    }
    for (i=1; i<8; i++)
    {
        if (board[r][c+i]==king) return true;
        if (board[r][c+i]!=empty) break;
    }
    return false;
}

bool QueenChecks(int r, int c, bool WhiteKing)
{
    FIELDS king;
    if (WhiteKing) king = wKing; else king = bKing;
    int i, j;
    for (i=1; i<8; i++)
    {
        if (board[r-i][c]==king) return true;
        if (board[r-i][c]!=empty) break;
    }
    for (i=1; i<8; i++)
    {
        if (board[r+i][c]==king) return true;
        if (board[r+i][c]!=empty) break;
    }
    for (i=1; i<8; i++)
    {
        if (board[r][c-i]==king) return true;
        if (board[r][c-i]!=empty) break;
    }
    for (i=1; i<8; i++)
    {
        if (board[r][c+i]==king) return true;
        if (board[r][c+i]!=empty) break;
    }
    
    for (i=1; i<8; i++)
    {
        if (board[r-i][c-i]==king) return true;
        if (board[r-i][c-i]!=empty) break;
    }
    for (i=1; i<8; i++)
    {
        if (board[r-i][c+i]==king) return true;
        if (board[r-i][c+i]!=empty) break;
    }
    for (i=1; i<8; i++)
    {
        if (board[r+i][c-i]==king) return true;
        if (board[r+i][c-i]!=empty) break;
    }
    for (i=1; i<8; i++)
    {
        if (board[r+i][c+i]==king) return true;
        if (board[r+i][c+i]!=empty) break;
    }
    return false;
}

int main()
{
    using namespace std;
    int i, j;
    int game = 1;
    while ( true )
    {
        bool blackCheck = false;
        bool whiteCheck = false;
        for (i=0; i<12; i++) for (j=0; j<12; j++) board[i][j] = out;
        char row[10];
        for (i=0; i<8; i++)
        {
            cin.getline(row, 10);
            for (j=0; j<8; j++) board[i+2][j+2] = Piece( row[j] );
        }
        cin.getline(row, 10);
        if ( isEmpty() ) break;
        for (int row=0; row<8; row++)
        {
            for (int column=0; column<8; column++)
            {
                switch ( board[row+2][column+2] )
                {
                    case wPawn:
                        blackCheck = PawnChecks(row+2, column+2, false);
                        break;
                    case wKnight:
                        blackCheck = KnightChecks(row+2, column+2, false);
                        break;
                    case wBishop:
                        blackCheck = BishopChecks(row+2, column+2, false);
                        break;
                    case wRook:
                        blackCheck = RookChecks(row+2, column+2, false);
                        break;
                    case wQueen:
                        blackCheck = QueenChecks(row+2, column+2, false);
                        break;

                    case bPawn:
                        whiteCheck = PawnChecks(row+2, column+2, true);
                        break;
                    case bKnight:
                        whiteCheck = KnightChecks(row+2, column+2, true);
                        break;
                    case bBishop:
                        whiteCheck = BishopChecks(row+2, column+2, true);
                        break;
                    case bRook:
                        whiteCheck = RookChecks(row+2, column+2, true);
                        break;
                    case bQueen:
                        whiteCheck = QueenChecks(row+2, column+2, true);
                        break;
                }
                if (blackCheck || whiteCheck) break;
            }
            if (blackCheck || whiteCheck) break;
        }
        if ( blackCheck ) cout << "Game #" << game << ": black king is in check." << endl;
        if ( whiteCheck ) cout << "Game #" << game << ": white king is in check." << endl;
        if ( !(blackCheck || whiteCheck) ) cout << "Game #" << game << ": no king is in check." << endl;
        game+=1;
    }
    return 0;
}
//---------------------------------------------------------------------------
