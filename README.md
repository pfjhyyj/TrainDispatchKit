# TrainDispatchKit

SYSU 2015级数据结构Project1


Train dispatching system by 薛明淇，杨竣然，杨奕嘉，徐海洋

# Problem

一列火车要将n节车厢分别送往 n 个车站，车站按1~n的次序编号， 火车按照 n,n-1,...,1 的编号次序经过车站。假设车厢的编号就是其目的地车站的编号。

# Requirement

给定一个任意的车厢排列次序，设计一个软件系统重新排列车厢， 使其按照从 1 到 n 的次序输出。给出调度详细步骤，并统计出所用栈个数及调度总步数。规定重排调度时车厢只能从入轨到缓冲铁轨， 或者从缓冲铁轨到出轨。

# Solution

火车调度按照以下规则进行，直到调度完成：


如果某个缓冲区顶部的火车目的地编号（下简称编号）与当前所需的编号相等（入轨与缓冲区中车厢编号的最大值），从缓冲区弹出该车厢，如果弹出后缓冲区为空，则在逻辑上回收该缓冲区以后使用，从缓冲区的序列中移除。
如此往复，当无法从缓冲区移除火车时，将待调度队列中首位的车厢压入缓冲区序列中的某个缓冲区。
“某个缓冲区”定义如下，按照缓冲区再逻辑上的开辟先后次序，以从先至后的顺序依次检查缓冲区顶部火车编号，找到第一个缓冲区顶部火车编号小于待调度的火车编号的缓冲区，若没有满足条件的缓冲区，则使用新的缓冲区。

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

# build

cmake is requried

```
cd build
cmake -G "the type of output" ..
cd ..

```