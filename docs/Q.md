# 问题记录


## 线程堆栈初始化

- STK 栈帧？ SOL 栈帧？

STK 是指？
SOL 是指？

- rt_hw_stack_init 入口参数 栈帧地址为什么是 rt_uint8_t 类型？

```c
rt_uint8_t *rt_hw_stack_init(void *entry,
                             void *parameter,
                             rt_uint8_t *stack_addr)
```


- Hexspeak: ((rt_uint32_t *)stack_frame)[i] = 0xdeadbeef;

0xdeadbeef -> "dead beef"

[《什么是 0xdeadbeef ？》](https://blog.csdn.net/weixin_43921239/article/details/103295616)


- 为什么调用 rt_hw_stack_init 是 stack_addr (栈顶指针-4), 而后在 rt_hw_stack_init 中 stk + 4
