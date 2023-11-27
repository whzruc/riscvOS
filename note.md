# Phase 2

## 程序结构分析

- crt0.s 启动程序 先调用init 再调用main 不用改

- interrupt.s 中断控制
  
  - 需要实现系统调用

- main.c main函数

- startup.c 
  
  - init函数
    
    - 只读数据段复制到数据段
    
    - bss段内容初始化为0
    
    - 启用所有中断源
    
    - 配置定时器中断
  
  - c_interrupt_handler
    
    - 更新比较值 触发下一个中断
    
    - 增加全局计数器gloabl
    
    - 读取控制器状态并将其保存在controller_status中

### 任务拆解

### 时钟中断

判断中断是否为时钟中断

确认为时钟中断，调用中断处理程序

:heavy_check_mark:

### cartridge

期望的结果是插入cartridge之后 可以使用图形模式绘制一个图像

因为期望的系统调用在cartridge中，所以需要先实现这个



换了给的例子之后可以正常触发中断并且显示正确的结果

:heavy_check_mark:






### Draw something in graphics mode

text模式

512*288 长64个 宽36

Text Data 每位存一个字符 

Text Color 

高4位存背景颜色低4位存字体颜色

和data一样，使用一个字节表示颜色

| Bit         | 7..4     | 3..0     |
| ----------- | -------- | -------- |
| Description | BG Color | FG Color |

Text Palette

调色板 

2*16\*4B=0x80 128B

应该是对于颜色的全局定义

Graphics Mode

与第一版不同主要是在背景图

一个512*288的图像可以由 576(32\*18) 16*16的子图代替

先不考虑子图模式

XY 表示图像的左上位置 Z表示 图层直接设置为0即可

(想全屏显示X应该是512 Y应该是288)

先生成背景图 然后更改Mode control 的mode位即可 其他保持不变

:exclamation:



这一部分选择在cartridge中实现



### video 和command 中断



 Interrupt Enable Register

The layout of the Interrupt Enable Register can be seen in the table below. 

| Bit         | 31..6    | 5    | 4    | 3        | 2    | 1   | 0   |
| ----------- | -------- | ---- | ---- | -------- | ---- | --- | --- |
| Description | Reserved | D2IE | D1IE | Reserved | CMIE | VIE | CIE |

The CIE bit represents the Cartridge Interrupt Enable bit, the VIE bit represents the Video Interrupt Enable bit, the CMIE bit represents the Command Interrupt Enable bit, and the D1IE and D2IE bits represent the DMA channel 1 and 2 Interrupt Enable bits respectively. The CIE, VIE, CMIE, D1IE, and D2IE have corresponding Pending Interrupt bits CIP, VIP, CMIP, D1IP, and D2IP in the [Interrupt Pending Register](#interrupt-pending-register).

Interrupt Pending Register

See table below for the layout of the Interrupt Pending Register. The pending interrupt is cleared by writing a 1 to the corresponding bit, **NOT** by writing a zero. The reason for writing a 1 is that the register doesn't need to be read ANDed and then written back in order to clear the pending interrupt. 

| Bit         | 31..6    | 5    | 4    | 3        | 2    | 1   | 0   |
| ----------- | -------- | ---- | ---- | -------- | ---- | --- | --- |
| Description | Reserved | D2IP | D1IP | Reserved | CMIP | VIP | CIP |

中断使能寄存器 开所有中断

Pending Register中断待处理寄存器

某个中断事件发生 对应的中断位会被置为1，表示该中断事件需要被处理

位 2 是 CMIP（命令中断待处理位），位 1 是 VIP（视频中断待处理位），位 0 是 CIP（卡带中断待处理位）

例子是在cart中用了，在这个作业里面在firmware中使用 初始化图形界面时video中断，开始接收键盘中断控制光标移动，按下cmd后触发cmd中断，切换显示模式

:exclamation:





### Read input from the controller

一开始的代码是没有键盘中断的，只是每次触发时钟中断时，将检测的键盘输入赋值

所以还需要实现键盘中断 需要实现关于键盘输入的系统调用

需要判断mcause的值是不是11[原因](https://web.cecs.pdx.edu/~harry/riscv/RISCV-Summary.pdf)

:heavy_check_mark:

这里引用了例子的代码，别的方式我尝试了，都是不行的，原因未知





# Phase 3

## to-do list

### 在firmware中实现系统调用

考虑之后提供xxxtest更直观一些

后续的测试考虑实现在cartridge里面

main里面只提供两个进程

idle

还有waitfor cartidge

#### context_switch

结合例子 测试是在定时器中实现定时切换两个线程的上下文 一个显示A 一个显示OS_start

现象，运行后会先出现OS_START 证明malloc成功 然后是两个线程显示来回切换



(验收通过后写一下)

| 本地test    | 验收 |
| ----------- | ---- |
| 11.19(pass) |   √   |





#### malloc

例子是显示OS_start

| 本地test    | 验收 |
| ----------- | ---- |
| 11.19(pass) |   √   |

这个必须自己重新实现的 发现调用默认malloc 无法分配成功

0x70fff000 stack

理想的分配结果是 7000xxxx 7000xxxx

#### osInit

初始化并且为thread数组分配空间





#### thread

:heavy_check_mark:



#### scheduler

进程发送切换的时机

- 主动放弃，显示调用wait或者sleep
- 想获取的资源当前不可用 获得未释放的锁
- 外部中断，进行进程切换



进程调度算法

包含

队列的存的就是tid 自己实现了一个 但是不是线程安全的 

ready_list 优先队列 排序方法为优先级 存放着未开始执行的队列 执行进程调度时优先级作为先后的顺序



Waiting_list 普通队列 (调用sleep或wait后 放入该队列)

finsih_list list 普通队列 执行完进程之后放入这个队列进行删除资源 不能转为其他状态(一个进程执行完毕或者exit之后直接删除)



当用户进程A发生中断或系统调用之后，首先其中断帧会被保存，CPU进入内核态，执行中断处理函数。在执行完毕中断处理函数后，操作系统检查当前进程是否需要调度，如果需要，就把当前的进程状态保存，switch到另一个进程B中。注意在执行上面的操作的时候，进程A处于内核态，类似的，调度后我们到达的是进程B的内核态。进程B从系统调用中返回，继续执行。如果进程B在中断或系统调用中被调度，控制权可能转交给进程A的内核态，这样进程A从内核态返回后就可以继续执行之前的代码了。

![Flowchart](/home/whz/Downloads/Flowchart.jpg)





上述整体看到的结果是交替打印A和B 最后两个进程退出销毁资源 重新到main进程

:heavy_check_mark:(firmware测试成功)











#### mutex

维护一个mutex数组 每创建一个mutex 

每个mutex对象包含一个owner和waiting_list

当上锁时，检测当前锁是否已经存在owner如果存在则阻塞当前线程，并且将线程加入该锁的等待队列

如果该锁没有owner则上锁

释放锁时

如果waitinglist为空则直接释放owner

如果waiting不空则将所有线程排除 同时恢复owner(测试了上面的wait)

加锁::heavy_check_mark:

释放锁存在bug





#### condition

也有owner和waiting_list

维护一个cond_list的数组

wait等待锁 解锁 将当前thread放入waitinglist 挂起当前线程最后再上锁



notifone

让waitinglist中每个thread都重新唤醒



notfiyAll

重复调用waitinglist

未实现







#### video

:heavy_check_mark:









### 为其他group编写cartridge以及测试功能

video测试

:heavy_check_mark:

实际进程切换已经成功 

但是由于gp 没法打印出来





### submission











