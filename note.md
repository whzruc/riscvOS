- Launch the application program when cartridge is entered
  
  - cartridge是什么，要怎么实现
  
  - 

- Read input from the controller
  
  - 读取键盘控制 可以参考样例

- A periodic timer  :heavy_check_mark:

- Draw something in graphics mode
  
  - 研究显存模式
  
  - 编写例子

- Respond to command and video interrupts
  
  - 编写中断程序

- 修改文档

cartridge和firmware应该是两份代码

cartidge是一种即插即用的设备，再按下button就退出了

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
  
  - 需要实现更多的系统调用





### 时钟中断

判断中断是否为时钟中断

确认为时钟中断，调用中断处理程序


