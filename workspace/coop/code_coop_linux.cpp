/*************************************************************************************
 * Copyright (c) 2019 Xiaoyang Xu, Masoud Ghaffarinia, Wenhao Wang, and Kevin Hamlen *
 * The University of Texas at Dallas                                                 *
 *                                                                                   *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of   * 
 * this software and associated documentation files (the "Software"), to deal in     *
 * the Software without restriction, including without limitation the rights to      *
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of  *
 * the Software, and to permit persons to whom the Software is furnished to do so,   *
 * subject to the following conditions:                                              *
 *                                                                                   * 
 * The above copyright notice and this permission notice shall be included in all    *
 * copies or substantial portions of the Software.                                   *
 *                                                                                   *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR        *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS  *
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR    *
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER    *
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN           *
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.        *
 *************************************************************************************/
 
/* This file is part of the ConFIRM test suite, whose initial documentation can be
   found in the following publication:

   Xiaoyang Xu, Masoud Ghaffarinia, Wenhao Wang, Kevin W. Hamlen, and Zhiqiang Lin.
   "ConFIRM: Evaluating Compatibility and Relevance of Control-flow Integrity 
   Protections for Modern Software."  In Proceedings of the 28th USENIX Security
   Symposium, August 2019. */

/* For a detailed explanation of CODE-COOP attack, see the following publication:

   Wenhao Wang and Xiaoyang Xu and Kevin W. Hamlen.
   "Object Flow Integrity."  In Proceedings of the 24th ACM Conference on Computer 
   and Communications Security (CCS). */
 
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/application.h>
#include <iostream>

// Define a Gtk Window class with one button.
class CODECOOP : public Gtk::Window
{
public:
    CODECOOP();
    virtual ~CODECOOP();
protected:
    // Signal handlers:
    void on_button_clicked();
    // Member widgets:
    Gtk::Button m_button;
};

CODECOOP::CODECOOP()
: m_button("This is a test for CODE-COOP attack")
{
    set_border_width(10);
    m_button.signal_clicked().connect(sigc::mem_fun(*this, &CODECOOP::on_button_clicked));
    add(m_button);
    m_button.show();
}

CODECOOP::~CODECOOP()
{
}

void CODECOOP::on_button_clicked()
{
    std::cout << "This is a test for CODE-COOP attack" << std::endl;
}

struct __attribute__((packed)) MainStack {
  char buffer[1];
  CODECOOP codecoop;
};


int main (int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "");

    // CODECOOP codecoop;
    MainStack mainstack;
    // function call that leads to buffer overflow 
    // char buffer[1];
    printf("Any input can lead to buffer overwrite: \n");
    scanf("%s", mainstack.buffer);

    // Shows the window and returns when it is closed. 
    // In run(), it calls member function of codecoop. The codecoop pointer is stored
    // on the stack so that the above buffer overwrite vulnerability can rewrite this
    // pointer with one that points to a counterfeit object. Although CFI solutions
    // can guarantee that app->run flows to a valid target, the function call to 
    // other member function of codecoop in trusted module can therefore escape the
    // CFI sandbox.
    return app->run(mainstack.codecoop);
}
