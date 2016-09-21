#include <iostream>
#include <vector>
#include <stack>
#include "carriage.h"
#include "carriage_buffers.h"
#include "carriage_dispatcher.h"
#include "train_dispatch_kit_ui.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::stack;
using XXYY::CarriageDipatcher;
using XXYY::Carriage;

TrainDispatchKitUI::TrainDispatchKitUI() {
    quit  = false;
    queue_exist = false;
    StartScreen();
}

TrainDispatchKitUI::~TrainDispatchKitUI() {
    cout << "Good Bye!" << endl;
}

void TrainDispatchKitUI::OperationLoop() {
    while (!quit) {
        cout << "Command << ";
        string cmd;
        cin >> cmd;
        ExecuteCommand(cmd);
    }
}

void TrainDispatchKitUI::StartScreen() {
    cout << "                      (@@) (  ) (@)  ( )  @@    ()  @\n";
    cout << "                 (   )\n";
    cout << "             (@@@@)\n";
    cout << "          (    )\n";
    cout << "\n";
    cout << "        (@@@)\n";
    cout << "      ====        ________                ___________\n";
    cout << "  _D _|  |_______/        \\__I_I_____===__|_________|\n";
    cout << "   |(_)---  |   H\\________/ |   |        =|___ ___|\n";
    cout << "   /     |  |   H  |  |     |   |         ||_| |_||\n";
    cout << "  |      |  |   H  |__--------------------| [___] |\n";
    cout << "  | ________|___H__/__|_____/[][]~\\_______|       |\n";
    cout << "  |/ |   |-----------I_____I [][] []  D   |=======|___\n";
    cout << "__/ =| o |=-~~\\  /~~\\  /~~\\  /~~\\ ____Y___________|__|\n";
    cout << " |/-=|___|=    ||    ||    ||    |_____/~\\___/\n";
    cout << "  \\_/      \\_O=====O=====O=====O/      \\_/\n";
    cout << "\n";
    cout << "\n";
    cout << "_/_/_/_/_/              _/_/_/                _/    _/\n";
    cout << "   _/                  _/    _/              _/  _/\n";
    cout << "  _/                  _/_/_/                _/_/\n";
    cout << " _/                  _/    _/              _/  _/\n";
    cout << "_/                  _/    _/              _/    _/\n";
    cout << "\n\n\n";
    cout << "------------------- Train Dispatch Kit -------------------\n";
    cout << "     new - create new carriage queue\n";
    cout << "     next (n) - next step\n";
    cout << "     ctn (c) - continue for some steps\n";
    cout << "     check - check a certain buffer and show its detail\n";
    cout << "     total - show total number of the buffer\n";
    cout << "     quit (q) - quit trk" << endl;
    cout << "----------------------------------------------------------" << endl;
}

void TrainDispatchKitUI::ExecuteCommand(string cmd) {
    if (cmd == "next" || cmd == "n") { NextStep(); }
    else if (cmd == "ctn"  || cmd == "c") { ContinueForSteps(); }
    else if (cmd == "check") { CheckBuffer(); }
    else if (cmd == "quit"  || cmd == "q") { quit = true; }
    else if (cmd == "total") { GetBufferNum(); }
    else if (cmd == "new") { CreateQueue(); }
    else { cout << "ERROR: Command Not Found!" << endl; }
}

void TrainDispatchKitUI::CreateQueue() {
    cout << "Input a string as the queue.\n";
    cout << "(non-digit character will be automatically removed.)" << endl;
    cout << "String << ";
    string queue;
    cin >> queue;
    vector<uint32_t> carriageQueue;
    for (char ch : queue) {
        if (isdigit(ch)) carriageQueue.push_back(ch - '0');
    }
    dispatcher.reset(new CarriageDipatcher(carriageQueue));
    queue_exist = true;
}

void TrainDispatchKitUI::GetBufferNum() {
    int BufferNum = dispatcher->buffers_size();
    cout << "Now " << BufferNum << " buffer(s) exist." << endl;
}

void TrainDispatchKitUI::ContinueForSteps() {
    if (!queue_exist) {
        cout << "ERROR: You do not have a queue yet." << endl;
        return;
    }
    cout << "Please enter the number of steps that you want to continue for." << endl;
    cout << "Number << ";
    uint32_t steps;
    cin >> steps;
    dispatcher->ContinueFor(steps);
}

void TrainDispatchKitUI::NextStep() {
    if (!queue_exist) {
        cout << "ERROR: You do not have a queue yet." << endl;
        return;
    }
    cout << "Calculating the next step...success!" << endl;
    dispatcher->NextStep();
}

void TrainDispatchKitUI::CheckBuffer() {
    if (!queue_exist) {
        cout << "ERROR: You do not have a queue yet." << endl;
        return;
    }
    cout << "Please enter the index of the buffer.\n";
    cout <<  "Number << ";
    size_t index;
    cin >> index;
    auto buffer_ptr = dispatcher->Buffer(index);
    if (buffer_ptr == nullptr) {
        cout << "ERROR: The buffer doesn't exist." << endl;
    } else {
        // TODO: Convert to stack?
        cout << "Buffer " << index << " with carriages below: \n";
        for (Carriage carriage : *buffer_ptr) {
            cout << "Carriage " << carriage.index;
            cout << " with destination " << carriage.destination << endl;
        }
    }
}
