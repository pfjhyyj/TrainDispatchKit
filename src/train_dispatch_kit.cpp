#include <iostream>
#include "train_dispatch_kit_ui.cpp"

TrainDispatchKitUI trk_ui;

int main(int argc, char const *argv[]) {
    trk_ui.OperationLoop();
    return 0;
}