/**
 * @brief the "MIT/X Consortium License", (adapted for EXPARX.COM)
 *
 * Copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 * Permission is hereby  granted,  free of charge,  to  any  person
 * obtaining a copy of this software and  associated  documentation
 * files   (the  "Software"),  to deal  in   the  Software  without
 * restriction, including  without  limitation the rights  to  use,
 * copy,  modify, merge,  publish,  distribute,  sublicense, and/or
 * sell copies of the  Software, and to permit persons  to whom the
 * Software  is  furnished to  do  so,  subject  to  the  following
 * conditions:
 *
 * (See LICENSE.md for complete details)
 *
 */

#include <extras_rsi/gadgets/Spinner.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <iostream>
#include <sstream>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Test SpinnerInterface", "[SpinnerInterface]") {

    rsi::SpinnerMsg good = "[/]";

    for (int i = 0; i < 1000; i++)
        std::cout << "\r" << rsi::spinner(i) << std::flush;

    std::stringstream ss;
    ss << rsi::spinner(0);
    std::string text = ss.str();

    REQUIRE(text == "\033[32m\r[\033[33m+\033[32m]");

}
