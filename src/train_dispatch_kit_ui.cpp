#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <sstream>
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
using std::stringstream;
using std::reverse;
using XXYY::CarriageDipatcher;
using XXYY::Carriage;

TrainDispatchKitUI::TrainDispatchKitUI() {
    quit_  = false;
    queue_exist_ = false;
    m_steps_ = 0;
    StartScreen();
}

TrainDispatchKitUI::~TrainDispatchKitUI() {
    cout << "Good Bye!" << endl;
}

void TrainDispatchKitUI::OperationLoop() {
    while (!quit_) {
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
    cout << "     ctf - continue until finish\n";
    cout << "     check - check a certain buffer and show its detail\n";
    cout << "     total - show total number of the buffer\n";
    cout << "     quit (q) - quit trk" << endl;
    cout << "----------------------------------------------------------" << endl;
}

void TrainDispatchKitUI::ExecuteCommand(string cmd) {
    if (cmd == "next" || cmd == "n") { NextStep(); }
    else if (cmd == "ctn"  || cmd == "c") { ContinueForSteps(); }
    else if (cmd == "ctf") { ContinueUntilFinish(); }
    else if (cmd == "check") { CheckBuffer(); }
    else if (cmd == "quit"  || cmd == "q") { quit_ = true; }
    else if (cmd == "total") { GetBufferNum(); }
    else if (cmd == "new") { CreateQueue(); }
    else { cout << "ERROR: Command Not Found!" << endl; }
}

void TrainDispatchKitUI::CreateQueue() {
    cout << "Input a string as the queue.\n";
    cout << "Every number has a space as separator.\n";
    cout << "(non-digit character will be automatically removed.)" << endl;
    cout << "String << ";
    string queue_Str;
    getline(cin, queue_Str);
    stringstream queue_Ss;
    queue_Ss << queue_Str;
    vector<uint32_t> carriageQueue;
    for (int carriage_des; queue_Ss >> carriage_des;) {
        carriageQueue.push_back(carriage_des);
    }
    reverse(carriageQueue.begin(), carriageQueue.end());
    dispatcher_.reset(new CarriageDipatcher(carriageQueue));
    queue_exist_ = true;
    m_steps_ = 0;
}

void TrainDispatchKitUI::GetBufferNum() {
    int BufferNum = dispatcher_->buffers_used();
    cout << BufferNum << " buffer(s) used." << endl;
    cout << m_steps_ << " steps" << endl;
}

void TrainDispatchKitUI::ContinueForSteps() {
    if (!queue_exist_) {
        cout << "ERROR: You do not have a queue yet." << endl;
        return;
    }
    cout << "Please enter the number of steps that you want to continue for." << endl;
    cout << "Number << ";
    uint32_t steps;
    cin >> steps;
    auto result = dispatcher_->ContinueFor(steps);
    if (result.back() != "Finish") {
        for (auto iter = result.begin(); iter != result.end(); iter++) {
            cout << *iter << endl;
        }
    } else {
        result.pop_back();
        for (auto iter = result.begin(); iter != result.end(); iter++) {
            cout << *iter << endl;
        }
        m_steps_ += result.size();
    }
}

void TrainDispatchKitUI::ContinueUntilFinish() {
	if (!queue_exist_) {
        cout << "ERROR: You do not have a queue yet." << endl;
        return;
    }
    auto result = dispatcher_->NextStep();
    while (result != "Finish") {
        cout << result << endl;
        m_steps_++;
        result = dispatcher_->NextStep();
    }
    cout << "Finish dispatching" << endl;
    int max_size = dispatcher_->buffers_used();
    cout << "The used buffer amount is " << max_size << endl;
    cout << m_steps_ << " steps" << endl;
}

void TrainDispatchKitUI::NextStep() {
    if (!queue_exist_) {
        cout << "ERROR: You do not have a queue yet." << endl;
        return;
    }
    cout << "Calculating the next step...success!" << endl;
    auto result = dispatcher_->NextStep();
    if (result != "Finish") {
        m_steps_++;
    }
}

void TrainDispatchKitUI::CheckBuffer() {
    if (!queue_exist_) {
        cout << "ERROR: You do not have a queue yet." << endl;
        return;
    }
    cout << "Please enter the index of the buffer.\n";
    cout <<  "Number << ";
    size_t index;
    cin >> index;
    auto buffer_ptr = dispatcher_->Buffer(index);
    if (buffer_ptr == nullptr) {
        cout << "ERROR: The buffer doesn't exist." << endl;
    } else {
        // Convert buffer to the order of the real stack
        vector<Carriage> buffer_stack;
        for (auto it = (*buffer_ptr).rbegin(); it != (*buffer_ptr).rend(); it++) {
            buffer_stack.push_back(*it);
        }

        cout << "Buffer " << index << " with carriages below (top-to-bottom): \n";
        for (Carriage carriage : buffer_stack) {
            cout << "Carriage " << carriage.index;
            cout << " with destination " << carriage.destination << endl;
        }
    }
}
