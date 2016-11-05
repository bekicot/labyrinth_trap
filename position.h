//
//  position.h
//  labirin_trap
//
//  Created by Yana Agun Siswanto on 11/6/16.
//  Copyright © 2016 Yana Agun Siswanto. All rights reserved.
//

#ifndef position_h
#define position_h

#include <stdio.h>

struct Position {
    int x;
    int y;
};

typedef struct Position position;

position createPosition(int x, int y);

#endif /* position_h */
