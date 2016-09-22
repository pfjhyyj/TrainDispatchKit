# TrainDispatchKit

Train dispatching system by XMQ, YJR, XHY, YYJ

# Problem

一列火车要将n节车厢分别送往 n 个车站，车站按1~n的次序编号， 火车按照 n,n-1,...,1 的编号次序经过车站。假设车厢的编号就是其目的地车站的编号。

# Requirement

给定一个任意的车厢排列次序，设计一个软件系统重新排列车厢， 使其按照从 1 到 n 的次序输出。给出调度详细步骤，并统计出所用栈个数及调度总步数。规定重排调度时车厢只能从入轨到缓冲铁轨， 或者从缓冲铁轨到出轨。

# Solution

# Usage

While run the program, you should create a new queue first. Then, you could do any thing you want: control the program to solve the problem, check the buffer whenever youn want ...  and you are allowed to create another new queue just by typing command 'new' again.

Enjoy yourself!

# Commands

new - create new carriage queue
next (n) - next step
ctn (c) - continue for some steps
ctf - continue until finish
check - check a certain buffer and show its detail
total - show total number of the buffer
quit (q) - quit trk
