感谢 CCareaga/heap_allocator 写的简单版本堆分配器的启发，网址：https://github.com/CCareaga/heap_allocator 。准备自己实现一个练练手。  

主要借用 `malloc` 分配一块空间出来自己管理，通过实现各种功能来体验一下堆分配过程中的技术细节，提高对内存分配的理解。

特性：  

- 基本的堆内存分配和释放；✔
- 内存释放后，合并前后空内存块；✔
- 超出可分配容量后的边际处理；✔
- 内存碎片合并；✔

选加：

- 最佳匹配算法，分配内存时自动选择最合适的最小可用空内存块；


测试结果：

``` c
test_heap_alloc: 95                           // 不带碎片合并的堆分配结果
test_heap_alloc_with_fragment_merge: 139      // 带碎片合并的堆分配结果
test_malloc: 95                               // c 自带接口的分配结果
```

其它：

- 观察下来，`malloc` 接口实现的内存分配不像我这边实现的这样，有可能是把头尾信息放在其它地方了，分配的多块空间是连续的，也因此我在 `test_malloc` 计算的时候将头尾的 `size` 加上了，以方便比较。另外它本身没有自动的内存碎片处理，结果和我不加碎片合并代码的结果一致；
- 事实上，头信息确实不应该包含在具体的堆空间中，会造成使用者的困惑（主要是对 `HEAP_SIZE` 本身大小的困惑）。还有，合并内存碎片不可避免会有消耗，借用额外内存实现最佳匹配算法（我这边没有实现，以后再说~）能一定程度提高内存的利用率，为大内存分配成功增加概率。
