

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



## 任务拆解

### 时钟中断

判断中断是否为时钟中断

确认为时钟中断，调用中断处理程序



:exclamation:

## cartridge



期望的结果是插入cartridge之后 可以使用图形模式绘制一个图像

:heavy_check_mark:







## Draw something in graphics mode

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









## video 和command 中断







### Read input from the controller

一开始的代码是没有键盘中断的，只是每次触发时钟中断时，将检测的键盘输入赋值

所以还需要实现键盘中断 需要实现关于键盘输入的系统调用



:exclamation:
