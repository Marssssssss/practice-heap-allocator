感谢 CCareaga/heap_allocator 写的简单版本堆分配器的启发，网址：https://github.com/CCareaga/heap_allocator 。准备自己实现一个练练手。  

主要借用 `malloc` 分配一块空间出来自己管理，通过实现各种功能来体验一下堆分配过程中的技术细节，提高对内存分配的理解。

特性：  
- 基本的堆内存分配和释放；✔
- 内存释放后，合并前后空内存块；✔
- 内存碎片合并；
