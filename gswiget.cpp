#include "gswiget.h"

GSWiget::GSWiget(QWidget *parent) :
    QWidget(parent)
{
}

#define BASE_FREQ 440.0000

int CORDS_INDEXS[] = {2,5,8,11,13,16};

Note Notes[MAX_NOTES]= {               //cord
    //C D        base f                   0x draw poerativ
    //                          cord on qiotar
   //                            index
    //                               semitons form base
    //                                   semotons from previous
    {"do", "C",0,false,false,0x0,0, 0,  -9,  2, 4},
    {"re", "D",0,false,false,0x0,0, 1,  -7,  2, 4},
    {"mi", "E",0,false,false,0x0,1, 2,  -5,  1, 4}, // E
    {"fa", "F",0,false,false,0x1,0, 3,  -4,  2, 4},
    {"sol","G",0,false,false,0x0,0, 4,  -2,  2, 4}, //               2 draw portativ black / 1 grey 0 no
    {"la", "A",0,false,false,0x1,2, 5,   0,  2, 4}, // A              > base note 440 Hz
    {"si", "B",0,false,false,0x0,0, 6,   2,  1, 4},
    {"do", "C",0,false,false,0x1,0, 7,   3,  2, 5},
    {"re", "D",0,false,false,0x0,3, 8,   5,  2, 5},//  D
    {"mi", "E",0,false,false,0x2,0, 9,   7,  1, 5},
    {"fa", "F",0,false,false,0x0,0, 10,  8,  2, 5},
    {"sol","G",0,false,false,0x2,4, 11, 10,  2, 5},//  G
    {"la", "A",0,false,false,0x0,0, 12, 12,  2, 5},
    {"si", "B",0,false,false,0x2,5, 13, 14,  1, 5},//  B
    {"do", "C",0,false,false,0x0,0, 14, 15,  2, 6},
    {"re", "D",0,false,false,0x2,0, 15, 17,  2, 6},
    {"mi", "E",0,false,false,0x0,6, 16, 19,  1, 6},//   E
    {"fa", "F",0,false,false,0x2,0, 17, 20,  2, 6},
    {"sol","G",0,false,false,0x0,0, 18, 22,  2, 6},
    {"la", "A",0,false,false,0x1,0, 19, 24,  2, 6},
    {"si", "B",0,false,false,0x0,0, 20, 26,  1, 6},
    {"do", "C",0,false,false,0x1,0, 21, 27,  2, 7},
    {""  , "", 0,false,false,0x0,8, 22, 28,  0, 0},   // HIGHER
};

