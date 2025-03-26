# QWQC

1. *qwqc 的注释很容易理解。*
2. *qwqc 基于 [acwj](https://github.com/DoctorWkt/acwj/) 项目。*
3. *qwqc 的整体风格模仿 [Lua](https://github.com/lua/lua/)。*

qwqc 是一个简单轻量的 C 编译器，带有 [QBE](https://c9x.me/compile/) 后端。它旨在易于使用和理解，强调简单性和教育性。未来可能会添加更多后端，例如自定义虚拟机。

## 构建
```bash
cmake -Bbuild
cmake --build build -j
```
test文件每个测试源文件都拥有完整的测试命令，详情打开查看

> **Copyright (c) 2025 Xuanluo Qiu <<xuanluo.qwq@gmail.com>>, GPL3.**
