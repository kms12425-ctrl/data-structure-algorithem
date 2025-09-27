<!DOCTYPE html>
<html lang="zh-cn">
<head>
  <meta charset="UTF-8">
  <title>数据结构与算法实验项目 / Data Structure and Algorithm Lab Project</title>
  <style>
    .lang-btn.active {
      font-weight: bold;
      background: #e0e0e0;
    }
    .lang-btn {
      margin: 0 5px;
      padding: 5px 15px;
      border: 1px solid #ccc;
      border-radius: 4px;
      background: #f9f9f9;
      cursor: pointer;
      transition: background 0.2s;
    }
    .lang-btn:hover {
      background: #f0f0f0;
    }
    body {
      font-family: "Segoe UI", "PingFang SC", "Microsoft YaHei", Arial, sans-serif;
      margin: 40px;
    }
    [align="center"] {
      margin-bottom: 30px;
    }
  </style>
</head>
<body>
  <div align="center">
    <h1>数据结构与算法实验项目 / Data Structure and Algorithm Lab Project</h1>
    <button id="btn-zh" class="lang-btn active">中文</button>
    <button id="btn-en" class="lang-btn">English</button>
  </div>

  <div id="zh" style="display:block;">
    <!-- 中文内容开始 -->
    <h2>简介</h2>
    <p>本项目包含了数据结构课程的实验任务与源代码，涵盖了常用的数据结构实现与相关实验报告。内容组织如下：</p>
    <ul>
      <li>📄 课程实验任务文档：<code>Data Structure Laboratory Task Document (2024 ）​.docx</code></li>
      <li>🗂️ 源代码（Data Structure source code 文件夹）：
        <ul>
          <li>Graph（图）</li>
          <li>LinkList（链表）</li>
          <li>Sequence Structure（顺序结构）</li>
          <li>binary tree（二叉树）</li>
          <li>📄 实验报告：<code>Data Structure Lab Report.pdf</code></li>
        </ul>
      </li>
    </ul>
    <h2>如何使用</h2>
    <ol>
      <li>浏览 <code>Data Structure source code</code> 文件夹获取各类数据结构的源码实现。</li>
      <li>阅读对应目录下的文档和代码，了解具体实现方法。</li>
      <li><code>Data Structure Lab Report.pdf</code> 提供了实验总结和分析。</li>
    </ol>
    <h2>适用对象</h2>
    <ul>
      <li>数据结构课程学习者</li>
      <li>编程基础提升者</li>
    </ul>
    <h2>许可</h2>
    <p>本项目仅供学习和交流使用，禁止用于商业用途。</p>
    <!-- 中文内容结束 -->
  </div>

  <div id="en" style="display:none;">
    <!-- English content start -->
    <h2>Introduction</h2>
    <p>This project contains lab tasks and source code for a Data Structures course, covering implementations of common data structures and related lab reports. The content is organized as follows:</p>
    <ul>
      <li>📄 Lab Task Document: <code>Data Structure Laboratory Task Document (2024 ）​.docx</code></li>
      <li>🗂️ Source Code (<code>Data Structure source code</code> folder):
        <ul>
          <li>Graph</li>
          <li>LinkList</li>
          <li>Sequence Structure</li>
          <li>binary tree</li>
          <li>📄 Lab Report: <code>Data Structure Lab Report.pdf</code></li>
        </ul>
      </li>
    </ul>
    <h2>How to Use</h2>
    <ol>
      <li>Explore the <code>Data Structure source code</code> folder for various data structure implementations.</li>
      <li>Read the documentation and code in each directory for detailed implementation methods.</li>
      <li>The <code>Data Structure Lab Report.pdf</code> provides summaries and analysis of experiments.</li>
    </ol>
    <h2>Audience</h2>
    <ul>
      <li>Students learning Data Structures</li>
      <li>Beginners seeking to improve their programming skills</li>
    </ul>
    <h2>License</h2>
    <p>For educational and communication purposes only; commercial use is prohibited.</p>
    <!-- English content end -->
  </div>

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
</body>
</html>
