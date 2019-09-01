//
//  main.cpp
//  test
//
//  Created by Te-Wei Tsai on 5/31/14.
//  Copyright (c) 2014 Te-Wei Tsai. All rights reserved.
//

#include <iostream>
#include "Token_stream.h"
#include "Utility.h"

int main()
{
    Token_stream ts;

    try {
        double val = 0;
        while (std::cin) {
            Token t = ts.get();
            
            // 'q' for quit
            if (t.kind == 'q') {
                break;
            }

            // ';' for "print now"
            if (t.kind == ';') {
                std::cout << "=" << val << '\n';
            }
            else {
                ts.putback(t);
                val = expression(ts);
            }
        }
    }
    catch (std::exception& e) {
        std::cerr << "error: " << e.what() << '\n';
        return 1;
    }
    catch (...) {
        std::cerr << "Oops: unknown exception!\n"; 
        return 2;
    }
}