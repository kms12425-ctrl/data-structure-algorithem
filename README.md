<div align="center">
  <h1>数据结构与算法实验项目 / Data Structure and Algorithm Lab Project</h1>
  <button id="btn-zh" class="lang-btn active">中文</button>
  <button id="btn-en" class="lang-btn">English</button>
</div>

<div id="zh" style="display:block;">

## 简介

本项目包含了数据结构课程的实验任务与源代码，涵盖了常用的数据结构实现与相关实验报告。内容组织如下：

- 📄 课程实验任务文档：`Data Structure Laboratory Task Document (2024 ）​.docx`
- 🗂️ 源代码（Data Structure source code 文件夹）：
  - Graph（图）
  - LinkList（链表）
  - Sequence Structure（顺序结构）
  - binary tree（二叉树）
  - 📄 实验报告：`Data Structure Lab Report.pdf`

## 如何使用

1. 浏览 `Data Structure source code` 文件夹获取各类数据结构的源码实现。
2. 阅读对应目录下的文档和代码，了解具体实现方法。
3. `Data Structure Lab Report.pdf` 提供了实验总结和分析。

## 适用对象

- 数据结构课程学习者
- 编程基础提升者

## 许可

本项目仅供学习和交流使用，禁止用于商业用途。

</div>

<div id="en" style="display:none;">

## Introduction

This project contains lab tasks and source code for a Data Structures course, covering implementations of common data structures and related lab reports. The content is organized as follows:

- 📄 Lab Task Document: `Data Structure Laboratory Task Document (2024 ）​.docx`
- 🗂️ Source Code (`Data Structure source code` folder):
  - Graph
  - LinkList
  - Sequence Structure
  - binary tree
  - 📄 Lab Report: `Data Structure Lab Report.pdf`

## How to Use

1. Explore the `Data Structure source code` folder for various data structure implementations.
2. Read the documentation and code in each directory for detailed implementation methods.
3. The `Data Structure Lab Report.pdf` provides summaries and analysis of experiments.

## Audience

- Students learning Data Structures
- Beginners seeking to improve their programming skills

## License

For educational and communication purposes only; commercial use is prohibited.

</div>

<style>
.lang-btn.active {
  font-weight: bold;
  background: #e0e0e0;
}
</style>

<script>
document.addEventListener('DOMContentLoaded', function() {
  const btnZh = document.getElementById('btn-zh');
  const btnEn = document.getElementById('btn-en');
  const zhDiv = document.getElementById('zh');
  const enDiv = document.getElementById('en');

  btnZh.addEventListener('click', function() {
    zhDiv.style.display = 'block';
    enDiv.style.display = 'none';
    btnZh.classList.add('active');
    btnEn.classList.remove('active');
  });

  btnEn.addEventListener('click', function() {
    zhDiv.style.display = 'none';
    enDiv.style.display = 'block';
    btnEn.classList.add('active');
    btnZh.classList.remove('active');
  });
});
</script>
